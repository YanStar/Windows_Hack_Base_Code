// rundll_in_memory.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"


BOOL ShowMessage(char *lpszText, char *lpszCaption)
{
	MessageBoxA(NULL, lpszText, lpszCaption, MB_OK);
	return TRUE;
}
