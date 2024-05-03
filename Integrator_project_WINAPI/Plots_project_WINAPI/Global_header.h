#pragma once
#include <Windows.h>
#include <tchar.h>
#include <cmath>
#include <string>
#include <vector>
#include <gdiplus.h>
#include <array>
#include "str_to_double.h"
#pragma warning(disable : 4996)
#define MAX_LOADSTRING 100
using namespace Gdiplus;
//TCHAR WidMain_NAME[MAX_LOADSTRING] = _T("MainWindow");
//HINSTANCE hInst;
LPVOID CreateControls(HWND hWnd);
//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);