#pragma once
#include "Debug_sys.h"

//манифест для кастомизации 
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma warning(disable : 4996)

#include <Windows.h>
#include <tchar.h>
#include <cmath>
#include <string>
#include <stdio.h>
#include <vector>
#include <gdiplus.h>
#include <array>
#include "str_to_double.h"
#include "Global_header.h"
#include "Simps_meth.h"
#include "resource.h"
#define MAX_LOADSTRING 100
#define edit_otst1 60
#define edit_otst2 20
#define MoveToEx(a, x, y, d); MoveToEx(a, x + Wnd_Plot.setka.sx_center, y*(-1) + Wnd_Plot.setka.sy_center, d);
#define LineTo(a, x, y); LineTo(a, x + Wnd_Plot.setka.sx_center, y*(-1) + Wnd_Plot.setka.sy_center);
#define TextOutW(dc, x, y, s, st); TextOutW(dc, x + Wnd_Plot.setka.sx_center, y*(-1) + Wnd_Plot.setka.sy_center, s, st);

using namespace Gdiplus;

//константы
#define MAX_LOADSTRING 100
#define edit_otst1 60
#define edit_otst2 20



//Типы данных
enum CTL_ID {
	HWNDBUTTON_ENTER,
	HWNDBUTTON_CLEARPLOT,
	HWNDBUTTON_INTEGER,
	HWNDBUTTON_HOME,
	HWNDEDIT_BASE,
	HWNDEDIT_A,
	HWNDEDIT_B,
	HWNDEDIT_H
};
struct Pointer {
	double x, y;
};
struct Pointer_lng_double {
	long double x, y;
};
typedef struct Plot {
	std::vector<Pointer> myvec_xy_picsel{};//вектор хранит пиксельные координаты x,y 
	std::vector<Pointer> myvec_xy{};//вектор хранит реальные координаты x,y для каждой точки графика
	double A, B, H;//получаемые из окна границы графика
	//double C;//


}MyPlot;
typedef struct Setka {
	int sx_center, sy_center;
	double LLeft, RRight, TTop, BBottom, u_HHH;
	int h_setka, h5_setka;
	double u5_setka;
	int mantissa;

	double kxy_zoom;
	double unit_to_pixel;
	int Wide_Vec, Left_Wide_Vec, Right_Wide_Vec;
}MySetka;
typedef struct Wnd_Plot_struct {
	HWND hWnd;
	MyPlot plot;
	MySetka setka;
	int sx, sy;//размеры текушщего окна
	//КООРДИНАТЫ КРАЕВ
	int x_LL, y_BB, x_RR, y_TT, x_LL5, y_BB5;
	LPSTR text_;


}MyWnd_Plot;
typedef struct SMouseMove {
	POINT Prev_mouse_point{};
	BOOL Flag_for_mouse;
}MouseMove;


//глобальные переменные
const int Wide_of_Screen = GetSystemMetrics(SM_CXSCREEN);
double IntegerSum;
int countpaint = 0;
std::wstring str;
MyWnd_Plot Wnd_Plot{};
MouseMove MyMouse{};
HWND
//hWnd_plot{},
hWndButton_enter{},
hWndButton_clearPlot{},
hWndButton_clearEdit{},
hWndButton_home{},
hWndEdit_base{},
hWndEdit_A{},
hWndEdit_B{},
hWndEdit_H{},
hWndEdit_Integral{};
extern HINSTANCE hInst;/////////////////////////////////////////////////////убери глобальные переменные потому что так надо
HDC hdc{};
TCHAR Win_Plot_NAME[MAX_LOADSTRING] = _T("PlotWindow");

//оконные создания
LPVOID CreateControls(HWND hWnd);
ATOM MyRegisterChildClass();
//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
//исполнительные функции
void Plotting_edges_upd(int);
double Setka_unit(double get_value);//придвигает кратность юнита сетки графика к 1,2 или 5
LPSTR Wide_into_Ascii(LPCWSTR sw);
void StructInit();
void CorrectSetkaPos(int);
void MousePos(BOOL, int, int);
void DrowSetka(HDC hdc);
void DrowCounts(HDC hdc);
void DrowGraphSmooth(HDC hdc);
void DrowGraph(HDC hdc);
void FirstPlotting();
void RedrawPlot();


