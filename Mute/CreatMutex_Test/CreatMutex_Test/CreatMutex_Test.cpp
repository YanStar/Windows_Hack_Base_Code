// CreatMutex_Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>





bool IsAlreadyRun()
{
	HANDLE hMutex = NULL;
	hMutex = CreateMutexA(NULL, FALSE, "Mutextest");
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			return TRUE;
		}

	}
	return FALSE;
}


int _tmain(int argc, _TCHAR* argv[])
{
	if (IsAlreadyRun())
	{
		printf("Already run !\n");
	}
	else
	{
		printf("Not run !\n");
	}
	system("pause");
	return 0;
}

 