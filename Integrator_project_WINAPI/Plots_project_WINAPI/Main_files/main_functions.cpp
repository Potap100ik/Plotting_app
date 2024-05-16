#include "../Main_files/STD/stdafx.h"
#include "../Main_files/STD/Standard.h"
using namespace Gdiplus;



extern HINSTANCE hInst;/////////////////////////////////////////////////////убери глобальные переменные потому что так надо
//глобальные переменные
const int Wide_of_Screen = GetSystemMetrics(SM_CXSCREEN);
double IntegerSum;
int countpaint = 0;
//std::wstring str;
MyWnd_Plot Wnd_Plot{};
MouseMove MyMouse{};
HDC hdc{};
HWND
hWndButton_enter{},
hWndButton_clearPlot{},
hWndButton_clearEdit{},
hWndButton_home{},
hWndEdit_base{},
hWndEdit_A{},
hWndEdit_B{},
hWndEdit_H{},
hWndEdit_Integral{};



//исполнительные функции
double Setka_unit(double get_value)
{
	double u;
	double c1 = get_value;
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
	else if (c1 == 0)
		n = 2;
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
void StructInit()
{
	Wnd_Plot.text_ = (LPSTR)"";
	Wnd_Plot.setka.h_setka = 10;
	Wnd_Plot.setka.h5_setka = Wnd_Plot.setka.h_setka * 5; //50
	Wnd_Plot.setka.u5_setka = 2;
	Wnd_Plot.setka.mantissa = 1;
	Wnd_Plot.setka.kxy_zoom = Wnd_Plot.setka.h5_setka / Wnd_Plot.setka.u5_setka;//25
	Wnd_Plot.setka.unit_to_pixel = 1.0 / Wnd_Plot.setka.kxy_zoom;
	Plotting_edges_upd(1);
	Wnd_Plot.setka.LLeft = Wnd_Plot.x_LL / Wnd_Plot.setka.unit_to_pixel;
	Wnd_Plot.setka.RRight = Wnd_Plot.x_RR / Wnd_Plot.setka.unit_to_pixel;
	Wnd_Plot.setka.TTop = Wnd_Plot.y_TT / Wnd_Plot.setka.unit_to_pixel;
	Wnd_Plot.setka.BBottom = Wnd_Plot.y_BB / Wnd_Plot.setka.unit_to_pixel;



	Wnd_Plot.setka.Wide_Vec = 4000 + Wide_of_Screen;
	Wnd_Plot.setka.Left_Wide_Vec = -(Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;
	Wnd_Plot.setka.Right_Wide_Vec = (Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;

	Wnd_Plot.setka.u_HHH = 2;//шаг рисовки - 2 пикселя
	Wnd_Plot.plot.A = -10;
	Wnd_Plot.plot.B = 10;
	Wnd_Plot.plot.H = 0.1;
	SetWindowText(hWndEdit_base, L"sin(x)*abs(x)");//log(x)
	SetWindowText(hWndEdit_A, L"-10");// std::to_wstring(Wnd_Plot.plot.A).c_str()
	SetWindowText(hWndEdit_B, L"10");
	SetWindowText(hWndEdit_H, L"0,1");
	SetWindowText(hWndEdit_Integral, L"Ку-ку епта");

	Wnd_Plot.plot.myvec_xy_picsel.reserve(Wnd_Plot.setka.Wide_Vec + 1);
	Wnd_Plot.plot.myvec_xy.reserve(Wnd_Plot.setka.Wide_Vec + 1);


}
void MousePos(BOOL fl, int x, int y)
{
	MyMouse.Flag_for_mouse = fl;
	MyMouse.Prev_mouse_point.x = x;
	MyMouse.Prev_mouse_point.y = y;
}
void CorrectSetkaPos(int a)
{
	static char count_resizing = 0;


	if (Wnd_Plot.setka.h_setka <= 3)
		Wnd_Plot.setka.h_setka = 3;
	else if (Wnd_Plot.setka.h_setka >= 20)
	{
		count_resizing++;
		Wnd_Plot.setka.h_setka = 10;
		Wnd_Plot.setka.u5_setka = Setka_unit(Wnd_Plot.setka.u5_setka / 2.1);
	}
	else if (Wnd_Plot.setka.h_setka < 10)
	{
		count_resizing++;
		Wnd_Plot.setka.h_setka = 19;
		Wnd_Plot.setka.u5_setka = Setka_unit(Wnd_Plot.setka.u5_setka * 2.1);
	}




	Wnd_Plot.setka.h5_setka = Wnd_Plot.setka.h_setka * 5;
	Wnd_Plot.setka.kxy_zoom = Wnd_Plot.setka.h5_setka / Wnd_Plot.setka.u5_setka;
	Wnd_Plot.setka.unit_to_pixel = 1.0 / Wnd_Plot.setka.kxy_zoom;
	Wnd_Plot.setka.mantissa = floor(log10(Wnd_Plot.setka.u5_setka));
	for (int i = 0; i < Wnd_Plot.plot.myvec_xy_picsel.size(); i++)
	{
		Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_zoom;
		Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_zoom;
	}

	Plotting_edges_upd(2);
	if (Wnd_Plot.setka.LLeft < Wnd_Plot.setka.Left_Wide_Vec || Wnd_Plot.setka.RRight > Wnd_Plot.setka.Right_Wide_Vec || count_resizing > 4)
	{
		Wnd_Plot.setka.Left_Wide_Vec = Wnd_Plot.setka.LLeft - (Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;
		Wnd_Plot.setka.Right_Wide_Vec = Wnd_Plot.setka.LLeft + (Wnd_Plot.setka.Wide_Vec / 2 - 1000) * Wnd_Plot.setka.unit_to_pixel;
		count_resizing = 0;
		RedrawPlot();
	}
	return;
}
void DrowSetka(HDC dc)
{
	SelectObject(dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(dc, RGB(255, 255, 255));
	Rectangle(dc, 0, 0, Wnd_Plot.sx, Wnd_Plot.sy);
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(214, 214, 214));
	Plotting_edges_upd(0);

	for (int ix = Wnd_Plot.x_LL; ix < Wnd_Plot.x_RR; ix += Wnd_Plot.setka.h_setka) {
		MoveToEx(dc, ix, Wnd_Plot.y_BB, NULL);
		LineTo(dc, ix, Wnd_Plot.y_TT);
	}
	for (int iy = Wnd_Plot.y_BB; iy < Wnd_Plot.y_TT; iy += Wnd_Plot.setka.h_setka) {
		MoveToEx(dc, Wnd_Plot.x_LL, iy, NULL);
		LineTo(dc, Wnd_Plot.x_RR, iy);
	}
	//рисуем большие клетки 
	SetDCPenColor(dc, RGB(150, 150, 150));
	for (int ix = Wnd_Plot.x_LL5; ix < Wnd_Plot.x_RR; ix += Wnd_Plot.setka.h5_setka) {
		MoveToEx(dc, ix, Wnd_Plot.y_BB5, NULL);
		LineTo(dc, ix, Wnd_Plot.y_TT);
	}
	for (int iy = Wnd_Plot.y_BB5; iy < Wnd_Plot.y_TT; iy += Wnd_Plot.setka.h5_setka) {
		MoveToEx(dc, Wnd_Plot.x_LL5, iy, NULL);
		LineTo(dc, Wnd_Plot.x_RR, iy);
	}
	//рисуем оси координат и кромку
	SetDCPenColor(dc, RGB(0, 0, 0));
	MoveToEx(dc, 0, Wnd_Plot.y_TT, NULL);
	LineTo(dc, 0, Wnd_Plot.y_BB);
	MoveToEx(dc, Wnd_Plot.x_LL, 0, NULL);
	LineTo(dc, Wnd_Plot.x_RR, 0);
}
void DrowCounts(HDC dc)
{
	HFONT hFont1 = CreateFont(11, 0, 0, 0, 600, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Lusida Console"));
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(0, 0, 0));
	SelectObject(dc, hFont1);
	SetBkMode(dc, TRANSPARENT);
	//рисуем числa
	//////////////////////////////////////////////////////////////////////
	Plotting_edges_upd(1);
	//уходим в отрицательное крайнее значение графика X
	int mantissa = 0; int zerocount = 0;
	if (abs(Wnd_Plot.setka.mantissa) > 1)
	{
		zerocount = 0;
		mantissa = Wnd_Plot.setka.mantissa;
	}
	else if (Wnd_Plot.setka.mantissa < 0)
	{
		mantissa = 0;
		zerocount = 1;
	}

	double ux = Wnd_Plot.setka.u5_setka * Wnd_Plot.x_LL5 / Wnd_Plot.setka.h5_setka / pow(10, mantissa);;
	TCHAR s[20];
	//проверка на вещественность иди целостность координат
	//if (Wnd_Plot.setka.u5_setka < 1)zerocount = abs(round(log10(Wnd_Plot.setka.u5_setka))) + 1;
	SetTextAlign(dc, TA_TOP | TA_CENTER);
	for (int ix = Wnd_Plot.x_LL5; ix < Wnd_Plot.x_RR - Wnd_Plot.setka.h5_setka; ix += Wnd_Plot.setka.h5_setka) {
		if (mantissa == 0)
			_stprintf(s, L"%.*lf", zerocount, ux);
		else
			_stprintf(s, L"%.*lf^[%d]", zerocount, ux, mantissa);

		if (abs(ix) < Wnd_Plot.setka.h_setka)
		{
			_stprintf(s, L"%d", 0);
			TextOutW(dc, ix + 10, -8, s, _tcslen(s));
		}
		else {

			TextOutW(dc, ix, (Wnd_Plot.y_TT - 10), s, _tcslen(s));//рисуем на топе доп координаты
			MoveToEx(dc, ix, (Wnd_Plot.y_TT - 10), NULL);
			LineTo(dc, ix, (Wnd_Plot.y_TT + 10));

			TextOutW(dc, ix, (Wnd_Plot.y_BB + 20), s, _tcslen(s));
			MoveToEx(dc, ix, (Wnd_Plot.y_BB - 10), NULL);
			LineTo(dc, ix, (Wnd_Plot.y_BB + 10));

			TextOutW(dc, ix, -10, s, _tcslen(s));
			MoveToEx(dc, ix, -10, NULL);
			LineTo(dc, ix, 10);
		}
		ux += Wnd_Plot.setka.u5_setka / pow(10, mantissa);
	}
	//уходим в отрицательное крайнее значение графика Y
	double uy = Wnd_Plot.setka.u5_setka * Wnd_Plot.y_BB5 / Wnd_Plot.setka.h5_setka / pow(10, mantissa);
	SetTextAlign(dc, TA_LEFT);
	for (int iy = Wnd_Plot.y_BB5; iy < Wnd_Plot.y_TT - Wnd_Plot.setka.h5_setka; iy += Wnd_Plot.setka.h5_setka) {
		if (mantissa == 0)
			_stprintf(s, L"%.*lf", zerocount, uy);
		else
			_stprintf(s, L"%.*lf^[%d]", zerocount, uy, mantissa);

		if (abs(iy) < Wnd_Plot.setka.h_setka) {}
		else {
			TextOutW(dc, 15, iy, s, _tcslen(s));
			MoveToEx(dc, 10, iy, NULL);
			LineTo(dc, -10, iy);

			TextOutW(dc, (Wnd_Plot.x_LL + 15), iy, s, _tcslen(s));
			MoveToEx(dc, (Wnd_Plot.x_LL + 10), iy, NULL);
			LineTo(dc, (Wnd_Plot.x_LL - 10), iy);

			TextOutW(dc, (Wnd_Plot.x_RR - 20), (iy + 5), s, _tcslen(s));
			MoveToEx(dc, (Wnd_Plot.x_RR + 10), iy, NULL);
			LineTo(dc, (Wnd_Plot.x_RR - 10), iy);
		}
		uy += Wnd_Plot.setka.u5_setka / pow(10, mantissa);
	}

	//рисуем кромочку
	MoveToEx(dc, Wnd_Plot.x_LL, Wnd_Plot.y_TT, NULL);
	LineTo(dc, Wnd_Plot.x_LL, Wnd_Plot.y_BB);
	MoveToEx(dc, Wnd_Plot.x_RR - 1, Wnd_Plot.y_TT, NULL);
	LineTo(dc, Wnd_Plot.x_RR - 1, Wnd_Plot.y_BB);

	DeleteObject(hFont1);
}
void DrowGraphSmooth(HDC dc)
{
	Gdiplus::Graphics* graph = new (Gdiplus::Graphics)(dc);
	Gdiplus::Bitmap* buffer = new (Gdiplus::Bitmap)(Wnd_Plot.sx, Wnd_Plot.sy);
	Gdiplus::Graphics* myGraphics = new (Gdiplus::Graphics)(buffer);
	myGraphics->SetSmoothingMode(SmoothingModeAntiAlias);
	Pen* myPen = new Pen(Color(1000, 255, 0, 0), 2);
	int i = 0;
	while (Wnd_Plot.plot.myvec_xy[i].x < Wnd_Plot.setka.LLeft)
	{
		++i;
	}
	int j = i;
	while (Wnd_Plot.plot.myvec_xy[j].x < Wnd_Plot.setka.RRight)
	{
		++j;
	}

	for (; i < j; i++)
	{
		if (isnan(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) {
			i++; continue;
		}
		myGraphics->DrawLine(myPen,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i - 1].x)) + Wnd_Plot.setka.sx_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) * (-1) + Wnd_Plot.setka.sy_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i].x)) + Wnd_Plot.setka.sx_center,
			((int)(Wnd_Plot.plot.myvec_xy_picsel[i].y)) * (-1) + Wnd_Plot.setka.sy_center);
	}

	Gdiplus::CachedBitmap  cBitmap(buffer, graph);
	graph->DrawCachedBitmap(&cBitmap, 0, 0);
	delete buffer;
	delete graph;
	delete myGraphics;
	delete myPen;
}
void DrowGraph(HDC dc)
{
	SelectObject(dc, CreatePen(PS_SOLID, 5, RGB(255, 0, 50)));
	int i = 0;
	while (Wnd_Plot.plot.myvec_xy[i].x < Wnd_Plot.setka.LLeft)
	{
		++i;
	}
	int j = i;
	while (Wnd_Plot.plot.myvec_xy[j].x < Wnd_Plot.setka.RRight)
	{
		++j;
	}

	for (; i < j; i++)
	{

		if (isnan(Wnd_Plot.plot.myvec_xy_picsel[i - 1].y)) {
			i++; continue;
		}
		MoveToEx(dc, Wnd_Plot.plot.myvec_xy_picsel[i - 1].x, Wnd_Plot.plot.myvec_xy_picsel[i - 1].y, NULL);
		LineTo(dc, Wnd_Plot.plot.myvec_xy_picsel[i].x, Wnd_Plot.plot.myvec_xy_picsel[i].y);
	}
}
void Plotting_edges_upd(int draw_h5_inside_or_not)
{
	switch (draw_h5_inside_or_not)
	{
	case 0:
		//КООРДИНАТЫ СЕТОЧНЫХ КРАЕВ
		Wnd_Plot.x_LL = -(Wnd_Plot.setka.sx_center / Wnd_Plot.setka.h_setka + 1) * Wnd_Plot.setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot.y_BB = -((Wnd_Plot.sy - Wnd_Plot.setka.sy_center + 1) / Wnd_Plot.setka.h_setka) * Wnd_Plot.setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot.x_RR = Wnd_Plot.sx - Wnd_Plot.setka.sx_center;//граница правая
		Wnd_Plot.y_TT = Wnd_Plot.setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев большой сетки
		Wnd_Plot.x_LL5 = ((Wnd_Plot.x_LL / Wnd_Plot.setka.h5_setka) - 1) * Wnd_Plot.setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot.y_BB5 = ((Wnd_Plot.y_BB / Wnd_Plot.setka.h5_setka) - 1) * Wnd_Plot.setka.h5_setka;

		break;
	case 1:
		//КООРДИНАТЫ КРАЕВ
		Wnd_Plot.x_LL = -(Wnd_Plot.setka.sx_center);//**приведение типов -  координаты
		Wnd_Plot.y_BB = -(Wnd_Plot.sy - Wnd_Plot.setka.sy_center);//**приведение типов -  координаты
		Wnd_Plot.x_RR = Wnd_Plot.sx - Wnd_Plot.setka.sx_center;//граница правая
		Wnd_Plot.y_TT = Wnd_Plot.setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев
		Wnd_Plot.x_LL5 = ((Wnd_Plot.x_LL / Wnd_Plot.setka.h5_setka) + 1) * Wnd_Plot.setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot.y_BB5 = ((Wnd_Plot.y_BB / Wnd_Plot.setka.h5_setka) + 1) * Wnd_Plot.setka.h5_setka;
		break;
	case 2:
		Plotting_edges_upd(1);
		Wnd_Plot.setka.LLeft = Wnd_Plot.x_LL * Wnd_Plot.setka.unit_to_pixel;
		Wnd_Plot.setka.RRight = Wnd_Plot.x_RR * Wnd_Plot.setka.unit_to_pixel;
		Wnd_Plot.setka.TTop = Wnd_Plot.y_TT * Wnd_Plot.setka.unit_to_pixel;
		Wnd_Plot.setka.BBottom = Wnd_Plot.y_BB * Wnd_Plot.setka.unit_to_pixel;

		break;
	}
	return;
}
void FirstPlotting()
{

	Wnd_Plot.plot.myvec_xy_picsel.clear();
	Wnd_Plot.plot.myvec_xy.clear();
	Pointer point;
	long double y;
	int i = 0;
	for (double x = Wnd_Plot.setka.Left_Wide_Vec;
		x < Wnd_Plot.setka.Right_Wide_Vec;
		x += Wnd_Plot.setka.unit_to_pixel) {
		point.x = x;
		try {
			y = Function_String_to_Double(Wnd_Plot.text_, &x);
			point.y = y;
		}
		catch (double err)
		{
			point.y = err;
		}

		Wnd_Plot.plot.myvec_xy.push_back(point);
		++i;
	}

	for (int i = 0; i < Wnd_Plot.plot.myvec_xy.size(); i++)
	{
		Wnd_Plot.plot.myvec_xy_picsel.push_back({});
		Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_zoom;
		Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_zoom;
	}
}
void RedrawPlot()
{
	if (strlen(Wnd_Plot.text_) == 0) return;
	Wnd_Plot.plot.myvec_xy_picsel.clear();
	Wnd_Plot.plot.myvec_xy.clear();
	Pointer point;
	long double y;
	int i = 0;
	for (double x = Wnd_Plot.setka.Left_Wide_Vec;
		x < Wnd_Plot.setka.Right_Wide_Vec;
		x += Wnd_Plot.setka.unit_to_pixel) {
		point.x = x;
		try {
			y = Function_String_to_Double(Wnd_Plot.text_, &x);
			point.y = y;
		}
		catch (double err)
		{
			point.y = NAN;
		}

		Wnd_Plot.plot.myvec_xy.push_back(point);
		++i;
	}

	for (int i = 0; i < Wnd_Plot.plot.myvec_xy.size(); i++)
	{
		Wnd_Plot.plot.myvec_xy_picsel.push_back({});
		Wnd_Plot.plot.myvec_xy_picsel[i].x = Wnd_Plot.plot.myvec_xy[i].x * Wnd_Plot.setka.kxy_zoom;
		Wnd_Plot.plot.myvec_xy_picsel[i].y = Wnd_Plot.plot.myvec_xy[i].y * Wnd_Plot.setka.kxy_zoom;
	}
}
