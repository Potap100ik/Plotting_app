#pragma once
#include <Windows.h>
#include <tchar.h>
#include <string.h>
#define MAX_LOADSTRING 100
#define static1 2
HWND hStat1;
HWND hWnd_help1;
LRESULT WndHelp(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		SetWindowText(hStat1, L"400 sdfasf");
		return 0;
	case WM_COMMAND:
		return 0;
	}
	return DefWindowProcA(hWnd, message, wparam, lparam);
}


int main_help_wnd()
{
	WNDCLASSA wc{};
	wc.lpszClassName = "Help Me Wnd";
	wc.lpfnWndProc = WndHelp;
	RegisterClassA(&wc);

    hWnd_help1 = CreateWindowA("Help Me Wnd", "ok",WS_OVERLAPPEDWINDOW,
		10, 10, 400, 400, NULL, NULL, NULL, NULL);
	ShowWindow(hWnd_help1, SW_SHOWNORMAL);
	MSG msg;
	hStat1 = CreateWindowA("static", "static", WS_VISIBLE | WS_CHILD,
		10, 10, 400, 400, hWnd_help1, (HMENU) static1, NULL, NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return 0;
}
