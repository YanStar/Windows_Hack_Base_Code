// RemoteCmd.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

BOOL PipeCmd(char *pszCmd, char *pszResultBuffer, DWORD dwResultBufferSize);
void ShowError(char *pszText);


int _tmain(int argc, _TCHAR* argv[])
{
	char szCmd[] = "ping 127.0.0.1";
	char szResultBuffer[512] = { 0 };
	DWORD dwResultBufferSize = 512;

	if (FALSE == PipeCmd(szCmd, szResultBuffer, dwResultBufferSize))
	{
		ShowError("pipe cmd error");
	}
	else
	{
		printf("pipe cmd success!\nresult :\n%s\n",szResultBuffer);
	}
	system("pause");
	return 0;
}


void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	wsprintf(szErr, "%s ERROR [%d]", pszText, GetLastError());
	MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
}

BOOL PipeCmd(char *pszCmd, char *pszResultBuffer, DWORD dwResultBufferSize)
{
	HANDLE hReadPipe = NULL;
	HANDLE hWritePipe = NULL;
	SECURITY_ATTRIBUTES securityAttributes = { 0 };
	BOOL bRet = FALSE;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	securityAttributes.bInheritHandle = TRUE;
	securityAttributes.nLength = sizeof(securityAttributes);
	securityAttributes.lpSecurityDescriptor = NULL;

	bRet = CreatePipe(&hReadPipe, &hWritePipe, &securityAttributes, 0);
	if (FALSE == bRet)
	{
		ShowError("CreatePipe");
		return FALSE;
	}

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;

	bRet = CreateProcess(NULL, pszCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (FALSE == bRet)
	{
		ShowError("CreateProcess");
		return FALSE;
	}

	WaitForSingleObject(pi.hThread, INFINITE);
	WaitForSingleObject(pi.hProcess, INFINITE);

	RtlZeroMemory(pszResultBuffer, dwResultBufferSize);
	ReadFile(hReadPipe, pszResultBuffer, dwResultBufferSize, NULL, NULL);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);

	return TRUE;

}