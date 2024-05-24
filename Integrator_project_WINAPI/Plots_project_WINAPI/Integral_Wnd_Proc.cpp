#include "Integral_Wnd_Proc.h"
#include "Main_files/type.h"
#include "Main_files/main_header.h"
#include "Custom_for_nice_veiw.h"
#include "Plotting.h"

Wnd_Plot_struct* Wnd_Integral;
Integral_struct Myintegr;

#ifdef GLOBAL_PRINT
void PrintGlobal_integral_wnd_cpp()
{
	printf("integral_wnd\n\n");
	printf("Wnd_Integral = %llu\n", sizeof(Wnd_Integral));
	printf("Myintegr = %llu\n", sizeof(Myintegr));
	printf("Wnd_Plot_struct* = %llu\n", sizeof(Wnd_Plot_struct*));
	printf("Integral_struct = %llu\n", sizeof(Integral_struct));
}
#endif //GLOBAL_PRINT

void WND_Integral_Init(HWND hWnd_Integer_Wnd, LPSTR text_, double A, double B, double H)
{
	Wnd_Integral->hWnd = hWnd_Integer_Wnd;
	Wnd_Integral->text_ = text_;
	Myintegr.A = A;
	Myintegr.B = B;
	Myintegr.H = H;
	//////////////////////////////////////////////
	StructIntegralInit(Wnd_Integral,Myintegr);
	if (FirstPlotting(Wnd_Integral, Myintegr.vec) != 0)
	{
		SendMessage(Wnd_Integral->hWnd, WM_CLOSE, NULL, NULL);
	}
#ifdef VECTOR_OF_INTEGER_PRINT
	{
		int i = 0;
		printf("Инициация построения графика\n");
		for (Pointer it : Myintegr.vec.myvec_xy)
		{
			printf("%5d)x = %10.6lf y = %10.6lf\n", i, it.x, it.y);
			i++;
		}
	}
#endif //VECTOR_OF_INTEGER_PRINT
	//////////////////////////////////////////////

	double correct_x = 0, correct_y = 0;
	double size_of_plot = FillIntegralVector(Myintegr, Wnd_Integral, correct_x, correct_y);

#ifdef VECTOR_OF_INTEGER_PRINT
	{
		int i = 0;
		printf("Инициация построения графика\n");
		for (Pointer it : Myintegr.integral_plot.myvec_xy)
		{
			printf("%5d)x = %10.6lf y = %10.6lf\n", i, it.x, it.y);
			i++;
		}
	}
#endif //VECTOR_OF_INTEGER_PRINT

	Wnd_Integral->setka.u5_setka = Setka_UNIT_CHANGE(size_of_plot / KOL_OF_SETKA_SQARES5);
	CorrectSetkaPos(Wnd_Integral, Myintegr.integral_plot,MIN_H_SETKA_INT,MAX_H_SETKA_INT,BASE_H_SETKA_INT);
	//Wnd_Integral->setka.mantissa = floor((correct_x > correct_y) ? correct_x : correct_y);

	Wnd_Integral->setka.sx_center = Wnd_Integral->sx / 2 - correct_x * Wnd_Integral->setka.kxy_zoom;
	Wnd_Integral->setka.sy_center = Wnd_Integral->sy / 2 - correct_y * Wnd_Integral->setka.kxy_zoom;
}
LRESULT CALLBACK Integral_Wnd_Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	///////////////////////////////////////////////////
	PAINTSTRUCT ps2;
	HDC memdc;
	HBITMAP membit;
	HDC hdc2{};
	static SMouseMove MyMouse;
	static Gdiplus::Pen* Pen_for_INTEGRAL;
	static HFONT hFont1;
	TRACKMOUSEEVENT tme;
	///////////////////////////////////////////////////
	switch (message)
	{
	case WM_CREATE:
	{
		Pen_for_INTEGRAL = GetPen_for_Integral();

		Wnd_Integral = (Wnd_Plot_struct*)malloc(sizeof(Wnd_Plot_struct));

		MousePos(FALSE, 0, 0, MyMouse);

		hFont1 = CreateFont(11, 0, 0, 0, 600, 0, 0, 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Lusida Console");
	}return 0;
	case WM_LBUTTONDOWN:
	{
		MousePos(TRUE, LOWORD(lParam), HIWORD(lParam), MyMouse);
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = hWnd;
		tme.dwFlags = TME_LEAVE;

		TrackMouseEvent(&tme);
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
		else
		{
			MyMouse.Prev_mouse_point.x = LOWORD(lParam);
			MyMouse.Prev_mouse_point.y = HIWORD(lParam);
		}
	}return 0;
	case WM_MOUSELEAVE:
	{
		MyMouse.Flag_for_mouse = FALSE;
	}return 0;
	case WM_LBUTTONUP:
	{
		MyMouse.Flag_for_mouse = FALSE;
	}return 0;
	case WM_MOUSEWHEEL:
	{
		double u_pic = Wnd_Integral->setka.unit_to_pixel;
		Wnd_Integral->setka.h_setka += (GET_WHEEL_DELTA_WPARAM(wParam) / ZOOM_SMOOTH_COUNT);
		CorrectSetkaPos(Wnd_Integral, Myintegr.integral_plot, MIN_H_SETKA_INT, MAX_H_SETKA_INT, BASE_H_SETKA_INT, false);

		//это волшебное ощущение - когда выводимая формула наконец-то оказывается логичной и срабатывает
		int ax = (MyMouse.Prev_mouse_point.x - Wnd_Integral->setka.sx_center) * (1 - u_pic / Wnd_Integral->setka.unit_to_pixel);
		int ay = (MyMouse.Prev_mouse_point.y - Wnd_Integral->setka.sy_center) * (1 - u_pic / Wnd_Integral->setka.unit_to_pixel);
		Plotting_edges_upd(3, Wnd_Integral, ax, ay);
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
		free(Wnd_Integral);
		delete Pen_for_INTEGRAL;
		DeleteObject(hFont1);
	}return 0;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

