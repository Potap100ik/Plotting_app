#include "../Main_files/STD/stdafx.h"
#include "../Main_files/STD/Standard.h"

WCHAR Win_Plot_NAME[MAX_LOADSTRING] = L"PlotWindow";//классовое имя окна с графиком
WCHAR Integral_Wnd_NAME[MAX_LOADSTRING] = L"Integral_Wnd";//классовое имя окна с графиком интеграла
//МЕСТНЫЕ СТАТИЧЕСКИЕ ФУНКЦИИ
LPVOID CreateControls(HWND hWnd);
void EditInit();
ATOM Register_Main_Plot_Wnd_Class();
ATOM Register_Integer_Wnd_Class();

//extern - так делать нельзя, но я по-другому пока не умею
extern HINSTANCE hInst;//контекст приложения для создания кнопок, окон и прочего - инициализация в мейн.сррр

//копия данных из главного графика и расчет данных графика интеграла
//дескрипторы всех контролов для манипуляции ими в разных срр файлах
HWND
hWndChild_Plot{},
hWndChild_Integral,
hWndButton_enter{},
hWndButton_clearPlot{},
hWndButton_Integral{},
hWndButton_home{},
hWndEdit_base{},
hWndEdit_A{},
hWndEdit_B{},
hWndEdit_H{},
hWndEdit_Integral{},
hWndEdit_Erroors{};

