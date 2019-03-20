// excute_exe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

BOOL WinExe_Test(char *pszExePath, UINT uiCmdShow);
BOOL ShellExecute_Test(char *pszExePath, UINT uiCmdShow);
BOOL CreateProcess_Test(char *pszExePath, UINT uiCmdShow);


int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bRet = FALSE;
	bRet = WinExe_Test("C:\\Program Files (x86)\\EditPlus\\editplus.exe", SW_HIDE);
	if (bRet)
	{
		printf("editplus.exe Run Success (WinExe_Test)!\n");
	}
	else
	{
		printf("editplus.exe Run Failed (WinExe_Test)!\n");
	}

	bRet = ShellExecute_Test("C:\\Program Files (x86)\\EditPlus\\editplus.exe", SW_HIDE);
	if (bRet)
	{
		printf("editplus.exe Run Success (ShellExecute_Test)!\n");
	}
	else
	{
		printf("editplus.exe Run Failed (ShellExecute_Test)!\n");
	}

	bRet = CreateProcess_Test("C:\\Program Files (x86)\\EditPlus\\editplus.exe", SW_HIDE);
	if (bRet)
	{
		printf("editplus.exe Run Success (CreateProcess_Test)!\n");
	}
	else
	{
		printf("editplus.exe Run Failed (CreateProcess_Test)!\n");
	}

	system("pause");
	return 0;
}

BOOL WinExe_Test(char *pszExePath, UINT uiCmdShow)
{
	UINT uiRet = 0;
	uiRet = WinExec(pszExePath, uiCmdShow);
	if (31 < uiRet)
	{
		return TRUE;
	}
	return FALSE;

}

BOOL ShellExecute_Test(char *pszExePath, UINT uiCmdShow)
{
	HINSTANCE hInstance = 0;
	hInstance = ShellExecuteA(NULL, NULL, pszExePath, NULL, NULL, uiCmdShow);
	if (32 < (DWORD)hInstance)
	{
		return TRUE;
	}
	return FALSE;

}

BOOL CreateProcess_Test(char *pszExePath, UINT uiCmdShow)
{
	STARTUPINFOA si = { 0 };
	PROCESS_INFORMATION pi;
	BOOL bRet = FALSE;
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = uiCmdShow;
	bRet = CreateProcessA(NULL, pszExePath, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	if (bRet)
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		return TRUE;

	}
	return TRUE;
}