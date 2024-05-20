#pragma once
#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"

LRESULT CALLBACK Integral_Wnd_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void WND_Integral_Init(HWND hWnd_Integer_Wnd, LPSTR text_, double A, double B, double H);