LPVOID CreateControls(HWND hWnd)
{
	hWndButton_enter = CreateWindowEx(
		0,
		L"BUTTON",
		L"Построить график",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		60, 120, 240, 30,
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_ENTER),
		nullptr, nullptr);
	if (!hWndButton_enter)
		MessageBox(NULL, _T("hWndButton_enter"), _T("Ошибка"), MB_OK);

	hWndButton_clearPlot = CreateWindowEx(
		0,
		L"BUTTON",
		L"Убрать данные графика",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		edit_otst1, 160, 240, 30,
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_CLEARPLOT),
		nullptr, nullptr);
	if (!hWndButton_clearPlot)
		MessageBox(NULL, _T("hWndButton_clearPlot"), _T("Ошибка"), MB_OK);

	hWndButton_clearEdit = CreateWindowEx(
		0,
		L"BUTTON",
		L"Посчитать определенный интеграл",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		edit_otst1, 200, 240, 30,
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_INTEGER),
		nullptr, nullptr);
	if (!hWndButton_clearEdit)
		MessageBox(NULL, _T("hWndButton_clearEdit"), _T("Ошибка"), MB_OK);

	hWndButton_home = CreateWindowEx(
		0,
		L"BUTTON",
		L"Ы",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		edit_otst1, 240, 50, 50,
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_HOME),
		nullptr, nullptr);
	if (!hWndButton_clearEdit)
		MessageBox(NULL, _T("hWndButton_clearEdit"), _T("Ошибка"), MB_OK);



	hWndEdit_base = CreateWindow(
		L"EDIT",
		L"log(x)",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_MULTILINE,
		edit_otst1, 40, 240, 30,
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_BASE),
		nullptr, nullptr);

	if (!hWndEdit_base)
		MessageBox(NULL, _T("hWndEdit_base"), _T("Ошибка"), MB_OK);

	hWndEdit_A = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		L"1",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		edit_otst1, 80, 40, 30,
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_A),
		nullptr, nullptr);
	if (!hWndEdit_A)
		MessageBox(NULL, _T("hWndEdit_A"), _T("Ошибка"), MB_OK);
	hWndEdit_B = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		L"10",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		edit_otst1 + 80, 80, 60, 30,
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_B),
		nullptr, nullptr);
	if (!hWndEdit_B)
		MessageBox(NULL, _T("hWndEdit_B"), _T("Ошибка"), MB_OK);

	hWndEdit_H = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		L"0,1",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ETO_NUMERICSLOCAL,
		edit_otst1 + 180, 80, 60, 30,
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_H),
		nullptr, nullptr);
	if (!hWndEdit_H)
		MessageBox(NULL, _T("hWndEdit_H"), _T("Ошибка"), MB_OK);

	hWndEdit_Integral = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		L"Интеграл появится тут",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		edit_otst1 + 100, 260, 200, 30,
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_H),
		nullptr, nullptr);
	if (!hWndEdit_Integral)
		MessageBox(NULL, _T("hWndEdit_H"), _T("Ошибка"), MB_OK);
	return 0;
}
ATOM MyRegisterChildClass()
{
	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wcex.lpszClassName = Win_Plot_NAME;
	wcex.lpfnWndProc = Win_Plot;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hInstance = hInst;
	return RegisterClassEx(&wcex);
}


