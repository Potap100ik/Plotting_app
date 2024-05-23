#include "WndProc.h"

#include "type.h"
#include "../Custom_for_nice_veiw.h"
#include "../Integral_Wnd_Proc.h"
#include "../WinPlot_Proc.h"
#include "main_header.h"
#include "../Error.h"


WCHAR Win_Plot_NAME[MAX_LOADSTRING] = L"PlotWindow";//��������� ��� ���� � ��������
WCHAR Integral_Wnd_NAME[MAX_LOADSTRING] = L"Integral_Wnd";//��������� ��� ���� � �������� ���������
//������� ����������� �������

//extern - ��� ������ ������, �� � ��-������� ���� �� ����
extern HINSTANCE hInst;//�������� ���������� ��� �������� ������, ���� � ������� - ������������� � ����.����

//����� ������ �� �������� ������� � ������ ������ ������� ���������
//����������� ���� ��������� ��� ����������� ��� � ������ ��� ������
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


#ifdef GLOBAL_PRINT
void PrintGlobal_WndProc_cpp()
{
	printf("WndProc\n");
	printf("hWndButton_enter = %llu\n", sizeof(hWndButton_enter));
	printf("hWndButton_clearPlot = %llu\n", sizeof(hWndButton_clearPlot));
	printf("hWndButton_Integral = %llu\n", sizeof(hWndButton_Integral));
	printf("hWndButton_home = %llu\n", sizeof(hWndButton_home));
	printf("hWndEdit_base = %llu\n", sizeof(hWndEdit_base));
	printf("hWndEdit_A = %llu\n", sizeof(hWndEdit_A));
	printf("hWndEdit_B = %llu\n", sizeof(hWndEdit_B));
	printf("hWndEdit_H = %llu\n", sizeof(hWndEdit_H));
	printf("hWndEdit_Integral = %llu\n", sizeof(hWndEdit_Integral));
	printf("hWndEdit_erroors = %llu\n", sizeof(hWndEdit_Erroors));
	printf("hInst = %llu\n", sizeof(hInst)); Win_Plot_NAME;
	printf("Win_Plot_NAME = %llu\n", sizeof(Win_Plot_NAME));
	printf("Integral_Wnd_NAME = %llu\n", sizeof(Integral_Wnd_NAME));
}
#endif //GLOBAL_PRINT

void EditInit()
{
	SetWindowText(hWndEdit_base, L"sin(x)*abs(x)*tg(x^2)");//log(x)//sin(x)*abs(x)//x*x/10
	SetWindowText(hWndEdit_A, L"0");
	SetWindowText(hWndEdit_B, L"10");
	SetWindowText(hWndEdit_H, L"0.1");
	SetWindowText(hWndEdit_Integral, L"�������� ���������");
	SetWindowText(hWndEdit_Erroors, L"������:");
}
LPVOID CreateControls(HWND hWnd)//����� �������� ������ � ������ ���������
{
	hWndButton_enter = CreateWindowEx(
		0,
		L"BUTTON",
		L"��������� ������",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 1),//��� ���������� �������� � �������� � ��������� ������
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 2),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 3),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_ENTER, 4),
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_ENTER),
		nullptr, nullptr);
	if (!hWndButton_enter)
		MessageBox(NULL, L"hWndButton_enter", L"������", MB_OK);

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
		MessageBox(NULL, L"hWndButton_clearPlot", L"������", MB_OK);

	hWndButton_Integral = CreateWindowEx(
		0,
		L"BUTTON",
		L"��������� ��������",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_INTEGER, 1),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_INTEGER, 2),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_INTEGER, 3),
		Get_BUTTON_ENTER_koordinates(HWNDBUTTON_INTEGER, 4),
		hWnd,
		reinterpret_cast<HMENU> (CTL_ID::HWNDBUTTON_INTEGER),
		nullptr, nullptr);
	if (!hWndButton_Integral)
		MessageBox(NULL, L"hWndButton_clearEdit", L"������", MB_OK);

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
		MessageBox(NULL, L"hWndButton_clearEdit", L"������", MB_OK);



	hWndEdit_base = CreateWindow(
		L"EDIT",
		L"log(x)",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE,
		Get_EDIT_FUNC_koordinates(1),
		Get_EDIT_FUNC_koordinates(2),
		Get_EDIT_FUNC_koordinates(3),
		Get_EDIT_FUNC_koordinates(4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_BASE),
		nullptr, nullptr);

	if (!hWndEdit_base)
		MessageBox(NULL, L"hWndEdit_base", L"������", MB_OK);
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
		MessageBox(NULL, L"hWndEdit_A", L"������", MB_OK);
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
		MessageBox(NULL, L"hWndEdit_B", L"������", MB_OK);
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
		MessageBox(NULL, L"hWndEdit_H", L"������", MB_OK);
	SetEditTypingCenter(hWndEdit_H, 'H', Get_EDIT_ABH_koordinates);


	hWndEdit_Integral = CreateWindowEx(
		0,
		L"EDIT",
		L"�������� �������� ���",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
		Get_EDIT_INTEGRAL_koordinates(1),
		Get_EDIT_INTEGRAL_koordinates(2),
		Get_EDIT_INTEGRAL_koordinates(3),
		Get_EDIT_INTEGRAL_koordinates(4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_INTEGER),
		nullptr, nullptr);
	if (!hWndEdit_Integral)
		MessageBox(NULL, L"hWndEdit_Integral", L"������", MB_OK);
	SetEditTypingCenter(hWndEdit_Integral, Get_EDIT_INTEGRAL_koordinates);


	hWndEdit_Erroors = CreateWindowEx(
		0,
		L"EDIT",
		L"������:",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
		Get_EDIT_ERRORS_koordinates(1),
		Get_EDIT_ERRORS_koordinates(2),
		Get_EDIT_ERRORS_koordinates(3),
		Get_EDIT_ERRORS_koordinates(4),
		hWnd,
		reinterpret_cast<HMENU>(CTL_ID::HWNDEDIT_ERROR),
		nullptr, nullptr);
	if (!hWndEdit_Integral)
		MessageBox(NULL, L"hWndEdit_Erroors", L"������", MB_OK);
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
	wcex.style = CS_HREDRAW | CS_VREDRAW; // ����� ����
	wcex.lpszClassName = Win_Plot_NAME;
	wcex.lpfnWndProc = Win_Plot;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hInstance = hInst;
	return RegisterClassEx(&wcex);
}

//������� ���������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam)
{

	HDC hdc;//�������� ���������� ��� ��������� � ���� ����
	PAINTSTRUCT ps;
	static Gdiplus::Bitmap* img_side{};//�������� ��� ������� ���� ������
	static Gdiplus::Bitmap* img_clearbutton{};//�������� ��� ������
	static Gdiplus::Bitmap* img_homebutton{};

	static int img_side_height;//������� ��� ������ �������� ������� ����
	static int img_side_width;

	Gdiplus::Graphics* graph;//���������� ��� ��������� �������� � ����

	//����� ��� ������������ ������
	static HBRUSH defaultbrush;//������� ���������
	static HBRUSH selectbrush;//������� �� ������
	static HBRUSH hotbrush;//��������� �� ������

	static HFONT hFont1;//����� ��� ������ ����� �� �������

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
			MessageBox(NULL, L"�� ����� ������ ��������", L"������", MB_OK);
		if (!Register_Integer_Wnd_Class())
			MessageBox(NULL, L"�� ����� ������ ������ ��������", L"������", MB_OK);
		/////////////////////////////////////////////////////////////////////////////
		hWndChild_Plot = CreateWindow(Win_Plot_NAME, NULL,
			WS_CHILD | WS_DLGFRAME | WS_VISIBLE,
			0, 0, 0, 0,
			hWnd, NULL, hInst, NULL);
		createwindow_mainplot = true;
		/////////////////////////////////////////////////////////////////////////////
		img_side = Gdiplus::Bitmap::FromFile(Side_image_adress);
		img_homebutton = Gdiplus::Bitmap::FromFile(Image_Home_btn);
		img_clearbutton = Gdiplus::Bitmap::FromFile(Image_CLEAR_btn);
		if (CheckImageOpening(img_side, img_homebutton, img_clearbutton, hWnd))
		{
			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
			return 1;
		}
		img_side_height = img_side->GetHeight() * (Width_for_background_image) / img_side->GetWidth();
		img_side_width = Width_for_background_image;
#ifdef GLOBAL_PRINT
		PrintGlobal_WndProc_cpp();
		printf("img_side = %llu\n", sizeof(img_side));
		printf("img_clearbutton = %llu\n", sizeof(img_clearbutton));
		printf("img_homebutton = %llu\n", sizeof(img_homebutton));
		printf("img_side_height = %llu\n", sizeof(img_side_height));
		printf("img_side_width = %llu\n", sizeof(img_side_width));
		printf("defaultbrush = %llu\n", sizeof(defaultbrush));
		printf("img_siselectbrushde = %llu\n", sizeof(selectbrush));
		printf("hotbrush = %llu\n", sizeof(hotbrush));
		printf("Plot_WndSize = %llu\n", sizeof(Plot_WndSize));
		printf("createwindow_mainplot = %llu\n", sizeof(createwindow_mainplot));
#endif //GLOBAL_PRINT
	}return 0;
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = MINIMUM_BASE_WND_WIDTH;
		lpMMI->ptMinTrackSize.y = MINIMUM_BASE_WND_HEIGHT;
	}return 0;
	case WM_SIZE:
	{
#ifdef SIZE_PRINT
		printf("sx = %5d sy = %5d\n", LOWORD(lParam), HIWORD(lParam));
#endif //SIZE_PRINT
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
	//case WM_CTLCOLORBTN:return (LRESULT)GetSysColorBrush(COLOR_WINDOW + 1);////////////////////////////////////////////
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case HWNDBUTTON_ENTER:
		{
			SetWindowText(hWndEdit_Erroors, L"������:");
			LPWSTR w_text_ = (LPWSTR)malloc(MAX_LOADSTRING);
			GetWindowText(hWndEdit_base, w_text_, MAX_LOADSTRING - 1);
			LPSTR text_ = Wide_into_Ascii(w_text_);
			if (strlen(text_) == 0)
			{
				MessageBox(hWnd, L"��������� ������\n��� ���� �������?", L"��������, ������", MB_OK | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"�������� ���� �� �����");
				SetWindowText(hWndEdit_Erroors, L"������� �������");
				return 1;
			}
			////////////////////////////////////////////////////////////
			SendMessageW(hWndChild_Plot, WM_DRAW_MAIN_PLOT, (WPARAM)text_, NULL);
			free(w_text_);
			//free(text_);
			UpdateWindow(hWndChild_Plot);
			InvalidateRect(hWndChild_Plot, NULL, TRUE);
		}return 0;
		case HWNDBUTTON_CLEARPLOT:
		{
			///////////////////////////////////////?????????????????????????????????????????????????????
			SendMessageW(hWndChild_Plot, WM_CLEAR_PLOT, NULL, NULL);
			SetWindowText(hWndEdit_Integral, L"�������� ���������");
			SetWindowText(hWndEdit_Erroors, L"������:");
			SendMessageW(hWndChild_Integral, WM_CLOSE, 0, 0);
			InvalidateRect(hWndChild_Plot, NULL, TRUE);
		}return 0;
		case HWNDBUTTON_INTEGER:
		{
			if (hWndChild_Integral != NULL) DestroyWindow(hWndChild_Integral);
			SetWindowText(hWndEdit_Erroors, L"������:");

			LPWSTR w_text_ = (LPWSTR)malloc(MAX_LOADSTRING);
			double A, B, H;
			LPWSTR A_wstr = (LPWSTR)malloc(MAX_LOADSTRING);
			LPWSTR B_wstr = (LPWSTR)malloc(MAX_LOADSTRING);
			LPWSTR H_wstr = (LPWSTR)malloc(MAX_LOADSTRING);

			GetWindowText(hWndEdit_A, A_wstr, MAX_LOADSTRING);
			GetWindowText(hWndEdit_B, B_wstr, MAX_LOADSTRING);
			GetWindowText(hWndEdit_H, H_wstr, MAX_LOADSTRING);
			GetWindowText(hWndEdit_base, w_text_, MAX_LOADSTRING);

			if (CheckOnlyNumbers(A_wstr, B_wstr, H_wstr, hWndEdit_Erroors, hWnd, hWndEdit_Integral) != 0 && A_wstr != 0) {
				return 1;
			}
			if (A_wstr != 0 && B_wstr != 0 && H_wstr != 0)
			{
				A = std::stod(A_wstr);
				B = std::stod(B_wstr);
				H = std::stod(H_wstr);
			}



			LPSTR text_ = Wide_into_Ascii(w_text_);
			if (CheckValues_of_edit(A, B, H, hWnd, hWndEdit_Integral, text_)) {
				return 0;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			RECT rc; GetWindowRect(hWnd, &rc);

			hWndChild_Integral = CreateWindowEx(0, Integral_Wnd_NAME, L"������ ��������� �������",
				WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_POPUP | WS_CAPTION | WS_VISIBLE,
				Left_Wnd_Plot_Board + rc.left, rc.top + 30, Plot_WndSize.x / 2.1, Plot_WndSize.y / 2.1,
				hWnd, NULL, hInst, nullptr);

			WND_Integral_Init(hWndChild_Integral, text_, A, B, H);
			free(w_text_);
			//free(text_);
			free(A_wstr);
			free(B_wstr);
			free(H_wstr);
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
#ifdef MOUSE_KOORDITNATES_PRINT
		printf("x: %5d y: %5d\n", LOWORD(lParam), HIWORD(lParam));
#endif //MOUSE_KOORDITNATES_PRINT
	}return 0;
	case WM_ERASEBKGND:return 1;//�� ���� ����� ����������� ��� ����������� ����� ����
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
		if (img_side != 0)delete img_side;
		if (img_clearbutton != 0)delete img_clearbutton;
		if (img_homebutton != 0)delete img_homebutton;
		DeleteObject(defaultbrush);
		DeleteObject(selectbrush);
		DeleteObject(hotbrush);
		DeleteObject(hFont1);
		PostQuitMessage(0);
	}return 0;

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
	}
