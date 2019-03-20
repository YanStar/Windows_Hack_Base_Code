#include "stdafx.h"
#include <Windows.h>
#include <atlimage.h>
#include "ScreenCapture.h"

BOOL ScreenCapture()
{
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hdc = GetDC(hDesktopWnd);
	HDC mdc = CreateCompatibleDC(hdc);
	DWORD dwScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD dwScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	HBITMAP bmp = CreateCompatibleBitmap(hdc, dwScreenWidth, dwScreenHeight);
	HBITMAP holdbmp = (HBITMAP)SelectObject(mdc, bmp);
	BitBlt(mdc, 0, 0, dwScreenWidth, dwScreenHeight, hdc, 0, 0, SRCCOPY);
	PaintMouse(mdc);
	SaveBmp(bmp);
	DeleteDC(hdc);
	DeleteDC(mdc);
	return TRUE;


}

BOOL PaintMouse(HDC hdc)
{
	HDC bufdc = NULL;
	CURSORINFO cursorInfo = { 0 };
	ICONINFO iconInfo = { 0 };
	HBITMAP bmpOldMask = NULL;

	bufdc = CreateCompatibleDC(hdc);
	RtlZeroMemory(&iconInfo, sizeof(cursorInfo));
	cursorInfo.cbSize = sizeof(cursorInfo);

	GetCursorInfo(&cursorInfo);

	GetIconInfo(cursorInfo.hCursor, &iconInfo);

	bmpOldMask = (HBITMAP)SelectObject(bufdc, iconInfo.hbmMask);
	BitBlt(hdc, cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y, 20, 20, bufdc, 0, 0, SRCAND);
	SelectObject(bufdc, iconInfo.hbmColor);
	BitBlt(hdc, cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y, 20, 20, bufdc, 0, 0, SRCPAINT);

	SelectObject(bufdc, bmpOldMask);
	DeleteObject(iconInfo.hbmColor);
	DeleteObject(iconInfo.hbmMask);
	DeleteDC(bufdc);
	return TRUE;
}

BOOL SaveBmp(HBITMAP hBmp)
{
	LPCTSTR imageName = L"Mybmp.jpg";
	ATL::CImage image;
	image.Attach(hBmp);
	image.Save(imageName);
	return TRUE;
}