//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam)
{
	PAINTSTRUCT ps;
	Bitmap* img{};
	Gdiplus::Graphics* graph{};
	std::wstring text;
	switch (message)
	{
	case WM_CREATE:
		CreateControls(hWnd);
		if (!MyRegisterChildClass())
			MessageBox(NULL, _T("НЕ ВЫШЕЛ ГРАФИК ПОГУЛЯТЬ"), _T("Ошибка"), MB_OK);
		Wnd_Plot.hWnd = CreateWindow(Win_Plot_NAME, NULL, WS_CHILD | WS_DLGFRAME | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		StructInit();
		MousePos(FALSE, 0, 0);
		return 0;
	case WM_SIZE:
		Wnd_Plot.sx = LOWORD(lParam) - 405;
		Wnd_Plot.sy = HIWORD(lParam) - 5;
		MoveWindow(Wnd_Plot.hWnd, 400, 0, Wnd_Plot.sx, Wnd_Plot.sy, 1);
		Wnd_Plot.setka.sx_center = Wnd_Plot.sx / 2;
		Wnd_Plot.setka.sy_center = Wnd_Plot.sy / 2;
		return 0;
	
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		
		case VK_RETURN:
			printf("Hello Enter\n");
			SendMessage(hWnd, WM_COMMAND, HWNDBUTTON_ENTER, NULL);
			return 0;
		case HWNDBUTTON_ENTER:
		
			text.clear();
			text.reserve(MAX_LOADSTRING);
			GetWindowText(hWndEdit_base, &text[0], MAX_LOADSTRING);
			text.erase(remove(text.begin(), text.end(), 0), text.end());
			Wnd_Plot.text_ = Wide_into_Ascii(text.c_str());
			if (strlen(Wnd_Plot.text_) == 0)
			{
				MessageBox(hWnd, L"Уважаемый прогер\nГде ваша функция?", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
				return 0;
			}

			Plotting_edges_upd(2);
			FirstPlotting();
			UpdateWindow(Wnd_Plot.hWnd);
			InvalidateRect(Wnd_Plot.hWnd, NULL, TRUE);
		
		return 0;
		case	HWNDBUTTON_CLEARPLOT:
			Wnd_Plot.plot.myvec_xy_picsel.clear();
			Wnd_Plot.plot.myvec_xy.clear();
			Wnd_Plot.text_ = (LPSTR)"";
			InvalidateRect(Wnd_Plot.hWnd, NULL, TRUE);
			return 0;
		case HWNDBUTTON_INTEGER:
		{
			std::wstring Astr, Bstr, Hstr;
			text.clear();
			Astr.reserve(MAX_LOADSTRING);
			Bstr.reserve(MAX_LOADSTRING);
			Hstr.reserve(MAX_LOADSTRING);
			text.reserve(MAX_LOADSTRING);

			GetWindowText(hWndEdit_A, &Astr[0], MAX_LOADSTRING);
			GetWindowText(hWndEdit_B, &Bstr[0], MAX_LOADSTRING);
			GetWindowText(hWndEdit_H, &Hstr[0], MAX_LOADSTRING);
			GetWindowText(hWndEdit_base, &text[0], MAX_LOADSTRING);
			Wnd_Plot.text_ = Wide_into_Ascii(text.c_str());
			try
			{
				Wnd_Plot.plot.A = std::stod(Astr);
				Wnd_Plot.plot.B = std::stod(Bstr);
				Wnd_Plot.plot.H = std::stod(Hstr);
			}
			catch (...)
			{
				MessageBox(hWnd, L"Уважаемый прогер\nГде числа?!!!\nИз чего интегралы строить", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
				return 0;
			}
			Astr.clear(); Bstr.clear(); Hstr.clear(); text.clear();
			if (Wnd_Plot.plot.A == Wnd_Plot.plot.B || Wnd_Plot.plot.H == 0)
			{
				SetWindowText(hWndEdit_Integral, L"Интеграл равен нулю");
				return 0;
			}
			if (Wnd_Plot.plot.A > Wnd_Plot.plot.B || Wnd_Plot.plot.H == 0 || Wnd_Plot.plot.H > (Wnd_Plot.plot.B - Wnd_Plot.plot.A))
			{
				MessageBox(hWnd, L"Уважаемый прогер\nВ числах беспорядки!!!\nИз чего интегралы строить", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
				return 0;
			}
			if (strlen(Wnd_Plot.text_) == 0)
			{
				MessageBox(hWnd, L"Уважаемый прогер\nГде ваша функция?", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
				return 0;
			}
			try {
				IntegerSum = Integrator(Wnd_Plot.plot.A, Wnd_Plot.plot.B, Wnd_Plot.plot.H, Wnd_Plot.text_, Function_String_to_Double, Simps_method);
			}
			catch (double error_nan)
			{

				if (isinf(error_nan) || isnan(error_nan))
					SetWindowText(hWndEdit_Integral, L"Надо отрезок понепрерывнее");
				else
					SetWindowText(hWndEdit_Integral, L"Паранормальные явления в районе try-catch");
				return 0;
			}
			SetWindowText(hWndEdit_Integral, std::to_wstring(IntegerSum).c_str());
		}
		return 0;
		case HWNDBUTTON_HOME:
			Wnd_Plot.setka.sx_center = Wnd_Plot.sx / 2;
			Wnd_Plot.setka.sy_center = Wnd_Plot.sy / 2;
			Wnd_Plot.setka.h_setka = 10;
			Wnd_Plot.setka.u5_setka = 2;
			Wnd_Plot.setka.mantissa = 1;
			Wnd_Plot.setka.h5_setka = Wnd_Plot.setka.h_setka * 5;
			Wnd_Plot.setka.kxy_zoom = Wnd_Plot.setka.h5_setka / Wnd_Plot.setka.u5_setka;
			Wnd_Plot.setka.unit_to_pixel = 1.0 / Wnd_Plot.setka.kxy_zoom;
			Plotting_edges_upd(2);
			RedrawPlot();
			InvalidateRect(Wnd_Plot.hWnd, NULL, TRUE);
			return 0;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		img = Bitmap::FromFile(L"1.png");
		graph = new Gdiplus::Graphics(hdc);
		graph->DrawImage(img, 0, 0, 399, 445);
		delete graph;
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam)
{
	PAINTSTRUCT  ps2;
	HDC memdc;
	HBITMAP membit;
	HDC hdc2{};

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
		MousePos(TRUE, LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_MOUSEMOVE:
		if (MyMouse.Flag_for_mouse)
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			Wnd_Plot.setka.sx_center += x - MyMouse.Prev_mouse_point.x;
			Wnd_Plot.setka.sy_center += y - MyMouse.Prev_mouse_point.y;

			MyMouse.Prev_mouse_point.x = x;
			MyMouse.Prev_mouse_point.y = y;

			Plotting_edges_upd(2);
			if (Wnd_Plot.setka.LLeft < Wnd_Plot.setka.Left_Wide_Vec || Wnd_Plot.setka.RRight > Wnd_Plot.setka.Right_Wide_Vec)
			{
				Wnd_Plot.setka.Left_Wide_Vec = Wnd_Plot.setka.LLeft - (Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;
				Wnd_Plot.setka.Right_Wide_Vec = Wnd_Plot.setka.LLeft + (Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;
				RedrawPlot();
			}

			InvalidateRect(Wnd_Plot.hWnd, NULL, TRUE);
		}
		return 0;
	case WM_LBUTTONUP:
		MyMouse.Flag_for_mouse = FALSE;
		return 0;
	case WM_NCLBUTTONUP:
		MyMouse.Flag_for_mouse = FALSE;
		return 0;
	case WM_NCLBUTTONDOWN:
		MyMouse.Flag_for_mouse = FALSE;
		return 0;
	case WM_NCMOUSELEAVE:
		MyMouse.Flag_for_mouse = FALSE;
		return 0;
	case WM_MOUSEWHEEL:
	{
		int a = Wnd_Plot.setka.h_setka;
		Wnd_Plot.setka.h_setka += GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		/*{
			if (Wnd_Plot.setka.sx_center > Wnd_Plot.sx / 2)
				Wnd_Plot.setka.sx_center += GET_WHEEL_DELTA_WPARAM(wParam);
			else if (Wnd_Plot.setka.sx_center == Wnd_Plot.sx / 2) {}
			else
				Wnd_Plot.setka.sx_center -= GET_WHEEL_DELTA_WPARAM(wParam);

			if (Wnd_Plot.setka.sy_center > Wnd_Plot.sy / 2)
				Wnd_Plot.setka.sy_center += GET_WHEEL_DELTA_WPARAM(wParam);
			else if (Wnd_Plot.setka.sy_center == Wnd_Plot.sy / 2) {}
			else
				Wnd_Plot.setka.sy_center -= GET_WHEEL_DELTA_WPARAM(wParam);
		}*/
		CorrectSetkaPos(0);
		InvalidateRect(Wnd_Plot.hWnd, NULL, TRUE);
	}
	return 0;
	case WM_SIZE:
		Wnd_Plot.sx = LOWORD(lParam);
		Wnd_Plot.sy = HIWORD(lParam);
		return 0;
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
	{
		SimpleTimer timer;
		hdc2 = BeginPaint(Wnd_Plot.hWnd, &ps2);
		memdc = CreateCompatibleDC(hdc2);
		membit = CreateCompatibleBitmap(hdc2, Wnd_Plot.sx, Wnd_Plot.sy);
		SelectObject(memdc, membit);
		DrowSetka(memdc);
		DrowCounts(memdc);
		if (!Wnd_Plot.plot.myvec_xy_picsel.empty())
		{
			DrowGraphSmooth(memdc);
			//DrowGraph(memdc);оставим для экспериментов - рисование без GDI+
		}
		BitBlt(hdc2, 0, 0, Wnd_Plot.sx * 2, Wnd_Plot.sy * 2, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(membit);
		EndPaint(Wnd_Plot.hWnd, &ps2);
	}
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return DefWindowProc(hWnd, message, wParam, lParam);
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


//исполнительные функции
double Setka_unit(double get_value)
{
	double u;
	double c1 = get_value;
	int n;
	int k = 0;
	if (c1 >= 1) {

		do {
			n = c1 / 10;
			c1 /= 10;
			k++;
		} while (n != 0);
		n = round(c1 * 10); k--;
	}
	else if (c1 == 0)
		n = 2;
	else if (c1 < 1) {

		do {
			n = c1 * 10;
			c1 *= 10;
			k--;
		} while (n == 0);
		n = round(c1);
	}
	if (n <= 2) {
		u = n * pow(10, k);
	}
	else if (n <= 5) {
		u = 5 * pow(10, k);
	}
	else {
		u = 1 * pow(10, k + 1);
	}
	return u;
}
LPSTR Wide_into_Ascii(LPCWSTR sw)
{
	LPCWSTR LPWSTR_TMP = sw;
	DWORD iSizeStr = wcslen(LPWSTR_TMP) + 1;
	LPSTR lpStrTmp_RESULT = (PCHAR)calloc(iSizeStr, sizeof(CHAR));
	DWORD eResult = WideCharToMultiByte(
		CP_ACP,
		WC_NO_BEST_FIT_CHARS,
		LPWSTR_TMP,
		INFINITE,
		lpStrTmp_RESULT,
		iSizeStr,
		NULL,
		NULL);
	return lpStrTmp_RESULT;
}
void StructInit()
{
	Wnd_Plot.text_ = (LPSTR)"";
	Wnd_Plot.setka.h_setka = 10;
	Wnd_Plot.setka.h5_setka = Wnd_Plot.setka.h_setka * 5; //50
	Wnd_Plot.setka.u5_setka = 2;
	Wnd_Plot.setka.mantissa = 1;
	Wnd_Plot.setka.kxy_zoom = Wnd_Plot.setka.h5_setka / Wnd_Plot.setka.u5_setka;//25
	Wnd_Plot.setka.unit_to_pixel = 1.0 / Wnd_Plot.setka.kxy_zoom;
	Plotting_edges_upd(1);
	Wnd_Plot.setka.LLeft = Wnd_Plot.x_LL / Wnd_Plot.setka.unit_to_pixel;
	Wnd_Plot.setka.RRight = Wnd_Plot.x_RR / Wnd_Plot.setka.unit_to_pixel;
	Wnd_Plot.setka.TTop = Wnd_Plot.y_TT / Wnd_Plot.setka.unit_to_pixel;
	Wnd_Plot.setka.BBottom = Wnd_Plot.y_BB / Wnd_Plot.setka.unit_to_pixel;



	Wnd_Plot.setka.Wide_Vec = 4000 + Wide_of_Screen;
	Wnd_Plot.setka.Left_Wide_Vec = -(Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;
	Wnd_Plot.setka.Right_Wide_Vec = (Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;

	Wnd_Plot.setka.u_HHH = 2;//шаг рисовки - 2 пикселя
	Wnd_Plot.plot.A = -10;
	Wnd_Plot.plot.B = 10;
	Wnd_Plot.plot.H = 0.1;
	SetWindowText(hWndEdit_base, L"sin(x)*abs(x)");//log(x)
	SetWindowText(hWndEdit_A, L"-10");// std::to_wstring(Wnd_Plot.plot.A).c_str()
	SetWindowText(hWndEdit_B, L"10");
	SetWindowText(hWndEdit_H, L"0,1");
	SetWindowText(hWndEdit_Integral, L"Ку-ку епта");

	Wnd_Plot.plot.myvec_xy_picsel.reserve(Wnd_Plot.setka.Wide_Vec + 1);
	Wnd_Plot.plot.myvec_xy.reserve(Wnd_Plot.setka.Wide_Vec + 1);


}
void MousePos(BOOL fl, int x, int y)
{
	MyMouse.Flag_for_mouse = fl;
	MyMouse.Prev_mouse_point.x = x;
	MyMouse.Prev_mouse_point.y = y;
}
void CorrectSetkaPos(int a)
{
	static char count_resizing = 0;


	if (Wnd_Plot.setka.h_setka <= 3)
		Wnd_Plot.setka.h_setka = 3;
	else if (Wnd_Plot.setka.h_setka >= 20)
	{
		count_resizing++;
		Wnd_Plot.setka.h_setka = 10;
		Wnd_Plot.setka.u5_setka = Setka_unit(Wnd_Plot.setka.u5_setka / 2.1);
	}
	else if (Wnd_Plot.setka.h_setka < 10)
	{
		count_resizing++;
		Wnd_Plot.setka.h_setka = 19;
		Wnd_Plot.setka.u5_setka = Setka_unit(Wnd_Plot.setka.u5_setka * 2.1);
	}




	Wnd_Plot.setka.h5_setka = Wnd_Plot.setka.h_setka * 5;
	Wnd_Plot.setka.kxy_zoom = Wnd_Plot.setka.h5_setka / Wnd_Plot.setka.u5_setka;
	Wnd_Plot.setka.unit_to_pixel = 1.0 / Wnd_Plot.setka.kxy_zoom;
	Wnd_Plot.setka.mantissa = floor(log10(Wnd_Plot.setka.u5_setka));
	for (int i = 0; i < Wnd_Plot.plot.myvec_xy_picsel.size(); i++)
	{
		Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_zoom;
		Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_zoom;
	}

	Plotting_edges_upd(2);
	if (Wnd_Plot.setka.LLeft < Wnd_Plot.setka.Left_Wide_Vec || Wnd_Plot.setka.RRight > Wnd_Plot.setka.Right_Wide_Vec || count_resizing > 4)
	{
		Wnd_Plot.setka.Left_Wide_Vec = Wnd_Plot.setka.LLeft - (Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;
		Wnd_Plot.setka.Right_Wide_Vec = Wnd_Plot.setka.LLeft + (Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;
		count_resizing = 0;
		RedrawPlot();
	}
	return;
}
void DrowSetka(HDC dc)
{
	SelectObject(dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(dc, RGB(255, 255, 255));
	Rectangle(dc, 0, 0, Wnd_Plot.sx, Wnd_Plot.sy);
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(214, 214, 214));
	Plotting_edges_upd(0);

	for (int ix = Wnd_Plot.x_LL; ix < Wnd_Plot.x_RR; ix += Wnd_Plot.setka.h_setka) {
		MoveToEx(dc, ix, Wnd_Plot.y_BB, NULL);
		LineTo(dc, ix, Wnd_Plot.y_TT);
	}
	for (int iy = Wnd_Plot.y_BB; iy < Wnd_Plot.y_TT; iy += Wnd_Plot.setka.h_setka) {
		MoveToEx(dc, Wnd_Plot.x_LL, iy, NULL);
		LineTo(dc, Wnd_Plot.x_RR, iy);
	}
	//рисуем большие клетки 
	SetDCPenColor(dc, RGB(150, 150, 150));
	for (int ix = Wnd_Plot.x_LL5; ix < Wnd_Plot.x_RR; ix += Wnd_Plot.setka.h5_setka) {
		MoveToEx(dc, ix, Wnd_Plot.y_BB5, NULL);
		LineTo(dc, ix, Wnd_Plot.y_TT);
	}
	for (int iy = Wnd_Plot.y_BB5; iy < Wnd_Plot.y_TT; iy += Wnd_Plot.setka.h5_setka) {
		MoveToEx(dc, Wnd_Plot.x_LL5, iy, NULL);
		LineTo(dc, Wnd_Plot.x_RR, iy);
	}
	//рисуем оси координат и кромку
	SetDCPenColor(dc, RGB(0, 0, 0));
	MoveToEx(dc, 0, Wnd_Plot.y_TT, NULL);
	LineTo(dc, 0, Wnd_Plot.y_BB);
	MoveToEx(dc, Wnd_Plot.x_LL, 0, NULL);
	LineTo(dc, Wnd_Plot.x_RR, 0);
}
void DrowCounts(HDC dc)
{
	HFONT hFont1 = CreateFont(11, 0, 0, 0, 600, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Lusida Console"));
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(0, 0, 0));
	SelectObject(dc, hFont1);
	SetBkMode(dc, TRANSPARENT);
	//рисуем числa
	//////////////////////////////////////////////////////////////////////
	Plotting_edges_upd(1);
	//уходим в отрицательное крайнее значение графика X
	int mantissa = 0; int zerocount = 0;
	if (abs(Wnd_Plot.setka.mantissa) > 1)
	{
		zerocount = 0;
		mantissa = Wnd_Plot.setka.mantissa;
	}
	else if (Wnd_Plot.setka.mantissa < 0)
	{
		mantissa = 0;
		zerocount = 1;
	}

	double ux = Wnd_Plot.setka.u5_setka * Wnd_Plot.x_LL5 / Wnd_Plot.setka.h5_setka / pow(10, mantissa);;
	TCHAR s[20];
	//проверка на вещественность иди целостность координат
	//if (Wnd_Plot.setka.u5_setka < 1)zerocount = abs(round(log10(Wnd_Plot.setka.u5_setka))) + 1;
	SetTextAlign(dc, TA_TOP | TA_CENTER);
	for (int ix = Wnd_Plot.x_LL5; ix < Wnd_Plot.x_RR - Wnd_Plot.setka.h5_setka; ix += Wnd_Plot.setka.h5_setka) {
		if (mantissa == 0)
			_stprintf(s, L"%.*lf", zerocount, ux);
		else
			_stprintf(s, L"%.*lf^[%d]", zerocount, ux, mantissa);

		if (abs(ix) < Wnd_Plot.setka.h_setka)
		{
			_stprintf(s, L"%d", 0);
			TextOutW(dc, ix + 10, -8, s, _tcslen(s));
		}
		else {

			TextOutW(dc, ix, (Wnd_Plot.y_TT - 10), s, _tcslen(s));//рисуем на топе доп координаты
			MoveToEx(dc, ix, (Wnd_Plot.y_TT - 10), NULL);
			LineTo(dc, ix, (Wnd_Plot.y_TT + 10));

			TextOutW(dc, ix, (Wnd_Plot.y_BB + 20), s, _tcslen(s));
			MoveToEx(dc, ix, (Wnd_Plot.y_BB - 10), NULL);
			LineTo(dc, ix, (Wnd_Plot.y_BB + 10));

			TextOutW(dc, ix, -10, s, _tcslen(s));
			MoveToEx(dc, ix, -10, NULL);
			LineTo(dc, ix, 10);
		}
		ux += Wnd_Plot.setka.u5_setka / pow(10, mantissa);
	}
	//уходим в отрицательное крайнее значение графика Y
	double uy = Wnd_Plot.setka.u5_setka * Wnd_Plot.y_BB5 / Wnd_Plot.setka.h5_setka / pow(10, mantissa);
	SetTextAlign(dc, TA_LEFT);
	for (int iy = Wnd_Plot.y_BB5; iy < Wnd_Plot.y_TT - Wnd_Plot.setka.h5_setka; iy += Wnd_Plot.setka.h5_setka) {
		if (mantissa == 0)
			_stprintf(s, L"%.*lf", zerocount, uy);
		else
			_stprintf(s, L"%.*lf^[%d]", zerocount, uy, mantissa);

		if (abs(iy) < Wnd_Plot.setka.h_setka) {}
		else {
			TextOutW(dc, 15, iy, s, _tcslen(s));
			MoveToEx(dc, 10, iy, NULL);
			LineTo(dc, -10, iy);

			TextOutW(dc, (Wnd_Plot.x_LL + 15), iy, s, _tcslen(s));
			MoveToEx(dc, (Wnd_Plot.x_LL + 10), iy, NULL);
			LineTo(dc, (Wnd_Plot.x_LL - 10), iy);

			TextOutW(dc, (Wnd_Plot.x_RR - 20), (iy + 5), s, _tcslen(s));
			MoveToEx(dc, (Wnd_Plot.x_RR + 10), iy, NULL);
			LineTo(dc, (Wnd_Plot.x_RR - 10), iy);
		}
		uy += Wnd_Plot.setka.u5_setka / pow(10, mantissa);
	}

	//рисуем кромочку
	MoveToEx(dc, Wnd_Plot.x_LL, Wnd_Plot.y_TT, NULL);
	LineTo(dc, Wnd_Plot.x_LL, Wnd_Plot.y_BB);
	MoveToEx(dc, Wnd_Plot.x_RR - 1, Wnd_Plot.y_TT, NULL);
	LineTo(dc, Wnd_Plot.x_RR - 1, Wnd_Plot.y_BB);

	DeleteObject(hFont1);
}
void DrowGraphSmooth(HDC dc)
{
	Gdiplus::Graphics* graph = new (Gdiplus::Graphics)(dc);
	Gdiplus::Bitmap* buffer = new (Gdiplus::Bitmap)(Wnd_Plot.sx, Wnd_Plot.sy);
	Gdiplus::Graphics* myGraphics = new (Gdiplus::Graphics)(buffer);
	myGraphics->SetSmoothingMode(SmoothingModeAntiAlias);
	Pen* myPen = new Pen(Color(1000, 255, 0, 0), 2);
	int i = 0;
	while (Wnd_Plot.plot.myvec_xy[i].x < Wnd_Plot.setka.LLeft)
	{
		++i;
	}
	int j = i;
	while (Wnd_Plot.plot.myvec_xy[j].x < Wnd_Plot.setka.RRight)
	{
		++j;
	}

	for (; i < j; i++)
	{
		if (isnan(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) {
			i++; continue;
		}
		myGraphics->DrawLine(myPen,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i - 1].x)) + Wnd_Plot.setka.sx_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) * (-1) + Wnd_Plot.setka.sy_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i].x)) + Wnd_Plot.setka.sx_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i].y)) * (-1) + Wnd_Plot.setka.sy_center);
	}

	Gdiplus::CachedBitmap  cBitmap(buffer, graph);
	graph->DrawCachedBitmap(&cBitmap, 0, 0);
	delete buffer;
	delete graph;
	delete myGraphics;
	delete myPen;
}
void DrowGraph(HDC dc)
{
	SelectObject(dc, CreatePen(PS_SOLID, 5, RGB(255, 0, 50)));
	int i = 0;
	while (Wnd_Plot.plot.myvec_xy[i].x < Wnd_Plot.setka.LLeft)
	{
		++i;
	}
	int j = i;
	while (Wnd_Plot.plot.myvec_xy[j].x < Wnd_Plot.setka.RRight)
	{
		++j;
	}

	for (; i < j; i++)
	{

		if (isnan(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) {
			i++; continue;
		}
		MoveToEx(dc, Wnd_Plot.plot.myvec_xy_picsel[i - 1].x, Wnd_Plot.plot.myvec_xy_picsel[i - 1].y, NULL);
		LineTo(dc, Wnd_Plot.plot.myvec_xy_picsel[i].x, Wnd_Plot.plot.myvec_xy_picsel[i].y);
	}
}
void Plotting_edges_upd(int draw_h5_inside_or_not)
{
	switch (draw_h5_inside_or_not)
	{
	case 0:
		//КООРДИНАТЫ СЕТОЧНЫХ КРАЕВ
		Wnd_Plot.x_LL = -(Wnd_Plot.setka.sx_center / Wnd_Plot.setka.h_setka + 1) * Wnd_Plot.setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot.y_BB = -((Wnd_Plot.sy - Wnd_Plot.setka.sy_center + 1) / Wnd_Plot.setka.h_setka) * Wnd_Plot.setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot.x_RR = Wnd_Plot.sx - Wnd_Plot.setka.sx_center;//граница правая
		Wnd_Plot.y_TT = Wnd_Plot.setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев большой сетки
		Wnd_Plot.x_LL5 = ((Wnd_Plot.x_LL / Wnd_Plot.setka.h5_setka) - 1) * Wnd_Plot.setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot.y_BB5 = ((Wnd_Plot.y_BB / Wnd_Plot.setka.h5_setka) - 1) * Wnd_Plot.setka.h5_setka;

		break;
	case 1:
		//КООРДИНАТЫ КРАЕВ
		Wnd_Plot.x_LL = -(Wnd_Plot.setka.sx_center);//**приведение типов -  координаты
		Wnd_Plot.y_BB = -(Wnd_Plot.sy - Wnd_Plot.setka.sy_center);//**приведение типов -  координаты
		Wnd_Plot.x_RR = Wnd_Plot.sx - Wnd_Plot.setka.sx_center;//граница правая
		Wnd_Plot.y_TT = Wnd_Plot.setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев
		Wnd_Plot.x_LL5 = ((Wnd_Plot.x_LL / Wnd_Plot.setka.h5_setka) + 1) * Wnd_Plot.setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot.y_BB5 = ((Wnd_Plot.y_BB / Wnd_Plot.setka.h5_setka) + 1) * Wnd_Plot.setka.h5_setka;
		break;
	case 2:
		Plotting_edges_upd(1);
		Wnd_Plot.setka.LLeft = Wnd_Plot.x_LL * Wnd_Plot.setka.unit_to_pixel;
		Wnd_Plot.setka.RRight = Wnd_Plot.x_RR * Wnd_Plot.setka.unit_to_pixel;
		Wnd_Plot.setka.TTop = Wnd_Plot.y_TT * Wnd_Plot.setka.unit_to_pixel;
		Wnd_Plot.setka.BBottom = Wnd_Plot.y_BB * Wnd_Plot.setka.unit_to_pixel;

		break;
	}
	return;
}
void FirstPlotting()
{

	Wnd_Plot.plot.myvec_xy_picsel.clear();
	Wnd_Plot.plot.myvec_xy.clear();
	Pointer point;
	long double y;
	int i = 0;
	for (double x = Wnd_Plot.setka.Left_Wide_Vec;
		x < Wnd_Plot.setka.Right_Wide_Vec;
		x += Wnd_Plot.setka.unit_to_pixel) {
		point.x = x;
		try {
			y = Function_String_to_Double(Wnd_Plot.text_, &x);
			point.y = y;
		}
		catch (double err)
		{
			point.y = err;
		}

		Wnd_Plot.plot.myvec_xy.push_back(point);
		++i;
	}

	for (int i = 0; i < Wnd_Plot.plot.myvec_xy.size(); i++)
	{
		Wnd_Plot.plot.myvec_xy_picsel.push_back({});
		Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_zoom;
		Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_zoom;
	}
}
void RedrawPlot()
{
	if (strlen(Wnd_Plot.text_) == 0) return;
	Wnd_Plot.plot.myvec_xy_picsel.clear();
	Wnd_Plot.plot.myvec_xy.clear();
	Pointer point;
	long double y;
	int i = 0;
	for (double x = Wnd_Plot.setka.Left_Wide_Vec;
		x < Wnd_Plot.setka.Right_Wide_Vec;
		x += Wnd_Plot.setka.unit_to_pixel) {
		point.x = x;
		try {
			y = Function_String_to_Double(Wnd_Plot.text_, &x);
			point.y = y;
		}
		catch (double err)
		{
			point.y = NAN;
		}

		Wnd_Plot.plot.myvec_xy.push_back(point);
		++i;
	}

	for (int i = 0; i < Wnd_Plot.plot.myvec_xy.size(); i++)
	{
		Wnd_Plot.plot.myvec_xy_picsel.push_back({});
		Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_zoom;
		Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_zoom;
	}
}
