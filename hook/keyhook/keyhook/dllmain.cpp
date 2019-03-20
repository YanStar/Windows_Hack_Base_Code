// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <stdio.h>

#include <Windows.h>

#define DEF_PROCESS_NAME "notepad.exe"

HINSTANCE g_hInstance = NULL;
HHOOK g_hHOOK = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
							   g_hInstance = hinstDLL;
							   break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

LRESULT CALLBACK KeyBoradProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	char szPath[MAX_PATH] = { 0 };
	char *p = NULL;

	if (nCode = 0)
	{
		if ((!lParam & 0x8000000))
		{
			GetModuleFileNameA(NULL, szPath, MAX_PATH);
			p = strrchr(szPath, '\\');

			if (!_stricmp(p + 1, DEF_PROCESS_NAME))
			{
				return 1;
			}
		}
	}

	return CallNextHookEx(g_hHOOK, nCode, wParam, lParam);
}

#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport) void HookStart()
	{
		g_hHOOK = SetWindowsHookEx(WH_KEYBOARD, KeyBoradProc, g_hInstance, 0);
	}

	__declspec(dllexport) void HookStop()
	{
		if (g_hHOOK)
		{
			UnhookWindowsHookEx(g_hHOOK);
			g_hHOOK = NULL;
		}

	}
#ifdef __cplusplus
}
#endif