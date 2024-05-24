#include "Plotting.h"
#include "Custom_for_nice_veiw.h"
#include "Main_files/main_header.h"

#define MoveToEx(a, x, y, d); MoveToEx(a, x + Wnd_Plot->setka.sx_center, y*(-1) + Wnd_Plot->setka.sy_center, d);
#define LineTo(a, x, y); LineTo(a, x + Wnd_Plot->setka.sx_center, y*(-1) + Wnd_Plot->setka.sy_center);
#define TextOutW(dc, x, y, s, st); TextOutW(dc, x + Wnd_Plot->setka.sx_center, y*(-1) + Wnd_Plot->setka.sy_center, s, st);

void DrowSetka(HDC dc, Wnd_Plot_struct* Wnd_Plot)
{
	SelectObject(dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(dc, BCKGRND_SETKA_COLOR);
	Rectangle(dc, 0, 0, Wnd_Plot->sx, Wnd_Plot->sy);
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, SMALL_SETKA_SQARE_COLOR);
	Plotting_edges_upd(0,Wnd_Plot);

	for (int ix = Wnd_Plot->setka.p_x_Left; ix < Wnd_Plot->setka.p_x_Right; ix += Wnd_Plot->setka.h_setka) {
		MoveToEx(dc, ix, Wnd_Plot->setka.p_y_Bottom, NULL);
		LineTo(dc, ix, Wnd_Plot->setka.p_y_Top);
	}
	for (int iy = Wnd_Plot->setka.p_y_Bottom; iy < Wnd_Plot->setka.p_y_Top; iy += Wnd_Plot->setka.h_setka) {
		MoveToEx(dc, Wnd_Plot->setka.p_x_Left, iy, NULL);
		LineTo(dc, Wnd_Plot->setka.p_x_Right, iy);
	}
	//рисуем большие клетки 
	SetDCPenColor(dc, BIG_SETKA_SQARE_COLOR);
	for (int ix = Wnd_Plot->setka.p_x_LLeft5; ix < Wnd_Plot->setka.p_x_Right; ix += Wnd_Plot->setka.h5_setka) {
		MoveToEx(dc, ix, Wnd_Plot->setka.p_y_BBottom5, NULL);
		LineTo(dc, ix, Wnd_Plot->setka.p_y_Top);
	}
	for (int iy = Wnd_Plot->setka.p_y_BBottom5; iy < Wnd_Plot->setka.p_y_Top; iy += Wnd_Plot->setka.h5_setka) {
		MoveToEx(dc, Wnd_Plot->setka.p_x_LLeft5, iy, NULL);
		LineTo(dc, Wnd_Plot->setka.p_x_Right, iy);
	}
	//рисуем оси координат и кромку
	SetDCPenColor(dc, OSI_SETKA_COLOR);
	MoveToEx(dc, 0, Wnd_Plot->setka.p_y_Top, NULL);
	LineTo(dc, 0, Wnd_Plot->setka.p_y_Bottom);
	MoveToEx(dc, Wnd_Plot->setka.p_x_Left, 0, NULL);
	LineTo(dc, Wnd_Plot->setka.p_x_Right, 0);
}
void DrowCounts(HDC dc, Wnd_Plot_struct* Wnd_Plot, HFONT* hFont)
{

	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, OSI_SETKA_COLOR);
	SelectObject(dc, *hFont);
	SetBkMode(dc, TRANSPARENT);
	//рисуем числa
	//////////////////////////////////////////////////////////////////////
	Plotting_edges_upd(1,Wnd_Plot);
	//уходим в отрицательное крайнее значение графика X
	int mantissa = 0; int zerocount = 0;
	if (abs(Wnd_Plot->setka.mantissa) > 1)
	{
		zerocount = 0;
		mantissa = Wnd_Plot->setka.mantissa;
	}
	else if (Wnd_Plot->setka.mantissa < 0)
	{
		mantissa = 0;
		zerocount = 1;
	}

	double ux = Wnd_Plot->setka.u5_setka * Wnd_Plot->setka.p_x_LLeft5 / Wnd_Plot->setka.h5_setka / pow(10, mantissa);;
	WCHAR str_[20];
	//проверка на вещественность иди целостность координат
	//if (Wnd_Plot->setka.u5_setka < 1)zerocount = abs(round(log10(Wnd_Plot->setka.u5_setka))) + 1;
	SetTextAlign(dc, TA_TOP | TA_CENTER);
	
	if (Wnd_Plot->setka.p_x_Left - Wnd_Plot->setka.p_x_LLeft5 > Wnd_Plot->setka.h5_setka / 2) 
		Wnd_Plot->setka.p_x_LLeft5 = ((Wnd_Plot->setka.p_x_Left / Wnd_Plot->setka.h5_setka)) * Wnd_Plot->setka.h5_setka;
	for (int ix = Wnd_Plot->setka.p_x_LLeft5;
		ix < Wnd_Plot->setka.p_x_Right - Wnd_Plot->setka.h5_setka/2;
		ix += Wnd_Plot->setka.h5_setka) {
		if (mantissa == 0)
			swprintf(str_, L"%.*lf", zerocount, ux);
		else
			swprintf(str_, L"%.*lf^[%d]", zerocount, ux, mantissa);

		if (abs(ix) < Wnd_Plot->setka.h_setka)
		{
			swprintf(str_, L"%d", 0);
			TextOutW(dc, ix + 10, -8, str_, wcslen(str_));
		}
		else {

			TextOutW(dc, ix, (Wnd_Plot->setka.p_y_Top - 10), str_, wcslen(str_));//рисуем на топе доп координаты
			MoveToEx(dc, ix, (Wnd_Plot->setka.p_y_Top - 10), NULL);
			LineTo(dc, ix, (Wnd_Plot->setka.p_y_Top + 10));

			TextOutW(dc, ix, (Wnd_Plot->setka.p_y_Bottom + 20), str_, wcslen(str_));
			MoveToEx(dc, ix, (Wnd_Plot->setka.p_y_Bottom - 10), NULL);
			LineTo(dc, ix, (Wnd_Plot->setka.p_y_Bottom + 10));

			TextOutW(dc, ix, -10, str_, wcslen(str_));
			MoveToEx(dc, ix, -10, NULL);
			LineTo(dc, ix, 10);
		}
		ux += Wnd_Plot->setka.u5_setka / pow(10, mantissa);
	}
	//уходим в отрицательное крайнее значение графика Y
	double uy = Wnd_Plot->setka.u5_setka * Wnd_Plot->setka.p_y_BBottom5 / Wnd_Plot->setka.h5_setka / pow(10, mantissa);
	SetTextAlign(dc, TA_LEFT);
	if (Wnd_Plot->setka.p_y_Bottom - Wnd_Plot->setka.p_y_BBottom5 > Wnd_Plot->setka.h5_setka / 2)
		Wnd_Plot->setka.p_y_BBottom5 = ((Wnd_Plot->setka.p_y_Bottom / Wnd_Plot->setka.h5_setka)) * Wnd_Plot->setka.h5_setka;
	for (int iy = Wnd_Plot->setka.p_y_BBottom5; iy < Wnd_Plot->setka.p_y_Top - Wnd_Plot->setka.h5_setka/2; iy += Wnd_Plot->setka.h5_setka) {
		if (mantissa == 0)
			swprintf(str_, L"%.*lf", zerocount, uy);
		else
			swprintf(str_, L"%.*lf^[%d]", zerocount, uy, mantissa);

		if (abs(iy) < Wnd_Plot->setka.h_setka) {}
		else {
			TextOutW(dc, 15, iy, str_, wcslen(str_));
			MoveToEx(dc, 10, iy, NULL);
			LineTo(dc, -10, iy);

			TextOutW(dc, (Wnd_Plot->setka.p_x_Left + 15), iy, str_, wcslen(str_));
			MoveToEx(dc, (Wnd_Plot->setka.p_x_Left + 10), iy, NULL);
			LineTo(dc, (Wnd_Plot->setka.p_x_Left - 10), iy);

			TextOutW(dc, (Wnd_Plot->setka.p_x_Right - 20), (iy + 5), str_, wcslen(str_));
			MoveToEx(dc, (Wnd_Plot->setka.p_x_Right + 10), iy, NULL);
			LineTo(dc, (Wnd_Plot->setka.p_x_Right - 10), iy);
		}
		uy += Wnd_Plot->setka.u5_setka / pow(10, mantissa);
	}

	//рисуем кромочку
	MoveToEx(dc, Wnd_Plot->setka.p_x_Left, Wnd_Plot->setka.p_y_Top, NULL);
	LineTo(dc, Wnd_Plot->setka.p_x_Left, Wnd_Plot->setka.p_y_Bottom);
	MoveToEx(dc, Wnd_Plot->setka.p_x_Right - 1, Wnd_Plot->setka.p_y_Top, NULL);
	LineTo(dc, Wnd_Plot->setka.p_x_Right - 1, Wnd_Plot->setka.p_y_Bottom);
}
void DrowGraphSmooth(HDC dc, Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot, Gdiplus::Pen* Pen_for_plot)
{
	Gdiplus::Graphics* graph = new (Gdiplus::Graphics)(dc);
	Gdiplus::Bitmap* buffer = new (Gdiplus::Bitmap)(Wnd_Plot->sx, Wnd_Plot->sy);
	Gdiplus::Graphics* myGraphics = new (Gdiplus::Graphics)(buffer);
	myGraphics->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	int size = Myplot.myvec_xy.size() - 1;
	int j = 0, i = 1;
	if (Myplot.Redraw == ALLOW) {

		while (Myplot.myvec_xy[i].x < Wnd_Plot->setka.u_x_Left && i < size)
		{
			++i;
		}
		j = i;
		while (Myplot.myvec_xy[j].x < Wnd_Plot->setka.u_x_Right && j < size)
		{
			++j;
		}
	}
	else {
     j = Myplot.picsel.size();
	}

	for (; i < j; i++)
	{
		if (isnan(Myplot.myvec_xy[i - 1].y)) {
			i++; continue;
		}
		myGraphics->DrawLine(Pen_for_plot,
			((int)(Myplot.picsel[i - 1].x)) + Wnd_Plot->setka.sx_center,
			((int)(Myplot.picsel[i - 1].y)) * (-1) + Wnd_Plot->setka.sy_center,
			((int)(Myplot.picsel[i].x)) + Wnd_Plot->setka.sx_center,
			((int)(Myplot.picsel[i].y)) * (-1) + Wnd_Plot->setka.sy_center);
	}
	Gdiplus::CachedBitmap  cBitmap(buffer, graph);
	graph->DrawCachedBitmap(&cBitmap, 0, 0);
	delete buffer;
	delete graph;
	delete myGraphics;
}
void DrowGraph(HDC dc, Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{
	SelectObject(dc, CreatePen(PS_SOLID, 5, RGB(255, 0, 50)));
	int i = 0;
	while (Myplot.myvec_xy[i].x < Wnd_Plot->setka.u_x_Left)
	{
		++i;
	}
	int j = i;
	while (Myplot.myvec_xy[j].x < Wnd_Plot->setka.u_x_Right)
	{
		++j;
	}

	for (; i < j; i++)
	{

		if (isnan(Myplot.myvec_xy[i - 1].y)) {
			i++; continue;
		}
		MoveToEx(dc, Myplot.picsel[i - 1].x, Myplot.picsel[i - 1].y, NULL);
		LineTo(dc, Myplot.picsel[i].x, Myplot.picsel[i].y);
	}
}
