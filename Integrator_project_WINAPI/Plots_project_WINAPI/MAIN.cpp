#pragma comment(lib, "GdiPlus.lib")
#include "main_header.h"
#define CONSOLE

HINSTANCE hInst;
TCHAR WidMain_NAME[MAX_LOADSTRING] = _T("MainWindow");

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
#ifdef CONSOLE
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

	GdiplusStartupInput gdiplusStartupInput;
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

	HWND hWnd = CreateWindow(
		WidMain_NAME, 
		_T("Каркас Windows-приложения"), 
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
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

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}
