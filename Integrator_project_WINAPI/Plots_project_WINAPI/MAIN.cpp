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
//����� ��� �������
TCHAR WidMain_NAME[MAX_LOADSTRING] = _T("MainWindow");


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	hInst = hInstance;
	HWND hWnd; // ���������� �������� ���� ���������
	MSG msg; // ��������� ��� �������� ���������
	WNDCLASS wc{}; // ����� ����
	// ����������� ������ ����
	wc.hInstance = hInstance;
	wc.lpszClassName = WidMain_NAME; // ��� ������ ����
	wc.lpfnWndProc = WinProc; // ������� ����///////////////////////////////////////////////////////////////
	wc.style = CS_HREDRAW | CS_VREDRAW; // ����� ����
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ��_����������� ������
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ����������� ������
	wc.lpszMenuName = NULL; // ��� ���� - NULL
	wc.cbClsExtra = 0; // ��� �������������� ������ ������
	wc.cbWndExtra = 0; // ��� �������������� ������ ����
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// ���������� ���� ����� ������
	if (!RegisterClass(&wc)) return 0; // ����������� ������ ����
	// �������� ����
	hWnd = CreateWindow(
		WidMain_NAME, // ��� ������ ����
		_T("������ Windows-����������"), // ��������� ����
		WS_OVERLAPPEDWINDOW, // ����� ����
		CW_USEDEFAULT, // x
		CW_USEDEFAULT, // y ������� ����
		CW_USEDEFAULT, // width
		CW_USEDEFAULT, // Height
		HWND_DESKTOP, // ���������� ������������� ����
		NULL, // ��� ����
		hInstance, // ���������� ����������
		NULL); // �������������� ���������� ���
	//hWnd_main = hWnd;
	//CreateControls(hWnd);
	ShowWindow(hWnd, nCmdShow); // �������� ����
	// ���� ��������� ���������
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // ������� ���������� ����� ������� �������
		DispatchMessage(&msg); // �������� ��������� ������� WndProc()
	}
	//WinMain_(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}
#pragma comment(lib, "GdiPlus.lib")//� �� �������� �����