// ScreenCapture.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ScreenCapture.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == ScreenCapture())
	{
		printf("Screen Capture Error.\n");
	}
	printf("Screen Capture Suceess.\n");
	system("pause");
	return 0;
}

