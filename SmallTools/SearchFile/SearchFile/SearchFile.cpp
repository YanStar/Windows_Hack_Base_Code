// SearchFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

void SearchFile(char *pszDirectory);


int _tmain(int argc, _TCHAR* argv[])
{
	SearchFile("C:");
	system("pause");
	return 0;
}

void SearchFile(char *pszDirectory)
{
	DWORD dsBufferSize = 2048;
	char *pszFileName = NULL;
	char *pTempSrc = NULL;
	WIN32_FIND_DATA FileData = { 0 };
	BOOL bRet = FALSE;

	pszFileName = new char[dsBufferSize];
	pTempSrc = new char[dsBufferSize];

	wsprintf(pszFileName, "%s\\*.*", pszDirectory);

	HANDLE hFile = FindFirstFile(pszFileName, &FileData);
	if (INVALID_HANDLE_VALUE != hFile)
	{
		do 
		{
			if ('.' == FileData.cFileName[0])
			{
				continue;
			}
			sprintf(pTempSrc, "%s\\%s", pszDirectory, FileData.cFileName);

			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				SearchFile(pTempSrc);
			}
			else
			{
				printf("%s\n", pTempSrc);
			}
		} while (FindNextFile(hFile,&FileData));
	}

	FindClose(hFile);
	delete []pTempSrc;
	pTempSrc = NULL;
	delete[] pszFileName;
	pszFileName = NULL;


}