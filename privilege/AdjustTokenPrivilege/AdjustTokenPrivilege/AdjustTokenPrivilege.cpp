// AdjustTokenPrivilege.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include "enable.h"


int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == EnbalePrivileges(GetCurrentProcess(), "SeDebugPrivilege"))
	{
		printf("Enable Privileges Error! \n");
	}
	printf("Enable Privileges Success! \n");
	system("pause");
	return 0;
}

