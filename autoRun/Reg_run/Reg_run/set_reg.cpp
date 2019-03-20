#include "stdafx.h"
#include <windows.h>

void ShowError(char *lpszText)
{
	char szBuff[MAX_PATH] = { 0 };
	sprintf(szBuff, "%s Error [%d]", lpszText, GetLastError());
	MessageBoxA(NULL, szBuff, "ERROR", MB_OK | MB_ICONERROR);
}

BOOL Reg_CurrentUser(char *lpszFileName, char *lpszValueName)
{
	HKEY hKey;
	if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey))
	{
		ShowError("RegOpenKeyExA");
		return FALSE;
	}
	if (ERROR_SUCCESS != RegSetValueExA(hKey, lpszValueName, 0, REG_SZ, (BYTE *)lpszFileName, (1 + lstrlenA(lpszFileName))))
	{
		RegCloseKey(hKey);
		ShowError("RegSetValueExA");
		return FALSE;
	}
	RegCloseKey(hKey);

	return TRUE;
}

BOOL Reg_LocalMachine(char *lpszFileName, char *lpszValueName)
{
	HKEY hKey;
	if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey))
	{
		ShowError("RegOpenKeyExA");
		return FALSE;
	}
	if (ERROR_SUCCESS != RegSetValueExA(hKey, lpszValueName, 0, REG_SZ, (BYTE *)lpszFileName, (1 + lstrlenA(lpszFileName))))
	{
		RegCloseKey(hKey);
		ShowError("RegSetValueExA");
		return FALSE;
	}
	RegCloseKey(hKey);

	return TRUE;
}