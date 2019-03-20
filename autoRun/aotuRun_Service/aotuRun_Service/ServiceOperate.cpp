#include "stdafx.h"
#include <Windows.h>
#include "ServicewOperate.h"

void ShowError(char *lpszText)
{
	char szErr[MAX_PATH] = { 0 };
	sprintf(szErr, "%s ERROR [%d]", lpszText, GetLastError());
	MessageBoxA(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
}

BOOL SystemServiceOperate(char *lpszDriverPath, int iOperateType)
{
	BOOL bRet = FALSE;
	char szName[MAX_PATH] = { 0 };

	lstrcpyA(szName, lpszDriverPath);
	PathStripPathA(szName);

	SC_HANDLE shOSCM = NULL, shCS = NULL;
	SERVICE_STATUS ss;

	shOSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!shOSCM)
	{
		ShowError("OpenSCManager");
		return FALSE;

	}
	if (0 != iOperateType)
	{
		shCS = OpenServiceA(shOSCM, szName, SERVICE_ALL_ACCESS);
		if (!shCS)
		{
			ShowError("OpenServiceA");
			CloseServiceHandle(shOSCM);
			shOSCM = NULL;
			return FALSE;
		}
	}

	switch (iOperateType)
	{
	case 0:
	{
			  shCS = CreateServiceA(shOSCM, szName, szName, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, lpszDriverPath, NULL, NULL, NULL, NULL, NULL);
			  if (!shCS)
			  {
				  ShowError("CreateServiceA");
				  bRet = FALSE;
			  }
			  break;
	}
	case 1:
	{
			  if (!StartService(shCS, 0, NULL))
			  {
				  ShowError("StartService");
				  bRet = FALSE;
			  }
			  break;
	}
	case 2:
	{
			  if (!ControlService(shCS, SERVICE_CONTROL_STOP, &ss));
			  {
				  ShowError("ControlService");
				  bRet = FALSE;
			  }
			  break;
	}
	case 3:
	{
			  if (!DeleteService(shCS))
			  {
				  ShowError("DeleteService");
				  bRet = FALSE;
			  }
			  break;
	}
	default:
		break;
	}

	if (shCS)
	{
		CloseServiceHandle(shCS);
		shCS = NULL;
	}
	if (shOSCM)
	{
		CloseServiceHandle(shOSCM);
		shOSCM = NULL;

	}
	return bRet;
}