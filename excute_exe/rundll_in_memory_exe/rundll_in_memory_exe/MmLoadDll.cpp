#include "stdafx.h"
#include <windows.h>
#include "MmLoadDll.h"




void ShowError(char *lpszText)
{
	char szErr[MAX_PATH] = { 0 };
	sprintf(szErr, "%s Error [%d]\n", lpszText, GetLastError());
	MessageBoxA(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);

}


LPVOID MmLoadLibrary(LPVOID lpdata, DWORD dwSize)
{
	LPVOID lpBassAddress = NULL;

	DWORD dwSizeOfImage = GetSizeOfImage(lpdata);

	lpBassAddress = VirtualAlloc(NULL, dwSizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (NULL == lpBassAddress)
	{
		ShowError("VirtualAlloc");
		return FALSE;
	}

	RtlZeroMemory(lpBassAddress, dwSizeOfImage);

	if (FALSE == MmMapFile(lpdata, lpBassAddress))
	{
		ShowError("MmMapFile");
		return FALSE;
	}

	if (FALSE == DoRelocationTable(lpBassAddress))
	{
		ShowError("DoRelocationTable");
		return FALSE;
	}

	if (FALSE == DoImportTable(lpBassAddress))
	{
		ShowError("DoImportTable");
		return FALSE;
	}

	DWORD dwOldProtect = 0;
	if (FALSE == VirtualProtect(lpBassAddress, dwSizeOfImage, PAGE_EXECUTE_READWRITE, &dwOldProtect))
	{
		ShowError("VirtualProtect");
		return FALSE;
	}

	if (FALSE == SetImageBase(lpBassAddress))
	{
		ShowError("SetImageBase");
		return FALSE;
	}

	if (FALSE == CallDllMain(lpBassAddress))
	{
		ShowError("CallDllMain");
		return FALSE;
	}

	return lpBassAddress;



}


DWORD GetSizeOfImage(LPVOID lpdata)
{
	DWORD dwSizeOfImage = 0;
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpdata;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
	dwSizeOfImage = pNtHeaders->OptionalHeader.SizeOfImage;
	return dwSizeOfImage;
}

BOOL MmMapFile(LPVOID lpdata, LPVOID lpBaseAddress)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpdata;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);

	//获取所有头+节区头的大小
	DWORD dwSzieOfHeaders = pNtHeaders->OptionalHeader.SizeOfHeaders;

	//获取所有节区的数量
	WORD wNumberOfSections = pNtHeaders->FileHeader.NumberOfSections;

	//获取第一个节区头的地址
	PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeaders + sizeof(IMAGE_NT_HEADERS));

	RtlCopyMemory(lpBaseAddress, lpdata, dwSzieOfHeaders);

	WORD i = 0;
	LPVOID lpSrcMem = NULL;
	LPVOID lpDestMem = NULL;
	DWORD dwSizeOfRawData = 0;

	for (i = 0; i < wNumberOfSections; i++)
	{
		if ((0 == pSectionHeader->VirtualAddress) || (0 == pSectionHeader->SizeOfRawData))
		{
			pSectionHeader++;
			continue;
		}

		lpSrcMem = (LPVOID)((DWORD)lpdata + pSectionHeader->PointerToRawData);
		lpDestMem = (LPVOID)((DWORD)lpBaseAddress + pSectionHeader->VirtualAddress);
		dwSizeOfRawData = pSectionHeader->SizeOfRawData;
		RtlCopyMemory(lpDestMem, lpSrcMem, dwSizeOfRawData);

		pSectionHeader++;

	}
	return TRUE;

}

BOOL DoRelocationTable(LPVOID lpBaseAddress)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
	PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((unsigned long)pDosHeader + pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

	//判断是否有重定位
	if ((PVOID)pLoc == (PVOID)pDosHeader)
	{
		//没有重定位
		return TRUE;
	}

	while ((pLoc->VirtualAddress + pLoc->SizeOfBlock) != 0)
	{
		WORD *pLocData = (WORD *)((PBYTE)pLoc + sizeof(IMAGE_BASE_RELOCATION));

		int nNumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);

		for (int i = 0; i < nNumberOfReloc; i++)
		{
			if ((DWORD)(pLocData[i] & 0x0000F000) == 0x00003000)
			{
				DWORD * pAddress = (DWORD *)((PBYTE)pDosHeader + pLoc->VirtualAddress + (pLocData[i] & 0x0FFF));
				DWORD dwDelta = (DWORD)pDosHeader - pNtHeaders->OptionalHeader.ImageBase;
				*pAddress += dwDelta;
			}
		}

		pLoc = (PIMAGE_BASE_RELOCATION)((PBYTE)pLoc + pLoc->SizeOfBlock);
	}
	return TRUE;
}

