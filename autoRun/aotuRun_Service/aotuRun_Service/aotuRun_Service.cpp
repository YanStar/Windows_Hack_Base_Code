// aotuRun_Service.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServicewOperate.h"



int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bRet = FALSE;
	char szFileName[MAX_PATH] = "I:\\VS2013Project\\windows_hack_base_code\\autoRun\\aotuRun_Service\\Debug\\ServiceTest.exe";
	bRet = SystemServiceOperate(szFileName, 0);
	if (FALSE == bRet)
	{
		printf("Create Error! \n");
	}
	bRet = SystemServiceOperate(szFileName, 1);
	if (FALSE == bRet)
	{
		printf("Start Error! \n");
	}
	printf("Creat and Start Success! \n");

	system("pause");

	bRet = SystemServiceOperate(szFileName, 2);
	if (FALSE == bRet)
	{
		printf("Stop Error! \n");
	}

	bRet = SystemServiceOperate(szFileName, 3);
	if (FALSE == bRet)
	{
		printf("Delete Error! \n");
	}
	printf("Stop and Delete Success! \n");

	system("pause");

	return 0;
}

