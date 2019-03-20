// DisguiseProcess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DisguiseProcess.h"



int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == DisguiseProcess(9540, L"C:\\Windows\\explorer.exe", L"explorer.exe"));
	{
		printf("DisguiseProcess ERROR!\n");
		
	}
	printf("DisguiseProcess SUCCESS!\n");

	return 0;
}

