#pragma once
#include "Help_wnd.h"

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
#define MAX_LOADSTRING 100
#define edit_otst1 60
#define edit_otst2 20
#define MoveToEx(a, x, y, d); MoveToEx(a, x + Wnd_Plot.setka.sx_center, y*(-1) + Wnd_Plot.setka.sy_center, d);
#define LineTo(a, x, y); LineTo(a, x + Wnd_Plot.setka.sx_center, y*(-1) + Wnd_Plot.setka.sy_center);
#define TextOutW(dc, x, y, s, st); TextOutW(dc, x + Wnd_Plot.setka.sx_center, y*(-1) + Wnd_Plot.setka.sy_center, s, st);
// DrawLine(a,x1,y,x2,y2) DrawLine(a,x1 + Wnd_Plot.setka.sx_center,y*(-1) + Wnd_Plot.setka.sy_center,x2 + Wnd_Plot.setka.sx_center,y2*(-1) + Wnd_Plot.setka.sy_center)

using namespace Gdiplus;

//константы
#define MAX_LOADSTRING 100
#define edit_otst1 60
#define edit_otst2 20



//Типы данных
enum CTL_ID {
	HWNDBUTTON_ENTER,
	HWNDBUTTON_CLEARPLOT,
	HWNDBUTTON_CLEAREDIT,
	HWNDBUTTON_HOME,
	HWNDEDIT_BASE,
	HWNDEDIT_A,
	HWNDEDIT_B,
	HWNDEDIT_H
};
struct Pointer {
	double x, y;
};
struct Pointer_int {
	int x, y;
};
typedef struct Plot {
	std::vector<Pointer> myvec_xy_picsel{};//вектор хранит пиксельные координаты x,y 
	std::vector<Pointer> myvec_xy{};//вектор хранит реальные координаты x,y для каждой точки графика
	double A, B, H;//получаемые из окна границы графика
	double C;//
}MyPlot;
typedef struct Setka {
	int sx_center, sy_center;//координаты центра осей координат
	double Ar, Br, Hr, Cr;//при зумировании что-то идет по пизде
	int h_setka, h5_setka;//пиксельные границы для сетки
	double u5_setka;//у.е на 5 сеточных клеток
	double kxy_setka;//коэфф. зума для графика
}MySetka;
typedef struct Wnd_Plot_ {
	HWND hWnd;
	MyPlot plot;
	MySetka setka;
	int sx, sy;//размеры текушщего окна

}MyWnd_Plot;
typedef struct SMouseMove {
	 POINT Prev_mouse_point{};
	 BOOL Flag_for_mouse;
}MouseMove;


//глобальные переменные
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
extern HINSTANCE hInst;/////////////////////////////////////////////////////
HWND hStat;
HWND hWnd_help;
HDC hdc{};
TCHAR Win_Plot_NAME[MAX_LOADSTRING] = _T("PlotWindow");

