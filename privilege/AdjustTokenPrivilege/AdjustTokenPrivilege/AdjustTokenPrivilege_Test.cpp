#include "stdafx.h"
#include <Windows.h>
#include "enable.h"

void ShowError(char *lpszText)
{
	char szErr[MAX_PATH] = { 0 };
	sprintf(szErr, "%s ERROR [%d]", lpszText, GetLastError());
	MessageBoxA(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
}

BOOL EnbalePrivileges(HANDLE hProcess, char *pszPrivilegesName)
{
	HANDLE hToken = NULL;
	LUID luidValue = { 0 };
	TOKEN_PRIVILEGES tokenPrivileges = { 0 };
	BOOL bRet = FALSE;
	DWORD dsRet = 0;

	bRet = OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken);
	if (FALSE == bRet)
	{
		ShowError("OpenProcessToken!");
		return FALSE;
	}
	bRet = LookupPrivilegeValueA(NULL, pszPrivilegesName, &luidValue);
	if (FALSE == bRet)
	{
		ShowError("LookupPrivilegeValueA!");
		return FALSE;
	}

	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[0].Luid = luidValue;
	tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	bRet = AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, 0, NULL, NULL);
	if (FALSE == bRet)
	{
		ShowError("AdjustTokenPrivileges");
		return FALSE;
	}
	else
	{
		dsRet = GetLastError();
		if (ERROR_SUCCESS == dsRet)
		{
			return TRUE;
		}
		else if (ERROR_NOT_ALL_ASSIGNED == dsRet)
		{
			ShowError("ERROR_NOT_ALL_ASSIGNED");
			return FALSE;
		}
	}

	return FALSE;
}