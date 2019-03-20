#include "stdafx.h"
#include "DisguiseProcess.h"


void ShowError(char *lpszText)
{
	char szErr[MAX_PATH] = { 0 };
	sprintf(szErr, "%s ERROR [%d]", lpszText, GetLastError());
	MessageBoxA(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
}

BOOL DisguiseProcess(DWORD dwProcessId, wchar_t *lpwszPath, wchar_t *lpwszCmd)
{
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (NULL == hProcess)
	{
		ShowError("OpenProcess");
		return FALSE;
	}

	typedef_NtQueryInformationProcess NtQueryInformationProcess = NULL;
	PROCESS_BASIC_INFORMATION pbi = { 0 };
	PEB peb = { 0 };
	RTL_USER_PROCESS_PARAMETERS Param = { 0 };
	USHORT usCmdLen = 0;
	USHORT usPathLen = 0;

	NtQueryInformationProcess = (typedef_NtQueryInformationProcess)::GetProcAddress(LoadLibraryA("ntdll.dll"), "NtQueryInformationProcess");
	if (NULL == NtQueryInformationProcess)
	{
		ShowError("GetProcAddress");
		return FALSE;
	}

	NTSTATUS status = NtQueryInformationProcess(hProcess, ProcessBasicInformation, &pbi, sizeof(pbi), NULL);
	if (!NT_SUCCESS(status))
	{
		ShowError("NtQueryInformationProcess");
		return FALSE;
	}


	::ReadProcessMemory(hProcess, pbi.PebBaseAddress, &peb, sizeof(peb), NULL);
	::ReadProcessMemory(hProcess, peb.ProcessParameters, &Param, sizeof(Param), NULL);

	usCmdLen = 2 + 2 * ::wcslen(lpwszCmd);
	::WriteProcessMemory(hProcess, Param.CommandLine.Buffer, lpwszCmd, usCmdLen, NULL);
	::WriteProcessMemory(hProcess, &Param.CommandLine.Length, &usCmdLen, sizeof(usCmdLen), NULL);


	usPathLen = 2 + 2 * ::wcslen(lpwszPath);
	::WriteProcessMemory(hProcess, Param.ImagePathName.Buffer, lpwszPath, usPathLen, NULL);
	::WriteProcessMemory(hProcess, &Param.ImagePathName.Length, &usPathLen, sizeof(usPathLen), NULL);
	
	return TRUE;

}