BOOL DoImportTable(LPVOID lpBaseAddress)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)pDosHeader + pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	//循环遍历DLL导入表中的DLL及获取导入表中的函数地址
	char *lpDllName = NULL;
	HMODULE hDll = NULL;
	PIMAGE_THUNK_DATA lpImportNameArray = NULL;
	PIMAGE_IMPORT_BY_NAME lpImportByName = NULL;
	PIMAGE_THUNK_DATA lpImportFuncAddrArray = NULL;
	FARPROC lpFuncAddress = NULL;
	DWORD i = 0;

	while (TRUE)
	{
		if (0 == pImportTable->OriginalFirstThunk)
		{
			break;
		}

		//获取导入表中dll的名称并加载dll
		lpDllName = (char *)((DWORD)pDosHeader + pImportTable->Name);
		hDll = GetModuleHandleA(lpDllName);
		if (NULL == hDll)
		{
			hDll = LoadLibraryA(lpDllName);
			if (NULL == hDll)
			{
				pImportTable++;
				continue;
			}
		}
		i = 0;

		lpImportNameArray = (PIMAGE_THUNK_DATA)((DWORD)pDosHeader + pImportTable->OriginalFirstThunk);

		lpImportFuncAddrArray = (PIMAGE_THUNK_DATA)((DWORD)pDosHeader + pImportTable->FirstThunk);

		while (TRUE)
		{
			if (0 == lpImportNameArray[i].u1.AddressOfData)
			{
				break;
			}

			lpImportByName = (PIMAGE_IMPORT_BY_NAME)((DWORD)pDosHeader + lpImportNameArray[i].u1.AddressOfData);

			if (0x80000000 & lpImportNameArray[i].u1.Ordinal)
			{
				lpFuncAddress = GetProcAddress(hDll, (LPCSTR)(lpImportNameArray[i].u1.Ordinal & 0x0000FFFF));
			}
			else
			{
				lpFuncAddress = GetProcAddress(hDll, (LPCSTR)(lpImportByName->Name));
			}
			lpImportFuncAddrArray[i].u1.Function = (DWORD)lpFuncAddress;
			i++;
		}
		pImportTable++;


	}
	return TRUE;
}

BOOL SetImageBase(LPVOID lpBaseAddress)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
	pNtHeaders->OptionalHeader.ImageBase = (ULONG32)lpBaseAddress;
	return TRUE;
}

BOOL CallDllMain(LPVOID lpBaseAddress)
{
	typedef_DllMain DllMain = NULL;
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
	DllMain = (typedef_DllMain)((ULONG32)pDosHeader + pNtHeaders->OptionalHeader.AddressOfEntryPoint);
	// 调用入口函数,附加进程DLL_PROCESS_ATTACH
	BOOL bRet = DllMain((HINSTANCE)lpBaseAddress, DLL_PROCESS_ATTACH, NULL);
	if (FALSE == bRet)
	{
		ShowError("DllMain");
	}

	return bRet;
}

LPVOID MmGetProAddress(LPVOID lpBaseAddress, PCHAR lpszFuncName)
{
	LPVOID lpFunc = NULL;
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpBaseAddress;
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((ULONG32)pDosHeader + pDosHeader->e_lfanew);
	PIMAGE_EXPORT_DIRECTORY pExporTable = (PIMAGE_EXPORT_DIRECTORY)((DWORD)pDosHeader + pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	
	PDWORD lpAddressOfNameArray = (PDWORD)((DWORD)pDosHeader + pExporTable->AddressOfNames);
	PCHAR lpFuncName = NULL;
	PWORD lpAddressOfNameOrdinalsArray = (PWORD)((DWORD)pDosHeader + pExporTable->AddressOfNameOrdinals);
	WORD wHint = 0;
	PDWORD lpAddressOfFuncationsArray = (PDWORD)((DWORD)pDosHeader + pExporTable->AddressOfFunctions);

	DWORD dwNumberOfNames = pExporTable->NumberOfNames;
	DWORD i = 0;

	for (i = 0; i < dwNumberOfNames; i++)
	{
		lpFuncName = (PCHAR)((DWORD)pDosHeader + lpAddressOfNameArray[i]);
		if (0 == lstrcmpiA(lpFuncName, lpszFuncName))
		{
			wHint = lpAddressOfNameOrdinalsArray[i];
			lpFunc = (LPVOID)((DWORD)pDosHeader + lpAddressOfFuncationsArray[wHint]);
			break;
		}
	}
	return lpFunc;

}

BOOL MmFreeLibrary(LPVOID lpBaseAddress)
{
	BOOL bRet = FALSE;
	if (NULL == lpBaseAddress)
	{
		return bRet;
	}

	bRet = VirtualFree(lpBaseAddress, 0, MEM_RELEASE);
	lpBaseAddress = NULL;
	return bRet;
}