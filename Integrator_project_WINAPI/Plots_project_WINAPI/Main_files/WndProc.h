#pragma once
#include "../Main_files/STD/stdafx.h"

LPVOID CreateControls(HWND hWnd);
void EditInit();
ATOM Register_Main_Plot_Wnd_Class();
ATOM Register_Integer_Wnd_Class();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
