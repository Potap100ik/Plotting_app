#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"

extern Integral_struct Myintegr;
MyWnd_Plot* Wnd_Integral{};
//LRESULT CALLBACK Integral_Wnd_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_DESTROY:
//		DestroyWindow(hWnd_Integer_Wnd);
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	default: return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}
void HWND_Integral_Init(HWND hWnd_Integer_Wnd)
{
	Wnd_Integral->hWnd = hWnd_Integer_Wnd;
	//////////////////////////////////////////////
	StructInit(Wnd_Integral, Myintegr);
	Plotting_edges_upd(2, Wnd_Integral);
	FirstPlotting(Wnd_Integral, Myintegr.vec);


	//////////////////////////////////////////////
	double correct_x = 0;
	double size_of_plot = FillIntegralVector(Myintegr, Wnd_Integral, correct_x);


	Wnd_Integral->setka.u5_setka = Setka_unit(size_of_plot / 4);

	CorrectSetkaPos(0, Wnd_Integral, Myintegr.vec);
	CorrectSetkaPos(0, Wnd_Integral, Myintegr.integral_plot);
	Wnd_Integral->setka.sx_center = Wnd_Integral->sx / 2 - correct_x * Wnd_Integral->setka.kxy_zoom;
	Wnd_Integral->setka.sy_center = Wnd_Integral->sy / 2;

}
LRESULT CALLBACK Integral_Wnd_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT  ps2;
	HDC memdc;
	HBITMAP membit;
	HDC hdc2{};
	static MouseMove MyMouse;
	static bool initialization_status;
	//static Integral_struct Myintegral;
	static Pen* Pen_for_INTEGRAL;
	switch (message)
	{
	case WM_CREATE:
	{
		Pen_for_INTEGRAL = GetPen_for_Integral();
		initialization_status = true;
		Wnd_Integral = (MyWnd_Plot*)malloc(sizeof(Wnd_Plot_struct));		
		InvalidateRect(Wnd_Integral->hWnd, NULL, TRUE);
	}
		return 0;
	case WM_LBUTTONDOWN:
		MousePos(TRUE, LOWORD(lParam), HIWORD(lParam), Wnd_Integral, MyMouse);
		return 0;
	case WM_MOUSEMOVE:
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
		return 0;
	case WM_LBUTTONUP:
		MyMouse.Flag_for_mouse = FALSE;
		return 0;
	case WM_MOUSEWHEEL:
	{
		int a = Wnd_Integral->setka.h_setka;
		Wnd_Integral->setka.h_setka += GET_WHEEL_DELTA_WPARAM(wParam) / 120;
		CorrectSetkaPos(0, Wnd_Integral, Myintegr.integral_plot, 2, 16, 8);
		InvalidateRect(Wnd_Integral->hWnd, NULL, TRUE);
	}
	return 0;
	case WM_SIZE:
		Wnd_Integral->sx = LOWORD(lParam);
		Wnd_Integral->sy = HIWORD(lParam);
		//if (initialization_status) {
		//	Wnd_Integral->sx = LOWORD(lParam);
		//	Wnd_Integral->sy = HIWORD(lParam);
		//	//////////////////////////////////////////////
		//	StructInit(Wnd_Integral, Myintegr);
		//	Plotting_edges_upd(2, Wnd_Integral);
		//	FirstPlotting(Wnd_Integral, Myintegr.vec);


		//	//////////////////////////////////////////////
		//	double correct_x = 0;
		//	double size_of_plot = FillIntegralVector(Myintegr, Wnd_Integral, correct_x);


		//	Wnd_Integral->setka.u5_setka = Setka_unit(size_of_plot / 4);

		//	CorrectSetkaPos(0, Wnd_Integral, Myintegr.vec);
		//	CorrectSetkaPos(0, Wnd_Integral, Myintegr.integral_plot);
		//	Wnd_Integral->setka.sx_center = Wnd_Integral->sx / 2 - correct_x * Wnd_Integral->setka.kxy_zoom;
		//	Wnd_Integral->setka.sy_center = Wnd_Integral->sy / 2;
		//	initialization_status = false;
			//Plotting_edges_upd(2, Wnd_Plot);	
			//InvalidateRect(Wnd_Integral->hWnd, NULL, TRUE);
		//}
		return 0;
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
	{
		//SimpleTimer timer;

		hdc2 = BeginPaint(Wnd_Integral->hWnd, &ps2);
		memdc = CreateCompatibleDC(hdc2);
		membit = CreateCompatibleBitmap(hdc2, Wnd_Integral->sx, Wnd_Integral->sy);
		SelectObject(memdc, membit);
		DrowSetka(memdc, Wnd_Integral);
		DrowCounts(memdc, Wnd_Integral);

		DrowGraphSmooth(memdc, Wnd_Integral, Myintegr.integral_plot, Pen_for_INTEGRAL);

		BitBlt(hdc2, 0, 0, Wnd_Integral->sx * 2, Wnd_Integral->sy * 2, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(membit);
		EndPaint(Wnd_Integral->hWnd, &ps2);
	}
	return 0;
	case WM_DESTROY:
		delete Pen_for_INTEGRAL;
		return DefWindowProc(hWnd, message, wParam, lParam);
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

