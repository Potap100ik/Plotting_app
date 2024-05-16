#include "../Main_files/STD/stdafx.h"
#include "../Main_files/STD/Standard.h"

TCHAR Win_Plot_NAME[MAX_LOADSTRING] = _T("PlotWindow");

//extern - так делать нельзя, но я по-другому пока не умею
extern MouseMove MyMouse;
extern HDC hdc;
extern double IntegerSum;
extern HINSTANCE hInst;
extern MyWnd_Plot* Wnd_Plot;
Ploting_struct Myplot{};
Integral_struct Myintegr{};
extern HWND
hWndButton_enter,
hWndButton_clearPlot,
hWndButton_clearEdit,
hWndButton_home,
hWndEdit_base,
hWndEdit_A,
hWndEdit_B,
hWndEdit_H,
hWndEdit_Integral;


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
	Gdiplus::Bitmap* img{};
	Gdiplus::Graphics* graph{};
	std::wstring text;
	switch (message)
	{
	case WM_CREATE:
		CreateControls(hWnd);
		if (!MyRegisterChildClass())
			MessageBox(NULL, _T("НЕ ВЫШЕЛ ГРАФИК ПОГУЛЯТЬ"), _T("Ошибка"), MB_OK);
		Wnd_Plot->hWnd = CreateWindow(Win_Plot_NAME, NULL, WS_CHILD | WS_DLGFRAME | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		StructInit(Wnd_Plot, Myplot, Myintegr);
		MousePos(FALSE, 0, 0, Wnd_Plot);
		return 0;
	case WM_SIZE:
		Wnd_Plot->sx = LOWORD(lParam) - 405;
		Wnd_Plot->sy = HIWORD(lParam) - 5;
		MoveWindow(Wnd_Plot->hWnd, 400, 0, Wnd_Plot->sx, Wnd_Plot->sy, 1);
		Wnd_Plot->setka.sx_center = Wnd_Plot->sx / 2;
		Wnd_Plot->setka.sy_center = Wnd_Plot->sy / 2;
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
			Wnd_Plot->text_ = Wide_into_Ascii(text.c_str());
			if (strlen(Wnd_Plot->text_) == 0)
			{
				MessageBox(hWnd, L"Уважаемый прогер\nГде ваша функция?", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
				return 0;
			}

			Plotting_edges_upd(2, Wnd_Plot, Myplot);
			FirstPlotting(Wnd_Plot, Myplot);
			UpdateWindow(Wnd_Plot->hWnd);
			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);

			return 0;
		case	HWNDBUTTON_CLEARPLOT:
			Myplot.picsel.clear();
			Myplot.myvec_xy.clear();
			Wnd_Plot->text_ = (LPSTR)"";
			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);
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
			Wnd_Plot->text_ = Wide_into_Ascii(text.c_str());
			try
			{
				Myintegr.A = std::stod(Astr);
				Myintegr.B = std::stod(Bstr);
				Myintegr.H = std::stod(Hstr);
			}
			catch (...)
			{
				MessageBox(hWnd, L"Уважаемый прогер\nГде числа?!!!\nИз чего интегралы строить", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
				return 0;
			}
			Astr.clear(); Bstr.clear(); Hstr.clear(); text.clear();
			if (Myintegr.A == Myintegr.B || Myintegr.H == 0)
			{
				SetWindowText(hWndEdit_Integral, L"Интеграл равен нулю");
				return 0;
			}
			if (Myintegr.A > Myintegr.B || Myintegr.H == 0 || Myintegr.H > (Myintegr.B - Myintegr.A))
			{
				MessageBox(hWnd, L"Уважаемый прогер\nВ числах беспорядки!!!\nИз чего интегралы строить", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
				return 0;
			}
			if (strlen(Wnd_Plot->text_) == 0)
			{
				MessageBox(hWnd, L"Уважаемый прогер\nГде ваша функция?", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
				return 0;
			}
			try {
				IntegerSum = Integrator(Myintegr.A, Myintegr.B, Myintegr.H, Wnd_Plot->text_, Function_String_to_Double, Simps_method);
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
			Wnd_Plot->setka.sx_center = Wnd_Plot->sx / 2;
			Wnd_Plot->setka.sy_center = Wnd_Plot->sy / 2;
			Wnd_Plot->setka.h_setka = 10;
			Wnd_Plot->setka.u5_setka = 2;
			Wnd_Plot->setka.mantissa = 1;
			Wnd_Plot->setka.h5_setka = Wnd_Plot->setka.h_setka * 5;
			Wnd_Plot->setka.kxy_zoom = Wnd_Plot->setka.h5_setka / Wnd_Plot->setka.u5_setka;
			Wnd_Plot->setka.unit_to_pixel = 1.0 / Wnd_Plot->setka.kxy_zoom;
			Plotting_edges_upd(2, Wnd_Plot, Myplot);
			RedrawPlot(Wnd_Plot, Myplot);
			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);
			return 0;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		img = Gdiplus::Bitmap::FromFile(L"1.png");
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
		MousePos(TRUE, LOWORD(lParam), HIWORD(lParam), Wnd_Plot);
		return 0;
	case WM_MOUSEMOVE:
		if (MyMouse.Flag_for_mouse)
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			Wnd_Plot->setka.sx_center += x - MyMouse.Prev_mouse_point.x;
			Wnd_Plot->setka.sy_center += y - MyMouse.Prev_mouse_point.y;

			MyMouse.Prev_mouse_point.x = x;
			MyMouse.Prev_mouse_point.y = y;

			Plotting_edges_upd(2, Wnd_Plot, Myplot);
			if (Wnd_Plot->setka.LLeft < Wnd_Plot->setka.Left_Wide_Vec || Wnd_Plot->setka.RRight > Wnd_Plot->setka.Right_Wide_Vec)
			{
				Wnd_Plot->setka.Left_Wide_Vec = Wnd_Plot->setka.LLeft - (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
				Wnd_Plot->setka.Right_Wide_Vec = Wnd_Plot->setka.LLeft + (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
				RedrawPlot(Wnd_Plot, Myplot);
			}

			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);
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
		int a = Wnd_Plot->setka.h_setka;
		Wnd_Plot->setka.h_setka += GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		/*{
			if (Wnd_Plot->setka.sx_center > Wnd_Plot->sx / 2)
				Wnd_Plot->setka.sx_center += GET_WHEEL_DELTA_WPARAM(wParam);
			else if (Wnd_Plot->setka.sx_center == Wnd_Plot->sx / 2) {}
			else
				Wnd_Plot->setka.sx_center -= GET_WHEEL_DELTA_WPARAM(wParam);

			if (Wnd_Plot->setka.sy_center > Wnd_Plot->sy / 2)
				Wnd_Plot->setka.sy_center += GET_WHEEL_DELTA_WPARAM(wParam);
			else if (Wnd_Plot->setka.sy_center == Wnd_Plot->sy / 2) {}
			else
				Wnd_Plot->setka.sy_center -= GET_WHEEL_DELTA_WPARAM(wParam);
		}*/
		CorrectSetkaPos(0, Wnd_Plot, Myplot);
		InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);
	}
	return 0;
	case WM_SIZE:
		Wnd_Plot->sx = LOWORD(lParam);
		Wnd_Plot->sy = HIWORD(lParam);
		return 0;
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
	{
		SimpleTimer timer;
		hdc2 = BeginPaint(Wnd_Plot->hWnd, &ps2);
		memdc = CreateCompatibleDC(hdc2);
		membit = CreateCompatibleBitmap(hdc2, Wnd_Plot->sx, Wnd_Plot->sy);
		SelectObject(memdc, membit);
		DrowSetka(memdc, Wnd_Plot, Myplot);
		DrowCounts(memdc, Wnd_Plot, Myplot);
		if (!Myplot.picsel.empty())
		{
			DrowGraphSmooth(memdc, Wnd_Plot, Myplot);
			//DrowGraph(memdc, Wnd_Plot);оставим для экспериментов - рисование без GDI+
		}
		BitBlt(hdc2, 0, 0, Wnd_Plot->sx * 2, Wnd_Plot->sy * 2, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(membit);
		EndPaint(Wnd_Plot->hWnd, &ps2);
	}
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return DefWindowProc(hWnd, message, wParam, lParam);
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
