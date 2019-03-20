#ifndef _MM_LOAD_DLL_H_
#define _MM_LOAD_DLL_H_

#include <windows.h>

typedef BOOL(__stdcall *typedef_DllMain)(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

void ShowError(char *lpszText);
LPVOID MmLoadLibrary(LPVOID lpdata, DWORD dwSize);

DWORD GetSizeOfImage(LPVOID lpdata);


BOOL MmMapFile(LPVOID lpdata, LPVOID lpBaseAddress);

BOOL DoRelocationTable(LPVOID lpBaseAddress);
BOOL DoImportTable(LPVOID lpBaseAddress);

BOOL SetImageBase(LPVOID lpBaseAddress);
BOOL CallDllMain(LPVOID lpBaseAddress);
LPVOID MmGetProAddress(LPVOID lpBaseAddress, PCHAR lpszFuncName);
BOOL MmFreeLibrary(LPVOID lpBaseAddress);

#endif