void EditInit()
{
	SetWindowText(hWndEdit_base, L"sin(x)");//log(x)//sin(x)*abs(x)//x*x/10
	SetWindowText(hWndEdit_A, L"0");
	SetWindowText(hWndEdit_B, L"10");
	SetWindowText(hWndEdit_H, L"0.1");
	SetWindowText(hWndEdit_Integral, L"Здесь появится значение интеграла");
	SetWindowText(hWndEdit_Erroors, L"Ошибки:");
}
LPVOID CreateControls(HWND hWnd)//магия создания кнопок и других контролов
{
	hWndButton_enter = CreateWindowEx(
		0,
		L"BUTTON",
		L"Построить график",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 1),//все координаты хранятся и меняются в отдельном хедере
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
		L"",
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
		L"Посчитать интеграл",
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
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE ,
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
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE ,
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
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
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
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
		Get_EDIT_ERRORS_koordinates(1),
		Get_EDIT_ERRORS_koordinates(2),
		Get_EDIT_ERRORS_koordinates(3),
		Get_EDIT_ERRORS_koordinates(4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_ERROR),
		nullptr, nullptr);
	if (!hWndEdit_Integral)
		MessageBox(NULL, L"hWndEdit_Erroors", L"Ошибка", MB_OK);
	return 0;
}
ATOM Register_Integer_Wnd_Class()
{
	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpszClassName = Integral_Wnd_NAME;
	wcex.lpfnWndProc = Integral_Wnd_Proc;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hInstance = hInst;
	return RegisterClassEx(&wcex);
}
ATOM Register_Main_Plot_Wnd_Class()
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

	HDC hdc;//контекст устройства для рисования в этом окне
	PAINTSTRUCT ps;
	static Gdiplus::Bitmap* img_side{};//картинка для заднего фона кнопок
	static Gdiplus::Bitmap* img_clearbutton{};//картинка для кнопок
	static Gdiplus::Bitmap* img_homebutton{};

	static int img_side_height;//размеры для вывода картинки заднего фона
	static int img_side_width;

	Gdiplus::Graphics* graph;//переменная для рисования картинок в окне
	
	//кисти для закрашивания кнопок
	static HBRUSH defaultbrush;//базовое состояние
	static HBRUSH selectbrush;//нажание на кнопку
	static HBRUSH hotbrush;//наведение на кнопку

	static HFONT hFont1;//шрифт для вывода чисел на графике

	static POINT Plot_WndSize;

	static bool createwindow_mainplot;
	switch (message)
	{
	case WM_CREATE:
	{
		////////////////////////////////////////////////////////////////////////////
		CreateControls(hWnd);
		EditInit();
		if (!Register_Main_Plot_Wnd_Class())
			MessageBox(NULL, L"НЕ ВЫШЕЛ ГРАФИК ПОГУЛЯТЬ", L"Ошибка", MB_OK);
		if (!Register_Integer_Wnd_Class())
			MessageBox(NULL, L"НЕ ВЫШЕЛ ПУШНЫЙ ГРАФИК ПОГУЛЯТЬ", L"Ошибка", MB_OK);
		/////////////////////////////////////////////////////////////////////////////
		
#pragma warning(suppress:6011)//нелогичная ошибка разыменования пустого указателы(несмотря на инициализацию сверху)
		hWndChild_Plot = CreateWindow(Win_Plot_NAME, NULL,
			WS_CHILD | WS_DLGFRAME | WS_VISIBLE,
			0, 0, 0, 0, 
			hWnd, NULL, hInst, NULL);
		createwindow_mainplot = true;
		/////////////////////////////////////////////////////////////////////////////
		img_side = Gdiplus::Bitmap::FromFile(Side_image_adress);
		img_side_height = img_side->GetHeight() * (Width_for_background_image) / img_side->GetWidth();
		img_side_width = Width_for_background_image;
		/////////////////////////////////////////////////////////////////////////////
		img_homebutton = Gdiplus::Bitmap::FromFile(Image_Home_btn);
		img_clearbutton = Gdiplus::Bitmap::FromFile(Image_CLEAR_btn);
	}return 0;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = MINIMUM_BASE_WND_WIDTH;
		lpMMI->ptMinTrackSize.y = MINIMUM_BASE_WND_HEIGHT;
	}return 0;
	case WM_SIZE:
	{
#ifdef CONSOLE
		printf("sx = %5d sy = %5d\n", LOWORD(lParam), HIWORD(lParam));
#endif //CONSOLE
		Plot_WndSize.x = LOWORD(lParam) - Left_Wnd_Plot_Board - len_till_main_wnd_board;
		Plot_WndSize.y = HIWORD(lParam) - len_till_main_wnd_board;
		MoveWindow(hWndChild_Plot, Left_Wnd_Plot_Board, 0, Plot_WndSize.x, Plot_WndSize.y, TRUE);
		if (createwindow_mainplot) { MainPlot_Init(hWndChild_Plot); createwindow_mainplot = false; }
		SendMessageW(hWndChild_Plot, WM_RESIZE_PLOT, NULL, NULL);
	}return 0;
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;
		switch (some_item->code)
		{
		case NM_CUSTOMDRAW:
			if (some_item->hwndFrom == hWndButton_enter)
				CustomPushBTN(hWnd, some_item, selectbrush, hotbrush, defaultbrush, GRADIENT);
			else if (some_item->hwndFrom == hWndButton_clearPlot)
				CustomPushBTN(hWnd, some_item, selectbrush, hotbrush, defaultbrush, GRADIENT, img_clearbutton);
			else if (some_item->hwndFrom == hWndButton_Integral)
				CustomPushBTN(hWnd, some_item, selectbrush, hotbrush, defaultbrush, GRADIENT);
			else if (some_item->hwndFrom == hWndButton_home)
				CustomPushBTN(hWnd, some_item, selectbrush, hotbrush, defaultbrush, GRADIENT, img_homebutton);
			break;
		}

	}
	return CDRF_DODEFAULT;
	case WM_CTLCOLORBTN:return (LRESULT)GetSysColorBrush(COLOR_WINDOW + 1);////////////////////////////////////////////
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case HWNDBUTTON_ENTER:
		{
			std::wstring text;//вводимое значение функции
			LPSTR text_;
			text.clear();
			text.reserve(MAX_LOADSTRING);
			GetWindowText(hWndEdit_base, &text[0], MAX_LOADSTRING);
			text.erase(remove(text.begin(), text.end(), 0), text.end());
			text_ = Wide_into_Ascii(text.c_str());
			if (strlen(text_) == 0)
			{
#ifdef CONSOLE
				MessageBox(hWnd, L"Уважаемый прогер\nГде ваша функция?", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
#else 
				SetWindowText(hWndEdit_Erroors, L"Где ваша функция?");
#endif //CONSOLE
				return 0;
			}
			////////////////////////////////////////////////////////////
			SendMessageW(hWndChild_Plot, WM_DRAW_MAIN_PLOT, (WPARAM)text_, NULL);
			UpdateWindow(hWndChild_Plot);
			InvalidateRect(hWndChild_Plot, NULL, TRUE);
		}return 0;
		case HWNDBUTTON_CLEARPLOT:
		{
			///////////////////////////////////////?????????????????????????????????????????????????????
			SendMessageW(hWndChild_Plot, WM_CLEAR_PLOT, NULL, NULL);
			SetWindowText(hWndEdit_Integral, L"");
			SetWindowText(hWndEdit_Erroors, L"");
			SendMessageW(hWndChild_Integral, WM_CLOSE, 0, 0);
			InvalidateRect(hWndChild_Plot, NULL, TRUE);
		}return 0;
		case HWNDBUTTON_INTEGER:
		{
			std::wstring text;//вводимое значение функции
			LPSTR text_ = (LPSTR)malloc(MAX_LOADSTRING);
			double A, B, H;
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
			try
			{
				A = std::stod(Astr);
				B = std::stod(Bstr);
				H = std::stod(Hstr);
			}
			catch (...)
			{
#ifdef CONSOLE
				MessageBox(hWnd, L"Уважаемый прогер\nГде числа?!!!\nИз чего интегралы строить", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
#endif //CONSOLE
				SetWindowText(hWndEdit_Integral, L"Err: Интеграл пока не равен");
				return 0;
			}

			text_ = Wide_into_Ascii(text.c_str());
			if (CheckValues_of_edit(A, B, H, hWnd, hWndEdit_Integral, text_))
				return 0;
			//////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (hWndChild_Integral != NULL) DestroyWindow(hWndChild_Integral);
			RECT rc; GetWindowRect(hWnd, &rc);
			
			hWndChild_Integral = CreateWindowEx(0, Integral_Wnd_NAME, L"График интеграла функции",
				WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_POPUP | WS_CAPTION | WS_VISIBLE,
				Left_Wnd_Plot_Board + rc.left,  rc.top + 30, Plot_WndSize.x / 2.1, Plot_WndSize.y / 2.1,
				hWnd, NULL, hInst, nullptr);

			WND_Integral_Init(hWndChild_Integral, text_,A,B,H);
			InvalidateRect(hWndChild_Integral, NULL, TRUE);
		}return 0;
		case HWNDBUTTON_HOME:
		{
			SendMessageW(hWndChild_Plot, WM_HOME_BTN_CLICKED, NULL, NULL);
			InvalidateRect(hWndChild_Plot, NULL, TRUE);
		}return 0;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_MOUSEMOVE:
	{
#ifdef CONSOLE
		printf("x: %5d y: %5d\n", LOWORD(lParam), HIWORD(lParam));
#endif //CONSOLE
	}return 0;
	case WM_ERASEBKGND:return 1;//не надо белым закрашивать при перерисовке целое окно
	case WM_PAINT:
	{

		hdc = BeginPaint(hWnd, &ps);
		graph = new Gdiplus::Graphics(hdc);
		graph->Clear(BACKGROUND_COLOR);
		graph->DrawImage(img_side, 0, 0, img_side_width, img_side_height);
		delete graph;
		EndPaint(hWnd, &ps);

	}return 0;
	case WM_DESTROY:
	{
		delete img_side;
		delete img_clearbutton;
		delete img_homebutton;
		DeleteObject(defaultbrush);
		DeleteObject(selectbrush);
		DeleteObject(hotbrush);
		DeleteObject(hFont1);
		PostQuitMessage(0);
	}return 0;
		
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
