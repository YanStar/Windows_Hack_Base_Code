#include "stdio.h"
#include <Windows.h>
#include <conio.h>


#define DEF_DLL_NAME "I:\\VS2013Project\\windows_hack_base_code\\hook\\inject\\Debug\\keyhook.dll"
#define DEF_HOOKSTART "HookStart"
#define DEF_HOOKSTOP "HookStop"

typedef void(*PEN_HOOKSTART)();
typedef void(*PEN_HOOKSTOP)();


void main()
{
	HMODULE hDll = NULL;
	PEN_HOOKSTART HookStart = NULL;
	PEN_HOOKSTART HookStop = NULL;
	char ch = 0;

	hDll = LoadLibraryA(DEF_DLL_NAME);

	HookStart = (PEN_HOOKSTART)GetProcAddress(hDll, DEF_HOOKSTART);
	HookStop = (PEN_HOOKSTART)GetProcAddress(hDll, DEF_HOOKSTOP);

	HookStart();

	printf(".....");
	while (_getch()!= 'q')
	{
		HookStop();

		FreeLibrary(hDll);
	}

}
