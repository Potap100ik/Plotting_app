/*
#pragma once
//манифест для кастомизации
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma warning(disable : 4996)

#include <Windows.h>
#include <tchar.h>
#include <cmath>
#include <string>
#include <vector>
#include <gdiplus.h>
#include <array>
#include "str_to_double.h"
#define MAX_LOADSTRING 100
#define edit_otst1 60
#define edit_otst2 20
using namespace Gdiplus;

HWND
hWnd_main{},
hWnd_plot{},
hWndButton_enter{},
hWndButton_clearPlot{},
hWndButton_clearEdit{},
hWndButton_home{},
hWndEdit_base{},
hWndEdit_A{},
hWndEdit_B{},
hWndEdit_H{};
extern HINSTANCE hInst;/////////////////////////////////////////////////////

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
TCHAR Win_Plot_NAME[MAX_LOADSTRING] = _T("PlotWindow");

int sx{}, sy{};
int sx_center{}, sy_center{};

std::vector<POINT> myvec_xy_picsel{};
struct Pointer {
	double x, y;
};
std::vector<Pointer> myvec_xy{};
//std::vector<double>::iterator it{};
double A = -10, B = 10, H = 0.1, C = max(abs(A), abs(B));/*10// bord_setka = 250;
double Ar = -10, Br = 10, Hr = 0.1, Cr = max(abs(Ar), abs(Br))/*10;

//double kxy_setka = bord_setka / C;//25 - пиксел/у.е - от нуля до границы............................................
///double size_setka = 1 / kxy_setka;//0.04 у.е/пиксел.......................................
//double hxy_setka = kxy_setka * H;//....................................................

int h_setka = 10, h5_setka = h_setka * 5;
double u5_setka = C / 5;//у.е на 5 сеточных клеток
double kxy_setka = h5_setka / u5_setka;


//процедуры классов
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Win_Plot(HWND, UINT, WPARAM, LPARAM);

//вспомогашки
LPSTR Wide_into_Ascii(LPCWSTR sw);
ATOM MyRegisterChildClass();
LPVOID CreateControls(HWND);
void transform(HDC& hdc);
double what_a_fk_its_too_late(double);


double what_a_fk_its_too_late(double include_something)
{
	double u;
	double c1 = include_something;
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



	hWndEdit_base = CreateWindowEx(
		WS_EX_CLIENTEDGE,
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
		L"-10",
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


	CreateWindowEx(0, L"STATIC", L"Поле для уравнения", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 15, 280, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"F(x) = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 42, 40, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"A = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"B = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 40, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"H. = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 140, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	CreateWindowEx(0, L"STATIC", L"\
Писать только так и никак иначе:\n\
- + * / ( )\n\
 'x - икс'\t'pi - 3.1415...'\n\
esp(  )\tabs(  )\tlog(  )\n\
log10(  )\tpow(  )\n\
sin(  )\tcos(  )\ttan(  ),",
WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1, 300, 300, 200, hWnd, nullptr, nullptr, nullptr);

	return 0;
}
ATOM MyRegisterChildClass()
{
	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = Win_Plot_NAME;
	wcex.lpfnWndProc = Win_Plot;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hInstance = hInst;
	return RegisterClassEx(&wcex);
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

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam)
{

	switch (message)
	{
	case WM_CREATE:
		//CreateControls();
		if (!MyRegisterChildClass())
			MessageBox(NULL, _T("НЕ ВЫШЕЛ ГРАФИК ПОГУЛЯТЬ"), _T("Ошибка"), MB_OK);
		hWnd_plot = CreateWindow(
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
		//break;
		return 0;
	case WM_SIZE:

		MoveWindow(hWnd_plot, 400, 0, LOWORD(lParam) - 405, HIWORD(lParam) - 5, 1);
		sx = LOWORD(lParam) - 405;
		sy = HIWORD(lParam) - 5;
		sx_center = sx / 2;
		sy_center = sy / 2;
		//break;
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 	HWNDBUTTON_ENTER:
			try
			{
				if (!myvec_xy_picsel.empty())
				{
					myvec_xy_picsel.clear();
					myvec_xy.clear();
				}
				myvec_xy_picsel.reserve((int)(Br - Ar) / Hr + 1);//+1 - а оно вообше надо?
				myvec_xy.reserve((int)(Br - Ar) / Hr + 1);//+1 - а оно вообше надо?
				std::wstring text{}, Astr{}, Bstr{}, Hstr{};
				GetWindowText(hWndEdit_A, &Astr[0], MAX_PATH);
				GetWindowText(hWndEdit_B, &Bstr[0], MAX_PATH);
				GetWindowText(hWndEdit_H, &Hstr[0], MAX_PATH);
				GetWindowText(hWndEdit_base, &text[0], MAX_PATH);
				/*if (text.empty() || Astr.empty() || Bstr.empty() || Hstr.empty())
				{
					MessageBox(hWnd, L"Введите число!", L"Информация", MB_ICONINFORMATION | MB_OK);
					break;
				}
				Astr.erase(remove(begin(Astr), end(Astr), 0), end(Astr));
				Bstr.erase(remove(begin(Bstr), end(Bstr), 0), end(Bstr));
				Hstr.erase(remove(begin(Hstr), end(Hstr), 0), end(Hstr));
				text.erase(remove(begin(text), end(text), 0), end(text));


				//переводим полученное сообщение из юникода в аски

				LPSTR text_ = Wide_into_Ascii(text.c_str());
				Ar = A = std::stod(Astr);
				Br = B = std::stod(Bstr);
				Hr = H = std::stod(Hstr);
				C = max(abs(A), abs(B));
				POINT point;
				Pointer pt;
				for (double x = Ar; x < Br; x += Hr) {
					point.x = pt.x = x;
					point.y = pt.y = Function_Count(text_, &x);
					//if (isnan(pt.y))continue;
					//if (isinf(pt.y))continue;
					myvec_xy.push_back(pt);
					myvec_xy_picsel.push_back({});
				}

				for (int i = 0; i < myvec_xy.size(); i++)
				{

					myvec_xy_picsel[i].x = myvec_xy[i].x * kxy_setka;
					myvec_xy_picsel[i].y = myvec_xy[i].y * kxy_setka;
				}

				InvalidateRect(hWnd, NULL, TRUE);
			}
			catch (...)
			{
				MessageBox(NULL, L"Число превышает 2 байта!", L"Предупреждение", MB_ICONWARNING | MB_OK);
			}
			//break;
			return 0;
		case	HWNDBUTTON_CLEARPLOT:
			if (!myvec_xy_picsel.empty())
			{
				myvec_xy_picsel.clear();
				myvec_xy.clear();
			}
			h_setka = 10;
			h5_setka = 50;
			u5_setka = C / 5;
			InvalidateRect(hWnd, NULL, TRUE);
			//break;
			return 0;
		case HWNDBUTTON_CLEAREDIT:
			MessageBox(NULL, _T("КНОПКА НЕ ГОТОВА\nЗА РАБОТУ"), _T("Ошибка"), MB_OKCANCEL);
			//break;
			return 0;
		case HWNDBUTTON_HOME:
			sx_center = sx / 2;
			sy_center = sy / 2;
			h_setka = 10;
			u5_setka = what_a_fk_its_too_late(C / 5);
			h5_setka = h_setka * 5;
			kxy_setka = h5_setka / u5_setka;
			for (int i = 0; i < myvec_xy_picsel.size(); i++)
			{
				myvec_xy_picsel[i].x = myvec_xy[i].x * kxy_setka;
				myvec_xy_picsel[i].y = myvec_xy[i].y * kxy_setka;
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
	Pen* myPen;
	Graphics* myGraphics;
	HDC hdc{};
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));;
	RECT rt = { 0, 0, 10, 100 };
	HRGN hRgn;
	HFONT hFont1{};
	HPEN hpen_setk1, hpen_setk2, hpen_black, hpen_plot1;
	HDC memdc;
	HBITMAP membit;
	//double x, y;

	static POINT Prev_mouse_point{};
	static BOOL Flag_for_mouse = FALSE;

	int x_edgelineR, y_edgelineT, x_edgelineL, y_edgelineB;
	int xr, xl, yt, yb;
	double kxy;
	int zerocount;
	double ux, uy;
	TCHAR s[20];
	switch (message)
	{
	case WM_CREATE:
	{
		hpen_setk1 = CreatePen(PS_SOLID, 1, RGB(204, 204, 204));
		hpen_setk2 = CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
		hpen_plot1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hpen_black = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hFont1 = CreateFont(10, 0, 0, 0, FW_NORMAL, 0, 0, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	}
	//break;
	return 0;
	case WM_LBUTTONDOWN:
		Flag_for_mouse = TRUE;
		Prev_mouse_point.x = LOWORD(lParam);
		Prev_mouse_point.y = HIWORD(lParam);

		//break;
		return 0;
	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		//break;
		return 0;
	case WM_MOUSEMOVE:
		if (Flag_for_mouse)
		{

			//hdc = GetDC(hWnd);
			//myGraphics = new Graphics(memdc);
			//myPen = new Pen(Color(200, 255, 0, 0), 3);

			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			sx_center += x - Prev_mouse_point.x;
			sy_center += y - Prev_mouse_point.y;

			//myGraphics->DrawLine(myPen, Prev_mouse_point.x, Prev_mouse_point.y, x, y);

			Prev_mouse_point.x = x;
			Prev_mouse_point.y = y;

			//delete myGraphics;
			//delete myPen;
			EndPaint(hWnd, &ps);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		//break;
		return 0;
	case WM_LBUTTONUP:
		Flag_for_mouse = FALSE;
		//break;
		return 0;
	case WM_MOUSEWHEEL:


		h_setka += GET_WHEEL_DELTA_WPARAM(wParam) / 120;


		if (h_setka <= 3)
			h_setka = 3;
		else if (h_setka >= 20)
		{
			h_setka = 10;
			u5_setka = what_a_fk_its_too_late(u5_setka / 2.1);
		}
		else if (h_setka < 10)
		{
			h_setka = 19;
			u5_setka = what_a_fk_its_too_late(u5_setka * 2.1);

		}
		h5_setka = h_setka * 5;
		kxy_setka = h5_setka / u5_setka;
		for (int i = 0; i < myvec_xy_picsel.size(); i++)
		{
			myvec_xy_picsel[i].x = myvec_xy[i].x * kxy_setka;
			myvec_xy_picsel[i].y = myvec_xy[i].y * kxy_setka;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		//break;
		return 0;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);

		for (int i = 0; i < myvec_xy_picsel.size(); i++)
		{
			myvec_xy_picsel[i].x = myvec_xy[i].x * kxy_setka;
			myvec_xy_picsel[i].y = myvec_xy[i].y * kxy_setka;
		}
		//break;
		return 0;
	case WM_PAINT:///////////////////////////////////////////////////////////////////////////
		memdc = BeginPaint(hWnd, &ps);
		//memdc = CreateCompatibleDC(hdc);//создаем виртуальный контекст для рисования в памяти
		//membit = CreateCompatibleBitmap(hdc, sx, sy);

		//SelectObject(memdc, membit);//в контексте memdc мы будем рисовать на картинке membit
		//hdc = BeginPaint(hWnd, &ps);
		//hdc = BeginPaint(hWnd, &ps);
		transform(memdc);
		hpen_setk1 = CreatePen(PS_SOLID, 1, RGB(204, 204, 204));
		hpen_setk2 = CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
		hpen_plot1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		hpen_black = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		hFont1 = CreateFont(10, 0, 0, 0, 600, 0, 0, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
		//рисуем сеточку
		SelectObject(memdc, hpen_setk1);

		x_edgelineL = (sx_center / h_setka) * h_setka;//**приведение типов -  координаты - расстояние ДО граница левая, от нее начинается рисование вертикальной сетки
		y_edgelineT = (sy_center / h_setka) * h_setka;//**приведение типов -  координаты - расстояние ДО граница верхняя, от нее начинается рисование горизонтальной сетки
		x_edgelineR = sx - sx_center;//граница правая - конец рисования - НЕ координаты - расстояние ДО граница правая
		y_edgelineB = sy - sy_center - 1;//граница нихняя - конец рисования - НЕ координаты - расстояние ДО граница нижняя
		for (int ix = -x_edgelineL; ix < x_edgelineR; ix += h_setka) {
			MoveToEx(memdc, ix, -y_edgelineB, NULL);
			LineTo(memdc, ix, y_edgelineT);
		}
		for (int iy = -y_edgelineB; iy < y_edgelineT; iy += h_setka) {
			MoveToEx(memdc, -x_edgelineL, iy, NULL);
			LineTo(memdc, x_edgelineR, iy);
		}
		//рисуем большие клетки 
		SelectObject(memdc, hpen_setk2);
		x_edgelineL = ((x_edgelineL / h5_setka) + 1) * h5_setka;//переходим в рисование больших квадратов и чисел
		y_edgelineB = ((y_edgelineB / h5_setka) + 1) * h5_setka;
		for (int ix = -x_edgelineL; ix < x_edgelineR; ix += h5_setka) {
			MoveToEx(memdc, ix, -y_edgelineB, NULL);
			LineTo(memdc, ix, y_edgelineT);
		}
		for (int iy = -y_edgelineB; iy < y_edgelineT; iy += h5_setka) {
			MoveToEx(memdc, -x_edgelineL, iy, NULL);
			LineTo(memdc, x_edgelineR, iy);
		}
		//рисуем оси координат
		SelectObject(memdc, hpen_black);
		MoveToEx(memdc, 0, y_edgelineT, NULL);
		LineTo(memdc, 0, -y_edgelineB);
		MoveToEx(memdc, -x_edgelineL, 0, NULL);
		LineTo(memdc, x_edgelineR, 0);
		//рисуем числa
		SelectObject(memdc, hFont1);
		SetTextAlign(memdc, TA_TOP | TA_CENTER);
		//////////////////////////////////////////////////////////////////////
		ux = -u5_setka * x_edgelineL / h5_setka;//уходим в отрицательное крайнее значение
		uy = -u5_setka * y_edgelineB / h5_setka;
		xr = sx - sx_center;
		xl = -sx_center;
		yt = sy_center;
		yb = -(sy - sy_center);


		zerocount = 0;
		if (u5_setka < 1)zerocount = abs(round(log10(u5_setka))) + 1;
		for (int ix = -x_edgelineL; ix < x_edgelineR; ix += h5_setka) {
			_stprintf(s, L"%.*lf", zerocount, ux);
			TextOut(memdc, ix, yt - 10, s, _tcslen(s));
			MoveToEx(memdc, ix, yt - 10, NULL);
			LineTo(memdc, ix, yt + 10);

			TextOut(memdc, ix, yb + 30, s, _tcslen(s));
			MoveToEx(memdc, ix, yb - 10, NULL);
			LineTo(memdc, ix, yb + 10);

			TextOut(memdc, ix, -10, s, _tcslen(s));
			MoveToEx(memdc, ix, -10, NULL);
			LineTo(memdc, ix, 10);
			ux += u5_setka;
		}
		SetTextAlign(memdc, TA_LEFT);
		for (int iy = -y_edgelineB; iy < y_edgelineT; iy += h5_setka) {
			_stprintf(s, L"%.*lf", zerocount, uy);
			TextOut(memdc, xl + 15, iy + 5, s, _tcslen(s));
			MoveToEx(memdc, xl + 10, iy, NULL);
			LineTo(memdc, xl - 10, iy);

			TextOut(memdc, xr - 30, iy + 5, s, _tcslen(s));
			MoveToEx(memdc, xr + 10, iy, NULL);
			LineTo(memdc, xr - 10, iy);

			TextOut(memdc, 15, iy + 5, s, _tcslen(s));
			MoveToEx(memdc, 10, iy, NULL);
			LineTo(memdc, -10, iy);
			uy += u5_setka;

		}
		//рисуем график
		//т.к. график рисуется лишь по пикселам, хотя надо будет потом произвести перестройку в логических координатах
		//х = количество пикселов, соотв. положению х на нормальной системе координат
		if (!myvec_xy_picsel.empty())
		{
			myGraphics = new Graphics(memdc);
			myGraphics->SetSmoothingMode(SmoothingModeAntiAlias);
			myPen = new Pen(Color(1000, 255, 0, 0), 2);
			for (int i = 1; i < myvec_xy_picsel.size(); i++)
			{
				myGraphics->DrawLine(myPen, (int)(myvec_xy_picsel[i - 1].x), (int)(myvec_xy_picsel[i - 1].y), (int)(myvec_xy_picsel[i].x), (int)(myvec_xy_picsel[i].y));
			}
			delete myGraphics;
			delete myPen;
		}

		//BitBlt(hdc, 0, 0, sx, sy, memdc, 0, 0, SRCCOPY);
		//DeleteDC(memdc);
		//DeleteObject(membit);
		EndPaint(hWnd, &ps);
		//break;
		return 0;
	case WM_DESTROY:
		//DeleteObject(hpen_setk1);
		//DeleteObject(hpen_setk2);
		//DeleteObject(hpen_black);
		//DeleteObject(hpen_plot1);
		//DeleteObject(hFont1);
		PostQuitMessage(0);
		return DefWindowProc(hWnd, message, wParam, lParam);
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void transform(HDC& hdc)
{
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, sx, -sy, NULL);//установка  логические размеры - в пикселах - влияет на размеры текста и проч "писельные" переменные
	//У.Е. (логические границы) = (реальные границы[пикс])/(указанное число x_lokal,y_lokal)
	SetViewportExtEx(hdc, sx, sy, NULL);//ОБЛАСТЬ ВЫВОДА  -  физические размеры области вывода в пикселах
	//= локальные поделить на указанные - в у.е.
	SetViewportOrgEx(hdc, sx_center, sy_center, NULL);
}


*/