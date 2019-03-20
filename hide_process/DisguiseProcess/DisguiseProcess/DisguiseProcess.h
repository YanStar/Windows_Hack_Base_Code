#ifndef _DISGUISE_PROCESS_H_
#define _DISGUISE_PROCESS_H_


#include <Windows.h>
#include <winternl.h>


typedef NTSTATUS(NTAPI *typedef_NtQueryInformationProcess)(
	IN HANDLE ProcessHandle,
	IN PROCESSINFOCLASS ProcessInformationClass,
	OUT PVOID ProcessInformation,
	IN ULONG ProcessInformationLength,
	OUT PULONG ReturnLength OPTIONAL
	);


// �޸�ָ�����̵Ľ��̻�����PEB�е�·������������Ϣ, ʵ�ֽ���αװ
BOOL DisguiseProcess(DWORD dwProcessId, wchar_t *lpwszPath, wchar_t *lpwszCmd);
void ShowError(char *lpszText);


#endif