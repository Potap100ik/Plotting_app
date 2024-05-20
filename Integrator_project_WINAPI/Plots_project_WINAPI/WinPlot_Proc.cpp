#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"

MyWnd_Plot* Wnd_Plot;
Ploting_struct Myplot;

void MainPlot_Init(HWND hWnd_MainPlot)
{
	Wnd_Plot->hWnd = hWnd_MainPlot;
	StructPlotInit(Wnd_Plot, Myplot);
}
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	static MouseMove MyMouse;//отслеживание передвижения мыщц мыши

	PAINTSTRUCT  ps2;
	HDC memdc;
	HBITMAP membit;
	HDC hdc2{};
	static Gdiplus::Pen* Pen_for_plot;
	static HFONT hFont1;

	switch (message)
	{
	case WM_CREATE:
	{
		Pen_for_plot = GetPen_for_Main_Plot();

		Wnd_Plot = (MyWnd_Plot*)malloc(sizeof(Wnd_Plot_struct));

		MousePos(FALSE, 0, 0, MyMouse);

		hFont1 = CreateFont(11, 0, 0, 0, 600, 0, 0, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Lusida Console");
	}return 0;
	case WM_LBUTTONDOWN:
	{
		MousePos(TRUE, LOWORD(lParam), HIWORD(lParam), MyMouse);
	}return 0;
	case WM_MOUSEMOVE:
	{
		if (MyMouse.Flag_for_mouse)
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			Wnd_Plot->setka.sx_center += x - MyMouse.Prev_mouse_point.x;
			Wnd_Plot->setka.sy_center += y - MyMouse.Prev_mouse_point.y;

			MyMouse.Prev_mouse_point.x = x;
			MyMouse.Prev_mouse_point.y = y;

			Plotting_edges_upd(2, Wnd_Plot);
			if (Wnd_Plot->setka.u_x_Left < Wnd_Plot->setka.Left_Wide_Vec_UNIT || Wnd_Plot->setka.u_x_Right > Wnd_Plot->setka.Right_Wide_Vec_UNIT)
			{
				Wide_for_vector_upd(Wnd_Plot, Myplot);
			}
			InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);
		}
	}return 0;
	case WM_DRAW_MAIN_PLOT:
	{
		Wnd_Plot->text_ = (LPSTR)wParam;
		Plotting_edges_upd(2, Wnd_Plot);//ОБНОВЛЯЕМ ГРАНИЦЫ ПИКСЕЛЬНЫЕ ДЛЯ ТОГО, ЧТОБЫ ПОНЯТЬ...................
		FirstPlotting(Wnd_Plot, Myplot);
//#ifdef VECTOR_OUT
//		{
//			int i = 0;
//			printf("Инициация построения графика\n");
//			for (Pointer it : Myplot.myvec_xy)
//			{
//				printf("%5d)x = %10.6lf y = %10.6lf\n", i, it.x, it.y);
//				i++;
//			}
//		}
//#endif //VECTOR_OUT
	}return 0;	
	case WM_HOME_BTN_CLICKED:
	{
		Wnd_Plot->setka.sx_center = Wnd_Plot->sx / 2;
		Wnd_Plot->setka.sy_center = Wnd_Plot->sy / 2;
		SetkaStructUpdate(Wnd_Plot, BASE_H_SETKA, BASE_U5_SETKA);
		CorrectSetkaPos(Wnd_Plot, Myplot, MIN_H_SETKA, MAX_H_SETKA, BASE_H_SETKA);
		Wide_for_vector_upd(Wnd_Plot, Myplot);
	}return 0;
	case WM_CLEAR_PLOT:
	{
		Myplot.picsel.clear();
		Myplot.myvec_xy.clear();
		Wnd_Plot->text_ = (LPSTR)"";
	}return 0;
	case WM_LBUTTONUP:
	{
		MyMouse.Flag_for_mouse = FALSE;
	}return 0;
	case WM_MOUSEWHEEL:
	{
		int a = Wnd_Plot->setka.h_setka;
		Wnd_Plot->setka.h_setka += GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		CorrectSetkaPos(Wnd_Plot, Myplot, MIN_H_SETKA, MAX_H_SETKA, BASE_H_SETKA);
		//RedrawPlot(Wnd_Plot, Myplot);
		InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE);
	}return 0;
	case WM_SIZE:
	{
		Wnd_Plot->sx = LOWORD(lParam);
		Wnd_Plot->sy = HIWORD(lParam);
	}return 0;
	case WM_RESIZE_PLOT:
	{
		CorrectSetkaPos(Wnd_Plot, Myplot, MIN_H_SETKA, MAX_H_SETKA, BASE_H_SETKA);
	}return 0;
	case WM_ERASEBKGND:return 1;
	case WM_PAINT:
	{
		//SimpleTimer timer;
		hdc2 = BeginPaint(Wnd_Plot->hWnd, &ps2);
		memdc = CreateCompatibleDC(hdc2);
		membit = CreateCompatibleBitmap(hdc2, Wnd_Plot->sx, Wnd_Plot->sy);
		SelectObject(memdc, membit);
		DrowSetka(memdc, Wnd_Plot);
		DrowCounts(memdc, Wnd_Plot, &hFont1);
		if (!Myplot.picsel.empty())
		{
			DrowGraphSmooth(memdc, Wnd_Plot, Myplot, Pen_for_plot);
			//DrowGraph(memdc, Wnd_Plot);оставим для экспериментов - рисование без GDI+
		}

		BitBlt(hdc2, 0, 0, Wnd_Plot->sx * 2, Wnd_Plot->sy * 2, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(membit);
		EndPaint(Wnd_Plot->hWnd, &ps2);
	}return 0;
	case WM_DESTROY:
	{
		free(Wnd_Plot);
		Myplot.picsel.clear();
		Myplot.myvec_xy.clear();
		//delete Pen_for_plot;
		DeleteObject(hFont1);
		PostQuitMessage(0);
	}return 0;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