//оконные создания
int WinMain_(HINSTANCE, HINSTANCE, LPTSTR, int);
LPVOID CreateControls(HWND hWnd);
ATOM MyRegisterChildClass();
//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
//исполнительные функции
double Setka_unit(double get_value);//придвигает кратность юнита сетки графика к 1,2 или 5
LPSTR Wide_into_Ascii(LPCWSTR sw);
void transform(HDC hdc);
void StructInit();
void CorrectSetkaPos();
void MousePos(BOOL, int, int);
void DrowSetka(HDC hdc);
void DrowCounts(HDC hdc);
void DrowGraphSmooth(HDC hdc);
void DrowGraph(HDC hdc);

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
		L"Убрать данные полей",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		edit_otst1, 200, 240, 30,
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_CLEAREDIT),
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
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
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
		L"0.1",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
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


	CreateWindowEx(0, L"STATIC", L"Поле для уравнения", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 15, 280, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"F(x) = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 42, 40, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"A = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"B = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 40, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"H. = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 140, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"Интегралушка ну посчитайся ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 100, 240, 200, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"\
Писать только так и никак иначе:\n\
- + * / ( )\n\
 'x - икс'\t'pi - 3.1415...'\n\
esp(  )\tabs(  )\tlog(  )\n\
log10(  )\tpow(  )\n\
sin(  )\tcos(  )\ttan(  ),",
WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1, 300, 300, 200, hWnd, nullptr, nullptr, nullptr);

	//hStat = CreateWindow(L"static", L"static", WS_VISIBLE,
	//	10, 10, 400, 400, NULL, NULL, NULL, NULL);

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

	switch (message)
	{
	case WM_CREATE:
		CreateControls(hWnd);///////////////////////////////////////////////////////////////////////////////////////
		if (!MyRegisterChildClass())
			MessageBox(NULL, _T("НЕ ВЫШЕЛ ГРАФИК ПОГУЛЯТЬ"), _T("Ошибка"), MB_OK);
		Wnd_Plot.hWnd = CreateWindow(
			Win_Plot_NAME,
			NULL,
			WS_CHILD |
			WS_DLGFRAME | //запрет на изменение размеров дочернего окна
			WS_VISIBLE,
			0, 0, 0, 0,
			hWnd,
			NULL,
			hInst,
			NULL);
		StructInit();
		MousePos(FALSE, 0,0);
		hdc = GetDC(Wnd_Plot.hWnd);
		//break;
		return 0;
	case WM_SIZE:
		Wnd_Plot.sx = LOWORD(lParam) - 405;
		Wnd_Plot.sy = HIWORD(lParam) - 5;
		MoveWindow(Wnd_Plot.hWnd, 400, 0, Wnd_Plot.sx, Wnd_Plot.sy, 1);
		Wnd_Plot.setka.sx_center = Wnd_Plot.sx / 2;
		Wnd_Plot.setka.sy_center = Wnd_Plot.sy / 2;
		//break;
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 	HWNDBUTTON_ENTER:
		{

			if (!Wnd_Plot.plot.myvec_xy_picsel.empty())
			{
				Wnd_Plot.plot.myvec_xy_picsel.clear();
				Wnd_Plot.plot.myvec_xy.clear();
			}
			//Wnd_Plot.plot.myvec_xy_picsel.reserve((int)(Wnd_Plot.setka.Br - Wnd_Plot.setka.Ar) / Wnd_Plot.setka.Hr + 1);//+1 - а оно вообше надо?
			//Wnd_Plot.plot.myvec_xy.reserve((int)(Wnd_Plot.setka.Br - Wnd_Plot.setka.Ar) / Wnd_Plot.setka.Hr + 1);//+1 - а оно вообше надо?
			std::wstring Astr{}, Bstr, Hstr{};
			std::wstring text;//ошибка считывания GetWindowText при вводе log(x)+tan(x)
			text.reserve(MAX_LOADSTRING);
			//char txt[100];
			LPWSTR lptext = (LPWSTR)malloc(MAX_LOADSTRING);
			GetWindowText(hWndEdit_A, &Astr[0], MAX_PATH);
			GetWindowText(hWndEdit_B, &Bstr[0], MAX_PATH);
			GetWindowText(hWndEdit_H, &Hstr[0], MAX_PATH);
			GetWindowText(hWndEdit_base, &text[0], MAX_PATH);

			/*if (text.empty() || Astr.empty() || Bstr.empty() || Hstr.empty())
			{
				MessageBox(hWnd, L"Введите число!", L"Информация", MB_ICONINFORMATION | MB_OK);
				break;
			}*/
			
			//if (Astr.empty() || Bstr.empty() || Hstr.empty() || text.empty())//НЕ ФУРЫЧИТ А ДОЛЖНО, НО КАК????
			//{
			//	MessageBox(hWnd, L"Введите число!", L"Информация", MB_ICONINFORMATION | MB_OK);
			//	break;
			//}
			Astr.erase(remove(begin(Astr), end(Astr), 0), end(Astr));
			Bstr.erase(remove(begin(Bstr), end(Bstr), 0), end(Bstr));
			Hstr.erase(remove(begin(Hstr), end(Hstr), 0), end(Hstr));
			text.erase(remove(text.begin(), text.end(), 0), text.end());


			//переводим полученное сообщение из юникода в аски
			LPSTR text_{};
			try {
				text_ = Wide_into_Ascii(text.c_str());
				Wnd_Plot.setka.Ar = Wnd_Plot.plot.A = std::stod(Astr);
				Wnd_Plot.setka.Br = Wnd_Plot.plot.B = std::stod(Bstr);
				Wnd_Plot.setka.Hr = Wnd_Plot.plot.H = std::stod(Hstr);
			}
			catch (...)
			{
				//MessageBox(NULL, L"Нельзя так числа вводить!", L"Информация", MB_ICONINFORMATION | MB_OK);
				HWND hStatic = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | SS_LEFT | WS_VISIBLE, 305, 120, 70, 40, hWnd, nullptr, nullptr, nullptr);
				std::wstring str = L"Введите\nчисла\n";
				SetWindowText(hStatic, str.c_str());
				Sleep(1000);
				DestroyWindow(hStatic);
				break;
			}
			
			Wnd_Plot.plot.C = max(abs(Wnd_Plot.plot.A), abs(Wnd_Plot.plot.B));
			//Pointer_int point;
			Pointer point;
			Pointer pt;
			IntegerSum = Integrator(Wnd_Plot.setka.Ar, Wnd_Plot.setka.Br, Wnd_Plot.setka.Hr, text_, Function_Count, Simps_method);
			//wstring wstr = std::to_wstring(IntegerSum);
			SetWindowText(hWndEdit_Integral, std::to_wstring(IntegerSum).c_str());
			for (double x = Wnd_Plot.setka.Ar; x < Wnd_Plot.setka.Br; x += Wnd_Plot.setka.Hr) {
				point.x = pt.x = x;
				try {
					point.y = pt.y = Function_Count(text_, &x);
				}
				catch (char* str1)
				{
					pt.y = NAN;
					//if (isnan(pt.y) || isinf(pt.y))//cout << "подтверждено isnan" << endl;
					//pt.y = NAN;

				}
				//point.y = pt.y = Function_Count(text_, &x);

				//if (isnan(pt.y))continue;
				//if (isinf(pt.y))continue;
				Wnd_Plot.plot.myvec_xy.push_back(pt);
			}

			for (int i = 0; i < Wnd_Plot.plot.myvec_xy.size(); i++)
			{
				Wnd_Plot.plot.myvec_xy_picsel.push_back({});
				Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_setka;
				Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_setka;
			}

			//InvalidateRect(hWnd, NULL, TRUE);
			//}
			//catch (...)
			//{
			////MessageBox(NULL, L"Число превышает 2 байта!", L"Предупреждение", MB_ICONWARNING | MB_OK);
			//}
			//break;
		}
			return 0;
		case	HWNDBUTTON_CLEARPLOT:
			if (!Wnd_Plot.plot.myvec_xy_picsel.empty())
			{
				Wnd_Plot.plot.myvec_xy_picsel.clear();
				Wnd_Plot.plot.myvec_xy.clear();
			}
			Wnd_Plot.setka.h_setka = 10;
			Wnd_Plot.setka.h5_setka = 50;
			Wnd_Plot.setka.u5_setka = Wnd_Plot.plot.C / 5;
			InvalidateRect(hWnd, NULL, TRUE);
			//break;
			return 0;
		case HWNDBUTTON_CLEAREDIT:
			MessageBox(NULL, _T("КНОПКА НЕ ГОТОВА\nЗА РАБОТУ"), _T("Ошибка"), MB_OKCANCEL);
			//break;
			return 0;
		case HWNDBUTTON_HOME:
			Wnd_Plot.setka.sx_center = Wnd_Plot.sx / 2;
			Wnd_Plot.setka.sy_center = Wnd_Plot.sy / 2;
			Wnd_Plot.setka.h_setka = 10;
			Wnd_Plot.setka.u5_setka = Setka_unit(Wnd_Plot.plot.C / 5);
			Wnd_Plot.setka.h5_setka = Wnd_Plot.setka.h_setka * 5;
			Wnd_Plot.setka.kxy_setka = Wnd_Plot.setka.h5_setka / Wnd_Plot.setka.u5_setka;
			for (int i = 0; i < Wnd_Plot.plot.myvec_xy_picsel.size(); i++)
			{
				Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_setka;
				Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_setka;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			//break;
			return 0;
		}
		//break;
		return 0;
	case WM_DESTROY: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam)
{
	PAINTSTRUCT  ps;
	HDC memdc;
	HBITMAP membit;
	//HDC hdc{};
	switch (message)
	{
	case WM_CREATE:

	//break;
	return 0;
	case WM_LBUTTONDOWN:
		MousePos(TRUE, LOWORD(lParam), HIWORD(lParam));
		//break;
		return 0;
	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		//break;
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

			//InvalidateRect(hWnd, NULL, TRUE);
		}
		//break;
		return 0;
	case WM_LBUTTONUP:
		MyMouse.Flag_for_mouse = FALSE;
		//break;
		return 0;
	case WM_MOUSEWHEEL:
		Wnd_Plot.setka.h_setka += GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		CorrectSetkaPos();
		//InvalidateRect(hWnd, NULL, TRUE);
		//break;
		return 0;
	case WM_SIZE:
		Wnd_Plot.sx = LOWORD(lParam);
		Wnd_Plot.sy = HIWORD(lParam);

		//break;
		return 0;
	case WM_PAINT:///////////////////////////////////////////////////////////////////////////
		//countpaint++;
		//str = std::to_wstring(countpaint);
		//
		//str += L"\nWnd_Plot.setka.sy_center: ";
		//str += std::to_wstring(Wnd_Plot.setka.sy_center);
		//str += L"\nWnd_Plot.sy: ";
		//str += std::to_wstring(Wnd_Plot.sy);
		//if (Wnd_Plot.setka.sy_center < 50)
		//{
		//	str += L"\nWOWOWOWOWOOWOWOWWOWOOWOWOWooooooo ";
		//}
		//SetWindowText(hStat, str.c_str());
		//hdc = BeginPaint(Wnd_Plot.hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);//создаем виртуальный контекст для рисования в памяти
		membit = CreateCompatibleBitmap(hdc, Wnd_Plot.sx, Wnd_Plot.sy);//с чем компэтибл

		SelectObject(memdc, membit);//в контексте memdc мы будем рисовать на картинке membit
		DrowSetka(memdc);
		DrowCounts(memdc);
		if (!Wnd_Plot.plot.myvec_xy_picsel.empty())
		{
			DrowGraphSmooth(memdc);
			//DrowGraph(memdc);
		}
		BitBlt(hdc, 0, 0, Wnd_Plot.sx * 2, Wnd_Plot.sy * 2, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(membit);
		Sleep(100);
	   // EndPaint(Wnd_Plot.hWnd, &ps);
		//break;
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
void transform(HDC hdc)
{
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, Wnd_Plot.sx, -Wnd_Plot.sy, NULL);//установка  логические размеры - в пикселах - влияет на размеры текста и проч "писельные" переменные
	//У.Е. (логические границы) = (реальные границы[пикс])/(указанное число x_lokal,y_lokal)
	SetViewportExtEx(hdc, Wnd_Plot.sx, Wnd_Plot.sy, NULL);//ОБЛАСТЬ ВЫВОДА  -  физические размеры области вывода в пикселах
	//= локальные поделить на указанные - в у.е.
	SetViewportOrgEx(hdc, Wnd_Plot.setka.sx_center, Wnd_Plot.setka.sy_center, NULL);
}
void StructInit()
{
	Wnd_Plot.setka.h_setka = 10;
	Wnd_Plot.setka.h5_setka = 50; //h_setka * 5
	Wnd_Plot.setka.u5_setka = 2;
	Wnd_Plot.setka.kxy_setka = 25;//h5_setka / u5_setka
	Wnd_Plot.setka.Ar = -10;
	Wnd_Plot.setka.Br = 10;
	Wnd_Plot.setka.Cr = 10;
	Wnd_Plot.setka.Hr = 0.1;
	
}
void MousePos(BOOL fl, int x, int y)
{
	MyMouse.Flag_for_mouse = fl;
	MyMouse.Prev_mouse_point.x = x;
	MyMouse.Prev_mouse_point.y = y;
}
void CorrectSetkaPos()
{
	if (Wnd_Plot.setka.h_setka <= 3)
		Wnd_Plot.setka.h_setka = 3;
	else if (Wnd_Plot.setka.h_setka >= 20)
	{
		Wnd_Plot.setka.h_setka = 10;
		Wnd_Plot.setka.u5_setka = Setka_unit(Wnd_Plot.setka.u5_setka / 2.1);
	}
	else if (Wnd_Plot.setka.h_setka < 10)
	{
		Wnd_Plot.setka.h_setka = 19;
		Wnd_Plot.setka.u5_setka = Setka_unit(Wnd_Plot.setka.u5_setka * 2.1);

	}
	Wnd_Plot.setka.h5_setka = Wnd_Plot.setka.h_setka * 5;
	Wnd_Plot.setka.kxy_setka = Wnd_Plot.setka.h5_setka / Wnd_Plot.setka.u5_setka;
	for (int i = 0; i < Wnd_Plot.plot.myvec_xy_picsel.size(); i++)
	{
		Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_setka;
		Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_setka;
	}
	return;
}
void DrowSetka(HDC dc)
{
	SelectObject(dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(dc, RGB(255, 255, 255));
	Rectangle(dc, 0, 0, Wnd_Plot.sx, Wnd_Plot.sy);
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(204, 204, 204));
	//КООРДИНАТЫ КРАЕВ
	const int x_LL = -(Wnd_Plot.setka.sx_center / Wnd_Plot.setka.h_setka) * Wnd_Plot.setka.h_setka;//**приведение типов -  координаты
	const int y_BB = -((Wnd_Plot.sy - Wnd_Plot.setka.sy_center) / Wnd_Plot.setka.h_setka) * Wnd_Plot.setka.h_setka;//**приведение типов -  координаты
	const int x_RR = Wnd_Plot.sx - Wnd_Plot.setka.sx_center;//граница правая
	const int y_TT = Wnd_Plot.setka.sy_center;//граница нихняя
	for (int ix = x_LL; ix < x_RR; ix += Wnd_Plot.setka.h_setka) {
		MoveToEx(dc, ix, y_BB, NULL);
		LineTo(dc, ix, y_TT);
	}
	for (int iy = y_BB; iy < y_TT; iy += Wnd_Plot.setka.h_setka) {
		MoveToEx(dc, x_LL, iy, NULL);
		LineTo(dc, x_RR, iy);
	}
	//рисуем большие клетки 
	SetDCPenColor(dc, RGB(150, 150, 150));

	const int x_LL5 = ((x_LL / Wnd_Plot.setka.h5_setka) - 1) * Wnd_Plot.setka.h5_setka;//переходим в рисование больших квадратов и чисел
	const int y_BB5 = ((y_BB / Wnd_Plot.setka.h5_setka) - 1) * Wnd_Plot.setka.h5_setka;
	for (int ix = x_LL5; ix < x_RR; ix += Wnd_Plot.setka.h5_setka) {
		MoveToEx(dc, ix, y_BB5, NULL);
		LineTo(dc, ix, y_TT);
	}
	for (int iy = y_BB5; iy < y_TT; iy += Wnd_Plot.setka.h5_setka) {
		MoveToEx(dc, x_LL5, iy, NULL);
		LineTo(dc, x_RR, iy);
	}
	//рисуем оси координат
	SetDCPenColor(dc, RGB(0, 0, 0));
	MoveToEx(dc, 0, y_TT, NULL);
	LineTo(dc, 0, y_BB);
	MoveToEx(dc, x_LL, 0, NULL);
	LineTo(dc, x_RR, 0);
}

void DrowCounts(HDC dc)
{
	HFONT hFont1 = CreateFont(10, 0, 0, 0, 600, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(0, 0, 0));
	SelectObject(dc, hFont1);
	SetBkMode(dc, TRANSPARENT);
	//рисуем числa
	//////////////////////////////////////////////////////////////////////
	//КООРДИНАТЫ КРАЕВ
	const int x_LL = -(Wnd_Plot.setka.sx_center / Wnd_Plot.setka.h_setka) * Wnd_Plot.setka.h_setka;//**приведение типов -  координаты
	const int y_BB = -((Wnd_Plot.sy - Wnd_Plot.setka.sy_center) / Wnd_Plot.setka.h_setka) * Wnd_Plot.setka.h_setka;//**приведение типов -  координаты
	const int x_RR = Wnd_Plot.sx - Wnd_Plot.setka.sx_center;//граница правая
	const int y_TT = Wnd_Plot.setka.sy_center;//граница нихняя
	//расстояние от центра СК до отрицательных краев
	const int x_LL5 = ((x_LL / Wnd_Plot.setka.h5_setka)+1) * Wnd_Plot.setka.h5_setka;//переходим в рисование больших квадратов и чисел
	const int y_BB5 = ((y_BB / Wnd_Plot.setka.h5_setka)+1) * Wnd_Plot.setka.h5_setka;

	//уходим в отрицательное крайнее значение графика X
	double ux = Wnd_Plot.setka.u5_setka * x_LL5 / Wnd_Plot.setka.h5_setka;
	TCHAR s[20];
	int zerocount = 0;//проверка на вещественность иди целостность координат
	if (Wnd_Plot.setka.u5_setka < 1)zerocount = abs(round(log10(Wnd_Plot.setka.u5_setka))) + 1;
	SetTextAlign(dc, TA_TOP | TA_CENTER);
	INT TERPILA;
	for (int ix = x_LL5; ix < x_RR - Wnd_Plot.setka.h5_setka; ix += Wnd_Plot.setka.h5_setka) {
		_stprintf(s, L"%.*lf", zerocount, ux);

		TextOutW(dc, ix, (y_TT - 10), s, _tcslen(s));//рисуем на топе доп координаты
		MoveToEx(dc, ix, (y_TT - 10), NULL);
		LineTo(dc, ix, (y_TT + 10));

		//КОСТЫЛИ ДЛЯ DEFINE - НУ УСТАЛ Я ИСКАТЬ КАК С ЭТИМ БОРОТЬСЯ -- 2 ЧАСА ушло на понимание того, что чтоб сработал макрос, надо поставить скобочки
		TextOutW(dc, ix, (y_BB + 20), s, _tcslen(s));
		MoveToEx(dc, ix, (y_BB - 10), NULL);
		LineTo(dc, ix, (y_BB + 10));

		TextOutW(dc, ix, -10, s, _tcslen(s));
		MoveToEx(dc, ix, -10, NULL);
		LineTo(dc, ix, 10);
		ux += Wnd_Plot.setka.u5_setka;
	}
	//уходим в отрицательное крайнее значение графика Y
	double uy = Wnd_Plot.setka.u5_setka * y_BB5 / Wnd_Plot.setka.h5_setka;
	SetTextAlign(dc, TA_LEFT| TA_CENTER);
	for (int iy = y_BB5; iy < y_TT - Wnd_Plot.setka.h5_setka; iy += Wnd_Plot.setka.h5_setka) {
		_stprintf(s, L"%.*lf", zerocount, uy);

		TextOutW(dc, 15, iy, s, _tcslen(s));
		MoveToEx(dc, 10, iy, NULL);
		LineTo(dc, -10, iy);

		TextOutW(dc, (x_LL + 15), iy, s, _tcslen(s));
		MoveToEx(dc, (x_LL + 10), iy, NULL);
		LineTo(dc, (x_LL - 10), iy);

		TextOutW(dc, (x_RR - 20), (iy + 5), s, _tcslen(s));
		MoveToEx(dc, (x_RR + 10), iy, NULL);
		LineTo(dc, (x_RR - 10), iy);
		uy += Wnd_Plot.setka.u5_setka;
	}
	DeleteObject(hFont1);
}
void DrowGraphSmooth(HDC dc)
{
	Graphics* myGraphics = new Graphics(dc);
	myGraphics->SetSmoothingMode(SmoothingModeAntiAlias);
	Pen* myPen = new Pen(Color(1000, 255, 0, 0), 2);
	for (int i = 1; i < Wnd_Plot.plot.myvec_xy_picsel.size(); i++)
	{
		if (isnan(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) {
			i++; continue;
		}
		myGraphics->DrawLine(myPen, 
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i - 1].x)) + Wnd_Plot.setka.sx_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) * (-1) + Wnd_Plot.setka.sy_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i].x))		+ Wnd_Plot.setka.sx_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i].y))		* (-1) + Wnd_Plot.setka.sy_center);
	}
	delete myGraphics;
	delete myPen;
}
void DrowGraph(HDC dc)
{
	SelectObject(dc, CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));
	for (int i = 1; i < Wnd_Plot.plot.myvec_xy_picsel.size(); i++)
	{

		if (isnan(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) {
			i++; continue;
		}
		MoveToEx(dc, Wnd_Plot.plot.myvec_xy_picsel[i - 1].x, Wnd_Plot.plot.myvec_xy_picsel[i - 1].y, NULL);
		LineTo(dc, Wnd_Plot.plot.myvec_xy_picsel[i].x, Wnd_Plot.plot.myvec_xy_picsel[i].y);
	}
}