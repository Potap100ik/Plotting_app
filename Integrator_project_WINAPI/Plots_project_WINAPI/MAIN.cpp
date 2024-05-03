//#include "Header.h"
#include "main_header.h"


int main()
{
	extern HWND hStat;
	main_help_wnd();
	SetWindowText(hStat, L"400 sdfasf");
	return 0;
}







HINSTANCE hInst;
//имена для классов
TCHAR WidMain_NAME[MAX_LOADSTRING] = _T("MainWindow");


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	hInst = hInstance;
	HWND hWnd; // Дескриптор главного окна программы
	MSG msg; // Структура для хранения сообщения
	WNDCLASS wc{}; // Класс окна
	// Определение класса окна
	wc.hInstance = hInstance;
	wc.lpszClassName = WidMain_NAME; // Имя класса окна
	wc.lpfnWndProc = WinProc; // Функция окна///////////////////////////////////////////////////////////////
	wc.style = CS_HREDRAW | CS_VREDRAW; // Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // НЕ_Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Стандартный курсор
	wc.lpszMenuName = NULL; // Нет меню - NULL
	wc.cbClsExtra = 0; // Нет дополнительных данных класса
	wc.cbWndExtra = 0; // Нет дополнительных данных окна
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// Заполнение окна белым цветом
	if (!RegisterClass(&wc)) return 0; // Регистрация класса окна
	// Создание окна
	hWnd = CreateWindow(
		WidMain_NAME, // Имя класса окна
		_T("Каркас Windows-приложения"), // Заголовок окна
		WS_OVERLAPPEDWINDOW, // Стиль окна
		CW_USEDEFAULT, // x
		CW_USEDEFAULT, // y Размеры окна
		CW_USEDEFAULT, // width
		CW_USEDEFAULT, // Height
		HWND_DESKTOP, // Дескриптор родительского окна
		NULL, // Нет меню
		hInstance, // Дескриптор приложения
		NULL); // Дополнительной информации нет
	//hWnd_main = hWnd;
	//CreateControls(hWnd);
	ShowWindow(hWnd, nCmdShow); // Показать окно
	// Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg); // Посылает сообщение функции WndProc()
	}
	//WinMain_(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}
#pragma comment(lib, "GdiPlus.lib")//а ты попробуй удали