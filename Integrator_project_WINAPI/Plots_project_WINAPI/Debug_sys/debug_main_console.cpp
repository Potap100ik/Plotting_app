#pragma comment(lib, "GdiPlus.lib")
#include "../Main_files/type.h"
#include "../resource.h"
#include "../Custom_for_nice_veiw.h"
#include "../Main_files/WndProc.h"
#include "../Main_files/STD/stdafx.h"
#ifdef SEARCH_UTECHKA_MEMORY
#ifdef CONSOLE
#include "vld.h"
#pragma comment (lib, "vld.lib")
#endif //CONSOLE
#endif //SEARCH_UTECHKA_MEMORY



extern HINSTANCE hInst;
//Wnd_Plot_struct* Wnd_Plot;
extern WCHAR WidMain_NAME[MAX_LOADSTRING];

//int main()
//{
//	//делаем консоль видимой для удобства - можно делать cout и дебажить как хочется - откл: закомментить #define CONSOLE
//
//
//	//призыв GDI+
//	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
//	ULONG_PTR gdiplusToken;
//	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
//	hInst = NULL;
//
//	WNDCLASS wc{};
//	memset(&wc, 0, sizeof(WNDCLASSA));
//	wc.lpszClassName = WidMain_NAME;
//	wc.lpfnWndProc = WndProc;
//	if (!RegisterClass(&wc)) return 0;
//
//	HWND hWnd = CreateWindowW(
//		WidMain_NAME,
//		L"Каркас Windows-приложения",
//		WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT,
//		CW_USEDEFAULT,
//		MINIMUM_BASE_WND_WIDTH,//GetSystemMetrics(SM_CXSCREEN),
//		MINIMUM_BASE_WND_HEIGHT,
//		HWND_DESKTOP,
//		NULL,
//		hInst,
//		NULL);
//	ShowWindow(hWnd, SW_SHOWNORMAL);
//
//	MSG msg{};
//	while (GetMessage(&msg, NULL, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	//прощание с GDI+
//	Gdiplus::GdiplusShutdown(gdiplusToken);
//	return 0;
//}
