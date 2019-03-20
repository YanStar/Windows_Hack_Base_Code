// auto_run_startup.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <ShlObj.h>


BOOL Auto_Startup(char *lpszScrFilePath, char *lpszDestFileName)
{
	BOOL bRet = FALSE;
	char szStartupPath[MAX_PATH] = { 0 };
	char szDestFilePath[MAX_PATH] = { 0 };

	bRet = SHGetSpecialFolderPathA(NULL, szStartupPath, CSIDL_STARTUP, TRUE);
	printf("szStartupPath=%s\n", szStartupPath);
	if (FALSE == bRet)
	{
		return FALSE;
	}

	sprintf(szDestFilePath, "%s\\%s", szStartupPath, lpszDestFileName);
	bRet = CopyFileA(lpszScrFilePath, szDestFilePath, FALSE);
	if (FALSE == bRet)
	{
		return FALSE;
	}
	return TRUE;
}



int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == Auto_Startup("E:\\Xshell\\Shadowsocks-4.0.7\\Shadowsocks.exe", "Shadowsocks.exe"))
	{
		printf("startup error!\n");
	}
	printf("startup ok!\n");
	system("pause");
	return 0;
}

