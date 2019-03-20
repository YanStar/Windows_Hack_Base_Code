// SaveKeyBoradInput.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "RawInputTest.h"
#define IDD_DIALOG1 101

BOOL CALLBACK ProMainDlg(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_INITDIALOG == uiMsg)
	{
		Init(hWnd);
	}
	else if (WM_CLOSE == uiMsg)
	{
		EndDialog(hWnd, NULL);
	}
	else if (WM_INPUT == uiMsg)
	{
		GetData(lParam);
	}
	return FALSE;
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd )
{
	DialogBoxParam(hInstance, (LPCSTR)IDD_DIALOG1, NULL, (DLGPROC)ProMainDlg, NULL);
	ExitProcess(NULL);
	return 0;
}

