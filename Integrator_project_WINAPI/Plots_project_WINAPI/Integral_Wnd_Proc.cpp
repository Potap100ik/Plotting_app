#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"


MyWnd_Plot* Wnd_Integral;
Integral_struct Myintegr;

void WND_Integral_Init(HWND hWnd_Integer_Wnd, LPSTR text_, double A, double B, double H)
{
	Wnd_Integral->hWnd = hWnd_Integer_Wnd;
	Wnd_Integral->text_ = text_;
	Myintegr.A = A;
	Myintegr.B = B;
	Myintegr.H = H;
	//////////////////////////////////////////////
	StructIntegralInit(Wnd_Integral,Myintegr);
	FirstPlotting(Wnd_Integral, Myintegr.vec);
#ifdef VECTOR_OUT
	{
		int i = 0;
		printf("Инициация построения графика\n");
		for (Pointer it : Myintegr.vec.myvec_xy)
		{
			printf("%5d)x = %10.6lf y = %10.6lf\n", i, it.x, it.y);
			i++;
		}
	}
#endif //VECTOR_OUT
	//////////////////////////////////////////////
	double correct_x = 0, correct_y = 0;
	double size_of_plot = FillIntegralVector(Myintegr, Wnd_Integral, correct_x, correct_y);
#ifdef VECTOR_OUT
	{
		int i = 0;
		printf("Инициация построения графика\n");
		for (Pointer it : Myintegr.integral_plot.myvec_xy)
		{
			printf("%5d)x = %10.6lf y = %10.6lf\n", i, it.x, it.y);
			i++;
		}
	}
#endif //VECTOR_OUT

	Wnd_Integral->setka.u5_setka = Setka_UNIT_CHANGE(size_of_plot / KOL_OF_SETKA_SQARES5);

	//CorrectSetkaPos(Wnd_Integral, Myintegr.vec);
	CorrectSetkaPos(Wnd_Integral, Myintegr.integral_plot,MIN_H_SETKA_INT,MAX_H_SETKA_INT,BASE_H_SETKA_INT);
	//Wnd_Integral->setka.sx_center = Wnd_Integral->sx / 2 - correct_x * Wnd_Integral->setka.kxy_zoom;
	//Wnd_Integral->setka.sy_center = Wnd_Integral->sy / 2 - correct_y * Wnd_Integral->setka.kxy_zoom;
}
LRESULT CALLBACK Integral_Wnd_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	///////////////////////////////////////////////////
	PAINTSTRUCT ps2;
	HDC memdc;
	HBITMAP membit;
	HDC hdc2{};
	static MouseMove MyMouse;
	static Gdiplus::Pen* Pen_for_INTEGRAL;
	static HFONT hFont1;
	///////////////////////////////////////////////////
	switch (message)
	{
	case WM_CREATE:
	{
		Pen_for_INTEGRAL = GetPen_for_Integral();

		Wnd_Integral = (MyWnd_Plot*)malloc(sizeof(Wnd_Plot_struct));

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

			Wnd_Integral->setka.sx_center += x - MyMouse.Prev_mouse_point.x;
			Wnd_Integral->setka.sy_center += y - MyMouse.Prev_mouse_point.y;

			MyMouse.Prev_mouse_point.x = x;
			MyMouse.Prev_mouse_point.y = y;

			Plotting_edges_upd(2, Wnd_Integral);
			InvalidateRect(Wnd_Integral->hWnd, NULL, TRUE);
		}

	}return 0;
	case WM_LBUTTONUP:
	{
		MyMouse.Flag_for_mouse = FALSE;
	}return 0;
	case WM_MOUSEWHEEL:
	{
		int a = Wnd_Integral->setka.h_setka;
		Wnd_Integral->setka.h_setka += GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		CorrectSetkaPos(Wnd_Integral, Myintegr.integral_plot, MIN_H_SETKA_INT, MAX_H_SETKA_INT, BASE_H_SETKA_INT);
		InvalidateRect(Wnd_Integral->hWnd, NULL, TRUE);
	}return 0;
	case WM_SIZE:
	{
		Wnd_Integral->sx = LOWORD(lParam);
		Wnd_Integral->sy = HIWORD(lParam);
	}return 0;
	case WM_ERASEBKGND:return 1;//не надо белым закрашивать при перерисовке целое окно
	case WM_PAINT:
	{
		//SimpleTimer timer;

		hdc2 = BeginPaint(Wnd_Integral->hWnd, &ps2);
		memdc = CreateCompatibleDC(hdc2);
		membit = CreateCompatibleBitmap(hdc2, Wnd_Integral->sx, Wnd_Integral->sy);
		SelectObject(memdc, membit);
		DrowSetka(memdc, Wnd_Integral);
		DrowCounts(memdc, Wnd_Integral, &hFont1);

		DrowGraphSmooth(memdc, Wnd_Integral, Myintegr.integral_plot, Pen_for_INTEGRAL);

		BitBlt(hdc2, 0, 0, Wnd_Integral->sx * 2, Wnd_Integral->sy * 2, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(membit);
		EndPaint(Wnd_Integral->hWnd, &ps2);
	}return 0;
	case WM_DESTROY:
	{
		Myintegr.A = NULL;
		Myintegr.B = NULL;
		Myintegr.H = NULL;
		Myintegr.integral_plot.myvec_xy.clear();
		Myintegr.integral_plot.picsel.clear();

		Myintegr.vec.myvec_xy.clear();
		Myintegr.vec.picsel.clear();

		delete Pen_for_INTEGRAL;
		DeleteObject(hFont1);
	}return 0;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

