#include "../Main_files/STD/stdafx.h"
#include "../Main_files/STD/Standard.h"

WCHAR Win_Plot_NAME[MAX_LOADSTRING] = L"PlotWindow";
WCHAR Integral_Wnd_NAME[MAX_LOADSTRING] = L"Integral_Wnd";



//extern - так делать нельзя, но я по-другому пока не умею
extern HINSTANCE hInst;
MouseMove MyMouse;//
HDC hdc;
MyWnd_Plot* Wnd_Plot{};
Ploting_struct Myplot{};
Integral_struct Myintegr{};

HWND
hWndButton_enter{},
hWndButton_clearPlot{},
hWndButton_Integral{},
hWndButton_home{},
hWndEdit_base{},
hWndEdit_A{},
hWndEdit_B{},
hWndEdit_H{},
hWndEdit_Integral{},
hWndEdit_Erroors{},
hWnd_Integer_Wnd{};

LPVOID CreateControls(HWND hWnd)
{



	hWndButton_enter = CreateWindowEx(
		0,
		L"BUTTON",
		L"Построить график",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 1),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 2),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 3),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 4),
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_ENTER),
		nullptr, nullptr);
	if (!hWndButton_enter)
		MessageBox(NULL, L"hWndButton_enter", L"Ошибка", MB_OK);

	hWndButton_clearPlot = CreateWindowEx(
		0,
		L"BUTTON",
		L"Убрать данные графика",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_CLEARPLOT, 1),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_CLEARPLOT, 2),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_CLEARPLOT, 3),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_CLEARPLOT, 4),
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_CLEARPLOT),
		nullptr, nullptr);
	if (!hWndButton_clearPlot)
		MessageBox(NULL, L"hWndButton_clearPlot", L"Ошибка", MB_OK);

	hWndButton_Integral = CreateWindowEx(
		0,
		L"BUTTON",
		L"",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_INTEGER, 1),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_INTEGER, 2),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_INTEGER, 3),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_INTEGER, 4),
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_INTEGER),
		nullptr, nullptr);
	if (!hWndButton_Integral)
		MessageBox(NULL, L"hWndButton_clearEdit", L"Ошибка", MB_OK);

	hWndButton_home = CreateWindowEx(
		0,
		L"BUTTON",
		L"",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_HOME, 1),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_HOME, 2),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_HOME, 3),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_HOME, 4),
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_HOME),
		nullptr, nullptr);
	if (!hWndButton_Integral)
		MessageBox(NULL, L"hWndButton_clearEdit", L"Ошибка", MB_OK);



	hWndEdit_base = CreateWindow(
		L"EDIT",
		L"log(x)",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL  | ES_LEFT | ES_MULTILINE,
		Get_EDIT_FUNC_koordinates(1),
		Get_EDIT_FUNC_koordinates(2),
		Get_EDIT_FUNC_koordinates(3),
		Get_EDIT_FUNC_koordinates(4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_BASE),
		nullptr, nullptr);

	if (!hWndEdit_base)
		MessageBox(NULL, L"hWndEdit_base", L"Ошибка", MB_OK);
	SetEditTypingCenter(hWndEdit_base, Get_EDIT_FUNC_koordinates);


	hWndEdit_A = CreateWindowEx(
		0,
		L"EDIT",
		L"1",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE,
		Get_EDIT_ABH_koordinates('A', 1),
		Get_EDIT_ABH_koordinates('A', 2),
		Get_EDIT_ABH_koordinates('A', 3),
		Get_EDIT_ABH_koordinates('A', 4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_A),
		nullptr, nullptr);
	if (!hWndEdit_A)
		MessageBox(NULL, L"hWndEdit_A", L"Ошибка", MB_OK);
	SetEditTypingCenter(hWndEdit_A, 'A', Get_EDIT_ABH_koordinates);


	hWndEdit_B = CreateWindowEx(
		0,
		L"EDIT",
		L"10",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE,
		Get_EDIT_ABH_koordinates('B', 1),
		Get_EDIT_ABH_koordinates('B', 2),
		Get_EDIT_ABH_koordinates('B', 3),
		Get_EDIT_ABH_koordinates('B', 4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_B),
		nullptr, nullptr);
	if (!hWndEdit_B)
		MessageBox(NULL, L"hWndEdit_B", L"Ошибка", MB_OK);
	SetEditTypingCenter(hWndEdit_B, 'B', Get_EDIT_ABH_koordinates);

	hWndEdit_H = CreateWindowEx(
		0,
		L"EDIT",
		L"0,1",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE,
		Get_EDIT_ABH_koordinates('H', 1),
		Get_EDIT_ABH_koordinates('H', 2),
		Get_EDIT_ABH_koordinates('H', 3),
		Get_EDIT_ABH_koordinates('H', 4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_H),
		nullptr, nullptr);
	if (!hWndEdit_H)
		MessageBox(NULL, L"hWndEdit_H", L"Ошибка", MB_OK);
	SetEditTypingCenter(hWndEdit_H, 'H', Get_EDIT_ABH_koordinates);


	hWndEdit_Integral = CreateWindowEx(
		0,
		L"EDIT",
		L"Интеграл появится тут",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE,
		Get_EDIT_INTEGRAL_koordinates(1),
		Get_EDIT_INTEGRAL_koordinates(2),
		Get_EDIT_INTEGRAL_koordinates(3),
		Get_EDIT_INTEGRAL_koordinates(4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_INTEGER),
		nullptr, nullptr);
	if (!hWndEdit_Integral)
		MessageBox(NULL, L"hWndEdit_Integral", L"Ошибка", MB_OK);
	SetEditTypingCenter(hWndEdit_Integral, Get_EDIT_INTEGRAL_koordinates);


	hWndEdit_Erroors = CreateWindowEx(
		0,
		L"EDIT",
		L"Ошибки:",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE,
		Get_EDIT_ERRORS_koordinates(1),
		Get_EDIT_ERRORS_koordinates(2),
		Get_EDIT_ERRORS_koordinates(3),
		Get_EDIT_ERRORS_koordinates(4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_ERROR),
		nullptr, nullptr);
	if (!hWndEdit_Integral)
		MessageBox(NULL, L"hWndEdit_Erroors", L"Ошибка", MB_OK);
	//SetEditTypingCenter(hWndEdit_Erroors, Get_EDIT_ERRORS_koordinates);
	return 0;
}


