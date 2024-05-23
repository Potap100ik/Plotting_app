#pragma once
#include "Main_files/STD/stdafx.h"
#include "Main_files/type.h"
const wchar_t NUMBERIC_STR[] = L"0123456789-..";
const wchar_t COMMA_[] = L",,";

int CheckOnlyNumbers(LPWSTR& A_wstr, LPWSTR& B_wstr, LPWSTR& H_wstr, HWND hWndEdit_Erroors, HWND hWnd, HWND hWndEdit_Integral);
int CheckFunctionErrorMsg(ERROR_STRUCT& err_msg, HWND hWndEdit_Erroors, HWND hWnd);
int CheckImageOpening(Gdiplus::Bitmap* img_bck, Gdiplus::Bitmap* img_home, Gdiplus::Bitmap* img_clr, HWND hWnd);





