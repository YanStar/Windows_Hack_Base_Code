#include <Windows.h>
#include <stdio.h>
#include "resource.h"

bool FreeMyResource(UINT uiResouceName, WCHAR *lpszResourceType, char *lpszSaveFileName);

int main()
{
		char szSaveFileName[MAX_PATH] = "5200.txt";
		bool ok = FreeMyResource(IDR_MYRES1, L"MYRES", szSaveFileName);
		if (ok)
		{
			printf("Resource Save Success !");

		}
		else
		{
			printf("Resouce Save Failed !");
		}
		system("pause");
		return 0;

}

bool FreeMyResource(UINT uiResouceName, WCHAR *lpszResourceType, char *lpszSaveFileName)
{
	
	HRSRC hRsrc = FindResourceW(NULL, MAKEINTRESOURCE(uiResouceName), lpszResourceType);
	if (hRsrc == NULL)
	{
		return FALSE;
	}

	DWORD dwSize = SizeofResource(NULL, hRsrc);
	if (dwSize <= 0)
	{
		return FALSE;
	}

	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	if (hGlobal == NULL)
	{
		return FALSE;
	}

	LPVOID lpVoid = LockResource(hGlobal);
	if (lpVoid == NULL)
	{
		return FALSE;
	}

	FILE *fp = NULL;
	fopen_s(&fp, lpszSaveFileName, "wb+");
	if (fp == NULL)
	{
		return FALSE;
	}
	fwrite(lpVoid, sizeof(char), dwSize, fp);
	fclose(fp);
	return TRUE;
}
