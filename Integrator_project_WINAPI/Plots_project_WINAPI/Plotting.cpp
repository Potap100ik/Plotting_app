#include "Plotting.h"

void DrowSetka(HDC dc, Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{
	SelectObject(dc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(dc, RGB(255, 255, 255));
	Rectangle(dc, 0, 0, Wnd_Plot->sx, Wnd_Plot->sy);
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(214, 214, 214));
	Plotting_edges_upd(0,Wnd_Plot, Myplot);

	for (int ix = Wnd_Plot->x_LL; ix < Wnd_Plot->x_RR; ix += Wnd_Plot->setka.h_setka) {
		MoveToEx(dc, ix, Wnd_Plot->y_BB, NULL);
		LineTo(dc, ix, Wnd_Plot->y_TT);
	}
	for (int iy = Wnd_Plot->y_BB; iy < Wnd_Plot->y_TT; iy += Wnd_Plot->setka.h_setka) {
		MoveToEx(dc, Wnd_Plot->x_LL, iy, NULL);
		LineTo(dc, Wnd_Plot->x_RR, iy);
	}
	//������ ������� ������ 
	SetDCPenColor(dc, RGB(150, 150, 150));
	for (int ix = Wnd_Plot->x_LL5; ix < Wnd_Plot->x_RR; ix += Wnd_Plot->setka.h5_setka) {
		MoveToEx(dc, ix, Wnd_Plot->y_BB5, NULL);
		LineTo(dc, ix, Wnd_Plot->y_TT);
	}
	for (int iy = Wnd_Plot->y_BB5; iy < Wnd_Plot->y_TT; iy += Wnd_Plot->setka.h5_setka) {
		MoveToEx(dc, Wnd_Plot->x_LL5, iy, NULL);
		LineTo(dc, Wnd_Plot->x_RR, iy);
	}
	//������ ��� ��������� � ������
	SetDCPenColor(dc, RGB(0, 0, 0));
	MoveToEx(dc, 0, Wnd_Plot->y_TT, NULL);
	LineTo(dc, 0, Wnd_Plot->y_BB);
	MoveToEx(dc, Wnd_Plot->x_LL, 0, NULL);
	LineTo(dc, Wnd_Plot->x_RR, 0);
}
void DrowCounts(HDC dc, Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{
	HFONT hFont1 = CreateFont(11, 0, 0, 0, 600, 0, 0, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Lusida Console"));
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(0, 0, 0));
	SelectObject(dc, hFont1);
	SetBkMode(dc, TRANSPARENT);
	//������ ����a
	//////////////////////////////////////////////////////////////////////
	Plotting_edges_upd(1,Wnd_Plot, Myplot);
	//������ � ������������� ������� �������� ������� X
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

	double ux = Wnd_Plot->setka.u5_setka * Wnd_Plot->x_LL5 / Wnd_Plot->setka.h5_setka / pow(10, mantissa);;
	TCHAR s[20];
	//�������� �� �������������� ��� ����������� ���������
	//if (Wnd_Plot->setka.u5_setka < 1)zerocount = abs(round(log10(Wnd_Plot->setka.u5_setka))) + 1;
	SetTextAlign(dc, TA_TOP | TA_CENTER);
	for (int ix = Wnd_Plot->x_LL5; ix < Wnd_Plot->x_RR - Wnd_Plot->setka.h5_setka; ix += Wnd_Plot->setka.h5_setka) {
		if (mantissa == 0)
			_stprintf(s, L"%.*lf", zerocount, ux);
		else
			_stprintf(s, L"%.*lf^[%d]", zerocount, ux, mantissa);

		if (abs(ix) < Wnd_Plot->setka.h_setka)
		{
			_stprintf(s, L"%d", 0);
			TextOutW(dc, ix + 10, -8, s, _tcslen(s));
		}
		else {

			TextOutW(dc, ix, (Wnd_Plot->y_TT - 10), s, _tcslen(s));//������ �� ���� ��� ����������
			MoveToEx(dc, ix, (Wnd_Plot->y_TT - 10), NULL);
			LineTo(dc, ix, (Wnd_Plot->y_TT + 10));

			TextOutW(dc, ix, (Wnd_Plot->y_BB + 20), s, _tcslen(s));
			MoveToEx(dc, ix, (Wnd_Plot->y_BB - 10), NULL);
			LineTo(dc, ix, (Wnd_Plot->y_BB + 10));

			TextOutW(dc, ix, -10, s, _tcslen(s));
			MoveToEx(dc, ix, -10, NULL);
			LineTo(dc, ix, 10);
		}
		ux += Wnd_Plot->setka.u5_setka / pow(10, mantissa);
	}
	//������ � ������������� ������� �������� ������� Y
	double uy = Wnd_Plot->setka.u5_setka * Wnd_Plot->y_BB5 / Wnd_Plot->setka.h5_setka / pow(10, mantissa);
	SetTextAlign(dc, TA_LEFT);
	for (int iy = Wnd_Plot->y_BB5; iy < Wnd_Plot->y_TT - Wnd_Plot->setka.h5_setka; iy += Wnd_Plot->setka.h5_setka) {
		if (mantissa == 0)
			_stprintf(s, L"%.*lf", zerocount, uy);
		else
			_stprintf(s, L"%.*lf^[%d]", zerocount, uy, mantissa);

		if (abs(iy) < Wnd_Plot->setka.h_setka) {}
		else {
			TextOutW(dc, 15, iy, s, _tcslen(s));
			MoveToEx(dc, 10, iy, NULL);
			LineTo(dc, -10, iy);

			TextOutW(dc, (Wnd_Plot->x_LL + 15), iy, s, _tcslen(s));
			MoveToEx(dc, (Wnd_Plot->x_LL + 10), iy, NULL);
			LineTo(dc, (Wnd_Plot->x_LL - 10), iy);

			TextOutW(dc, (Wnd_Plot->x_RR - 20), (iy + 5), s, _tcslen(s));
			MoveToEx(dc, (Wnd_Plot->x_RR + 10), iy, NULL);
			LineTo(dc, (Wnd_Plot->x_RR - 10), iy);
		}
		uy += Wnd_Plot->setka.u5_setka / pow(10, mantissa);
	}

	//������ ��������
	MoveToEx(dc, Wnd_Plot->x_LL, Wnd_Plot->y_TT, NULL);
	LineTo(dc, Wnd_Plot->x_LL, Wnd_Plot->y_BB);
	MoveToEx(dc, Wnd_Plot->x_RR - 1, Wnd_Plot->y_TT, NULL);
	LineTo(dc, Wnd_Plot->x_RR - 1, Wnd_Plot->y_BB);

	DeleteObject(hFont1);
}
void DrowGraphSmooth(HDC dc, Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{
	Gdiplus::Graphics* graph = new (Gdiplus::Graphics)(dc);
	Gdiplus::Bitmap* buffer = new (Gdiplus::Bitmap)(Wnd_Plot->sx, Wnd_Plot->sy);
	Gdiplus::Graphics* myGraphics = new (Gdiplus::Graphics)(buffer);
	myGraphics->SetSmoothingMode(SmoothingModeAntiAlias);
	Pen* myPen = new Pen(Color(1000, 255, 0, 0), 2);
	int i = 0;
	while (Myplot.myvec_xy[i].x < Wnd_Plot->setka.LLeft)
	{
		++i;
	}
	int j = i;
	while (Myplot.myvec_xy[j].x < Wnd_Plot->setka.RRight)
	{
		++j;
	}

	for (; i < j; i++)
	{
		if (isnan(Myplot.picsel[i - 1].y)) {
			i++; continue;
		}
		myGraphics->DrawLine(myPen,
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
	delete myPen;
}
void DrowGraph(HDC dc, Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{
	SelectObject(dc, CreatePen(PS_SOLID, 5, RGB(255, 0, 50)));
	int i = 0;
	while (Myplot.myvec_xy[i].x < Wnd_Plot->setka.LLeft)
	{
		++i;
	}
	int j = i;
	while (Myplot.myvec_xy[j].x < Wnd_Plot->setka.RRight)
	{
		++j;
	}

	for (; i < j; i++)
	{

		if (isnan(Myplot.picsel[i - 1].y)) {
			i++; continue;
		}
		MoveToEx(dc, Myplot.picsel[i - 1].x, Myplot.picsel[i - 1].y, NULL);
		LineTo(dc, Myplot.picsel[i].x, Myplot.picsel[i].y);
	}
}
