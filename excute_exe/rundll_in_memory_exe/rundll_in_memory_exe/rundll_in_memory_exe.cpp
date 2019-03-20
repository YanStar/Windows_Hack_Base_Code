// rundll_in_memory_exe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "MmLoadDll.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char szFileName[MAX_PATH] = "I:\\VS2013Project\\windows_hack_base_code\\excute_exe\\rundll_in_memory\\Debug\\rundll_in_memory.dll";

	HANDLE hFile = CreateFileA(szFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		ShowError("CreateFile");
		return FALSE;
	}

	DWORD dsFileSize = GetFileSize(hFile, NULL);

	BYTE *lpData = new BYTE[dsFileSize];
	if (NULL == lpData)
	{
		ShowError("new");
		return FALSE;

	}
	DWORD bRet = 0;
	ReadFile(hFile, lpData, dsFileSize, &bRet, NULL);

	LPVOID lpBaseAdress = MmLoadLibrary(lpData, dsFileSize);
	if (NULL == lpBaseAdress)
	{
		ShowError("MmLoadLibrary");
		return FALSE;
	}

	printf("加载dll成功！");

	typedef BOOL(*typedef_ShowMessage)(char *lpszText, char *lpszCation);
	typedef_ShowMessage ShowMessage = (typedef_ShowMessage)MmGetProAddress(lpBaseAdress, "ShowMessage");
	if (NULL == ShowMessage)
	{
		ShowError("MmGetProAddress");
		return FALSE;
	}
	ShowMessage("I am Hello\n", "HELLO WORLD!");

	BOOL bRetOK = MmFreeLibrary(lpBaseAdress);
	if (FALSE == bRetOK)
	{
		ShowError("MmFreeLibrary");
		return FALSE;
	}

	delete[] lpData;
	lpData = NULL;
	CloseHandle(hFile);

	system("pause");

	return 0;
}

