#pragma comment(lib, "GdiPlus.lib")
#include "../Main_files/STD/stdafx.h"
#include "../Main_files/STD/Standard.h"
#define CONSOLE

HINSTANCE hInst;
//MyWnd_Plot* Wnd_Plot;
WCHAR WidMain_NAME[MAX_LOADSTRING] = L"MainWindow";

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//делаем консоль видимой для удобства - можно делать cout и дебажить как хочется - откл: закомментить #define CONSOLE
#ifdef CONSOLE
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Rus");
	FILE* conin = stdin;
	FILE* conout = stdout;
	FILE* conerr = stderr;
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen_s(&conin, "CONIN$", "r", stdin);
	freopen_s(&conout, "CONOUT$", "w", stdout);
	freopen_s(&conerr, "CONOUT$", "w", stderr);
	SetConsoleTitle(L"appconsole");
	setlocale(LC_ALL, "Rus");
#endif //CONSOLE

	//призыв GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	hInst = hInstance;
	WNDCLASS wc{};
	wc.hInstance = hInstance;
	wc.lpszClassName = WidMain_NAME;
	wc.lpfnWndProc = WinProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;

	HWND hWnd = CreateWindowW(
		WidMain_NAME,
		L"Каркас Windows-приложения",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		MINIMUM_BASE_WND_WIDTH,//GetSystemMetrics(SM_CXSCREEN),
		MINIMUM_BASE_WND_HEIGHT,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hWnd, nCmdShow);

	MSG msg{};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//прощание с GDI+
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}