ATOM Register_Integer_Wnd_Class()
{
	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wcex.lpszClassName = Integral_Wnd_NAME;
	wcex.lpfnWndProc = Integral_Wnd_Proc;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hInstance = hInst;
	return RegisterClassEx(&wcex);
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
	static Gdiplus::Bitmap* img_side{};
	static Gdiplus::Bitmap* img_integral{};
	static Gdiplus::Bitmap* img_home{};
	static int img_height;
	static int img_width;
	Gdiplus::Graphics* graph{};
	std::wstring text;

	static HBRUSH defaultbrush;
	static HBRUSH selectbrush;
	static HBRUSH hotbrush;


	//static Gdiplus::Bitmap* img_for_BASE_edit;
	//static Gdiplus::Bitmap* img_for_A_edit;
	//static Gdiplus::Bitmap* img_for_B_edit;
	//static Gdiplus::Bitmap* img_for_H_edit;
	//static Gdiplus::Bitmap* img_for_INTEGAL_edit;
	//static Gdiplus::Bitmap* img_for_ERRORS_edit;
	//static Gdiplus::Bitmap* img_for_MEMORY_CARD;



	//static Gdiplus::Bitmap* img_for_ENTER_btn[3];
	//static Gdiplus::Bitmap* img_for_HOME_btn[3];
	//static Gdiplus::Bitmap* img_for_CLEAR_btn[3];
	//static Gdiplus::Bitmap* img_for_INTEGRAL_btn[3];

	static HFONT hFont;
	switch (message)
	{
	case WM_CREATE:
	{

		Wnd_Plot = (MyWnd_Plot*)malloc(sizeof(Wnd_Plot_struct));
		CreateControls(hWnd);
		if (!MyRegisterChildClass())
			MessageBox(NULL, L"НЕ ВЫШЕЛ ГРАФИК ПОГУЛЯТЬ", L"Ошибка", MB_OK);
		if (!Register_Integer_Wnd_Class())
			MessageBox(NULL, L"НЕ ВЫШЕЛ ПУШНЫЙ ГРАФИК ПОГУЛЯТЬ", L"Ошибка", MB_OK);
		Wnd_Plot->hWnd = CreateWindow(Win_Plot_NAME, NULL, WS_CHILD | WS_DLGFRAME | WS_VISIBLE, 0, 0, 0, 0, hWnd, NULL, hInst, NULL);
		StructInit(Wnd_Plot, Myplot, Myintegr);
		MousePos(FALSE, 0, 0, Wnd_Plot, MyMouse);
		img_side = Gdiplus::Bitmap::FromFile(Side_image_adress);
		img_height = img_side->GetHeight() * (Right_img_edge) / img_side->GetWidth();
		img_width = Right_img_edge;
		img_home = Gdiplus::Bitmap::FromFile(Image_Home_btn);
		img_integral = Gdiplus::Bitmap::FromFile(Image_INTEGRAL_btn);


		/*img_for_BASE_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_BASE);
		img_for_A_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_A);
		img_for_B_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_B);
		img_for_H_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_H);
		img_for_INTEGAL_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_INTEGRAL);
		img_for_ERRORS_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_ERRORS);
		img_for_MEMORY_CARD = Gdiplus::Bitmap::FromFile(IMAGE_FOR_MEMORY_CARD);

		img_for_ENTER_btn[0] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_ENTER[0]);
		img_for_ENTER_btn[1] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_ENTER[1]);
		img_for_ENTER_btn[2] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_ENTER[2]);

		img_for_CLEAR_btn[0] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_CLEAR[0]);
		img_for_CLEAR_btn[1] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_CLEAR[1]);
		img_for_CLEAR_btn[2] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_CLEAR[2]);

		img_for_HOME_btn[0] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_HOME[0]);
		img_for_HOME_btn[1] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_HOME[1]);
		img_for_HOME_btn[2] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_HOME[2]);

		img_for_INTEGRAL_btn[0] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_INTEGRAL[0]);
		img_for_INTEGRAL_btn[1] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_INTEGRAL[1]);
		img_for_INTEGRAL_btn[2] = Gdiplus::Bitmap::FromFile(IMAGE_FOR_BUTTONS_INTEGRAL[2]);*/



		LOGFONT lf;
		
		memset(&lf, 0, sizeof(LOGFONT));
		lstrcpy(lf.lfFaceName, L"Times new roman"); // Имя шрифта.
		lf.lfWeight = FONTWIDTH;
		lf.lfHeight = FONTSIZE; // По высоте.
		hFont = CreateFontIndirect(&lf);
		//delete &lf;

	}return 0;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = MINIMUM_BASE_WND_WIDTH;
		lpMMI->ptMinTrackSize.y = MINIMUM_BASE_WND_HEIGHT;

	}return 0;

	case WM_SIZE:
	{
		printf("sx = %5d sy = %5d\n", LOWORD(lParam), HIWORD(lParam));
		Wnd_Plot->sx = LOWORD(lParam) - Left_Plot_Edge - 5;
		Wnd_Plot->sy = HIWORD(lParam) - 5;
		MoveWindow(Wnd_Plot->hWnd, Left_Plot_Edge, 0, Wnd_Plot->sx, Wnd_Plot->sy, 1);
		Wnd_Plot->setka.sx_center = Wnd_Plot->sx / 2;
		Wnd_Plot->setka.sy_center = Wnd_Plot->sy / 2;

	}return 0;

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;
		switch (some_item->code)
		{
		case NM_CUSTOMDRAW:
		
			if (some_item->hwndFrom == hWndButton_enter)
				CustomPushBTN(hWnd, some_item, selectbrush, hotbrush, defaultbrush, GRADIENT);
				//CustomBTN_SET_IMAGE(hWnd, some_item, img_for_ENTER_btn);
			else if (some_item->hwndFrom == hWndButton_clearPlot)
				CustomPushBTN(hWnd, some_item, selectbrush, hotbrush, defaultbrush, GRADIENT);
			else if (some_item->hwndFrom == hWndButton_Integral)
				CustomPushBTN(hWnd, some_item, selectbrush, hotbrush, defaultbrush, GRADIENT, img_integral);
			else if (some_item->hwndFrom == hWndButton_home)
				CustomPushBTN(hWnd, some_item, selectbrush, hotbrush, defaultbrush, GRADIENT, img_home);
			break;
		}

	}return CDRF_DODEFAULT;

	case WM_CTLCOLORBTN: //In order to make those edges invisble when we use RoundRect(),////////////////////////////////
		//we make the color of our button's background match window's background
		return (LRESULT)GetSysColorBrush(COLOR_WINDOW + 1);

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//case VK_RETURN:
			//	printf("Hello Enter\n");
			//	SendMessage(hWnd, WM_COMMAND, HWNDBUTTON_ENTER, NULL);
			//	return 0;
		case HWNDBUTTON_ENTER:
		{
			Wnd_Plot->Draw_way = SIMPLE_PLOTTING;
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

			Plotting_edges_upd(2, Wnd_Plot);
			FirstPlotting(Wnd_Plot, Myplot);
			UpdateWindow(Wnd_Plot->hWnd);
			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);

		}return 0;
		case HWNDBUTTON_CLEARPLOT:
		{

			Myplot.picsel.clear();
			Myplot.myvec_xy.clear();
			Wnd_Plot->text_ = (LPSTR)"";
			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);

		}return 0;
		case HWNDBUTTON_INTEGER:
		{


			Wnd_Plot->Draw_way = DRAW_INTEGRAL;
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
			if (CheckValues_of_edit(Myintegr.A, Myintegr.B, Myintegr.H, hWnd, hWndEdit_Integral, Wnd_Plot))
				return 0;
			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			Text_Init(Wnd_Plot->text_);
			if (hWnd_Integer_Wnd != NULL) DestroyWindow(hWnd_Integer_Wnd);
			RECT rc; GetWindowRect(hWnd, &rc);
			
			hWnd_Integer_Wnd = CreateWindowEx(0, Integral_Wnd_NAME, L"График интеграла функции",
				WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_POPUP | WS_CAPTION | WS_VISIBLE,
				Left_Plot_Edge + rc.left,  rc.top + 30, Wnd_Plot->sx / 2.1, Wnd_Plot->sy / 2.1,
				hWnd, NULL, hInst, nullptr);
			HWND_Integral_Init(hWnd_Integer_Wnd);
			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);
		}return 0;
		case HWNDBUTTON_HOME:
		{

			Wnd_Plot->setka.sx_center = Wnd_Plot->sx / 2;
			Wnd_Plot->setka.sy_center = Wnd_Plot->sy / 2;
			Wnd_Plot->setka.h_setka = 10;
			Wnd_Plot->setka.u5_setka = 2;
			Wnd_Plot->setka.mantissa = 1;
			Wnd_Plot->setka.h5_setka = Wnd_Plot->setka.h_setka * 5;
			Wnd_Plot->setka.kxy_zoom = Wnd_Plot->setka.h5_setka / Wnd_Plot->setka.u5_setka;
			Wnd_Plot->setka.unit_to_pixel = 1.0 / Wnd_Plot->setka.kxy_zoom;
			Plotting_edges_upd(2, Wnd_Plot);
			RedrawPlot(Wnd_Plot, Myplot);
			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);

		}return 0;
		}
		return 0;
	case WM_MOUSEMOVE:
		printf("x: %5d y: %5d\n", LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_ERASEBKGND://не надо белым закрашивать при перерисовке целое окно
		return 1;
	case WM_PAINT:
	{

		hdc = BeginPaint(hWnd, &ps);
		graph = new Gdiplus::Graphics(hdc);
		graph->Clear(BACKGROUND_COLOR);
		graph->DrawImage(img_side, 0, 0, img_width, img_height);
		delete graph;
		EndPaint(hWnd, &ps);

	}return 0;
	case WM_DESTROY:
		DeleteObject(defaultbrush);
		DeleteObject(selectbrush);
		DeleteObject(hotbrush);
		DeleteObject(hFont);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}



LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT  ps2;
	HDC memdc;
	HBITMAP membit;
	HDC hdc2{};
	static Pen* Pen_for_plot;

	switch (message)
	{
	case WM_CREATE:
		Pen_for_plot = GetPen_for_Main_Plot();
		return 0;
	case WM_LBUTTONDOWN:
		MousePos(TRUE, LOWORD(lParam), HIWORD(lParam), Wnd_Plot, MyMouse);
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

			Plotting_edges_upd(2, Wnd_Plot);
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
	case WM_MOUSEWHEEL:
	{
		int a = Wnd_Plot->setka.h_setka;
		Wnd_Plot->setka.h_setka += GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		/*{//попытка сделать приближение к центру экрана а не к СК
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
		if (Wnd_Plot->Draw_way == DRAW_INTEGRAL) {
			CorrectSetkaPos(0, Wnd_Plot, Myintegr.vec);
			CorrectSetkaPos(0, Wnd_Plot, Myintegr.integral_plot);
		}
		else {
			CorrectSetkaPos(0, Wnd_Plot, Myplot);
		}
		//RedrawPlot(Wnd_Plot, Myplot);
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
		//SimpleTimer timer;
		hdc2 = BeginPaint(Wnd_Plot->hWnd, &ps2);
		memdc = CreateCompatibleDC(hdc2);
		membit = CreateCompatibleBitmap(hdc2, Wnd_Plot->sx, Wnd_Plot->sy);
		SelectObject(memdc, membit);
		DrowSetka(memdc, Wnd_Plot);
		DrowCounts(memdc, Wnd_Plot);
		//if (!Myplot.picsel.empty())
		//{
		//	DrowGraphSmooth(memdc, Wnd_Plot, Myplot);
		//	//DrowGraph(memdc, Wnd_Plot);оставим для экспериментов - рисование без GDI+
		//}
		if (!Myplot.picsel.empty())
		{
			DrowGraphSmooth(memdc, Wnd_Plot, Myplot, Pen_for_plot);
			//DrowGraph(memdc, Wnd_Plot);оставим для экспериментов - рисование без GDI+
		}

		BitBlt(hdc2, 0, 0, Wnd_Plot->sx * 2, Wnd_Plot->sy * 2, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(membit);
		EndPaint(Wnd_Plot->hWnd, &ps2);
	}
	return 0;
	case WM_DESTROY:
		//delete Pen_for_plot;
		PostQuitMessage(0);
		return DefWindowProc(hWnd, message, wParam, lParam);
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
