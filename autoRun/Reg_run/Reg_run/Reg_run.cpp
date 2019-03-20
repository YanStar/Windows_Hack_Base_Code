// Reg_run.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include "set_reg.h"


int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == Reg_CurrentUser("E:\\Xshell\\Shadowsocks-4.0.7\\Shadowsocks.exe", "520"))
	{
		ShowError("Reg_CurrentUser_printf\n");
	}

	if (FALSE == Reg_LocalMachine("E:\\Xshell\\Shadowsocks-4.0.7\\Shadowsocks.exe", "520"))
	{
		ShowError("Reg_LocalMachine_printf\n");
	}
	printf("Reg OK.\n");

	system("pause");
	return 0;
}

