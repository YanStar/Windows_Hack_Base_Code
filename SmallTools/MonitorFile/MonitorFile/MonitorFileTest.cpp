#include "MonitorFileTest.h"
#include "stdafx.h"
#include <Windows.h>


void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	wsprintf(szErr, "%S ERROR [%d]", pszText, GetLastError());
	MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);

}

void W2C(wchar_t *pwszSrc, int iSrcLen, char *pszDest, int iDestLen)
{
	RtlZeroMemory(pszDest, iDestLen);
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, (iSrcLen / 2), pszDest, iDestLen, NULL, NULL);

}

UINT MonitorFileThreadProc(LPVOID lpVoid)
{
	char *pszDirectory = (char *)lpVoid;

	HANDLE hDirectory = CreateFile(pszDirectory, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (INVALID_HANDLE_VALUE == hDirectory)
	{
		ShowError("CreateFile");
		return 1;
	}

	char szTemp[MAX_PATH] = { 0 };
	BOOL bRet = FALSE;
	DWORD dwRet = 0;
	DWORD dwBufferSize = 2048;

	BYTE *pBuf = new BYTE[dwBufferSize];
	if (NULL == pBuf)
	{
		ShowError("new");
		return FALSE;
	}
	FILE_NOTIFY_INFORMATION *pFileNotifyInfo = (FILE_NOTIFY_INFORMATION*)pBuf;

	do
	{
		RtlZeroMemory(pFileNotifyInfo, dwBufferSize);
		bRet = ReadDirectoryChangesW(hDirectory, pFileNotifyInfo, dwBufferSize, TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_LAST_WRITE, &dwRet, NULL, NULL);

		if (FALSE == bRet)
		{
			ShowError("ReadDirectoryChangesW");
			return FALSE;
		}

		W2C((wchar_t *)(&pFileNotifyInfo->FileName), pFileNotifyInfo->FileNameLength, szTemp, MAX_PATH);
		switch (pFileNotifyInfo->Action)
		{
		case FILE_ACTION_ADDED:
		{
								  printf("[File Added Action]%s\n", szTemp);
								  break;
		}
		default:
			break;
		}
	
	} while (bRet);
	
	CloseHandle(hDirectory);
	delete[] pBuf;
	pBuf = NULL;
	return 0;


}

void MonitorFile(char *pszDirectory)
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MonitorFileThreadProc, pszDirectory, 0, NULL);
}