#include "../Main_files/STD/stdafx.h"
#include "../Main_files/STD/Standard.h"
using namespace Gdiplus;



extern HINSTANCE hInst;/////////////////////////////////////////////////////убери глобальные переменные потому что так надо
//глобальные переменные
const int Wide_of_Screen = GetSystemMetrics(SM_CXSCREEN);
double IntegerSum;
int countpaint = 0;
//std::wstring str;
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
void StructInit(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot, Integral_struct Myintegr)
{
	Wnd_Plot->text_ = (LPSTR)"";
	Wnd_Plot->setka.h_setka = 10;
	Wnd_Plot->setka.h5_setka = Wnd_Plot->setka.h_setka * 5; //50
	Wnd_Plot->setka.u5_setka = 2;
	Wnd_Plot->setka.mantissa = 1;
	Wnd_Plot->setka.kxy_zoom = Wnd_Plot->setka.h5_setka / Wnd_Plot->setka.u5_setka;//25
	Wnd_Plot->setka.unit_to_pixel = 1.0 / Wnd_Plot->setka.kxy_zoom;
	Plotting_edges_upd(1, Wnd_Plot, Myplot);
	Wnd_Plot->setka.LLeft = Wnd_Plot->x_LL / Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.RRight = Wnd_Plot->x_RR / Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.TTop = Wnd_Plot->y_TT / Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.BBottom = Wnd_Plot->y_BB / Wnd_Plot->setka.unit_to_pixel;



	Wnd_Plot->setka.Wide_Vec = 4000 + Wide_of_Screen;
	Wnd_Plot->setka.Left_Wide_Vec = -(Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.Right_Wide_Vec = (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;

	Wnd_Plot->setka.u_HHH = 2;//шаг рисовки - 2 пикселя
	Myintegr.A = -10;
	Myintegr.B = 10;
	Myintegr.H = 0.1;
	SetWindowText(hWndEdit_base, L"sin(x)*abs(x)");//log(x)
	SetWindowText(hWndEdit_A, L"-10");// std::to_wstring(Myintegr.A).c_str()
	SetWindowText(hWndEdit_B, L"10");
	SetWindowText(hWndEdit_H, L"0,1");
	SetWindowText(hWndEdit_Integral, L"Ку-ку епта");

	Myplot.picsel.reserve(Wnd_Plot->setka.Wide_Vec + 1);
	Myplot.myvec_xy.reserve(Wnd_Plot->setka.Wide_Vec + 1);


}
void MousePos(BOOL fl, int x, int y, MyWnd_Plot* Wnd_Plot)
{
	MyMouse.Flag_for_mouse = fl;
	MyMouse.Prev_mouse_point.x = x;
	MyMouse.Prev_mouse_point.y = y;
}
void CorrectSetkaPos(int a, MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot)
{
	static char count_resizing = 0;


	if (Wnd_Plot->setka.h_setka <= 3)
		Wnd_Plot->setka.h_setka = 3;
	else if (Wnd_Plot->setka.h_setka >= 20)
	{
		count_resizing++;
		Wnd_Plot->setka.h_setka = 10;
		Wnd_Plot->setka.u5_setka = Setka_unit(Wnd_Plot->setka.u5_setka / 2.1);
	}
	else if (Wnd_Plot->setka.h_setka < 10)
	{
		count_resizing++;
		Wnd_Plot->setka.h_setka = 19;
		Wnd_Plot->setka.u5_setka = Setka_unit(Wnd_Plot->setka.u5_setka * 2.1);
	}




	Wnd_Plot->setka.h5_setka = Wnd_Plot->setka.h_setka * 5;
	Wnd_Plot->setka.kxy_zoom = Wnd_Plot->setka.h5_setka / Wnd_Plot->setka.u5_setka;
	Wnd_Plot->setka.unit_to_pixel = 1.0 / Wnd_Plot->setka.kxy_zoom;
	Wnd_Plot->setka.mantissa = floor(log10(Wnd_Plot->setka.u5_setka));
	for (int i = 0; i < Myplot.picsel.size(); i++)
	{
		Myplot.picsel[i].x = Myplot.myvec_xy[i].x * Wnd_Plot->setka.kxy_zoom;
		Myplot.picsel[i].y = Myplot.myvec_xy[i].y * Wnd_Plot->setka.kxy_zoom;
	}

	Plotting_edges_upd(2, Wnd_Plot, Myplot);
	if (Wnd_Plot->setka.LLeft < Wnd_Plot->setka.Left_Wide_Vec || Wnd_Plot->setka.RRight > Wnd_Plot->setka.Right_Wide_Vec || count_resizing > 4)
	{
		Wnd_Plot->setka.Left_Wide_Vec = Wnd_Plot->setka.LLeft - (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.Right_Wide_Vec = Wnd_Plot->setka.LLeft + (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
		count_resizing = 0;
		RedrawPlot(Wnd_Plot, Myplot);
	}
	return;
}
void Plotting_edges_upd(int draw_h5_inside_or_not, MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot)
{
	switch (draw_h5_inside_or_not)
	{
	case 0:
		//КООРДИНАТЫ СЕТОЧНЫХ КРАЕВ
		Wnd_Plot->x_LL = -(Wnd_Plot->setka.sx_center / Wnd_Plot->setka.h_setka + 1) * Wnd_Plot->setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot->y_BB = -((Wnd_Plot->sy - Wnd_Plot->setka.sy_center + 1) / Wnd_Plot->setka.h_setka) * Wnd_Plot->setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot->x_RR = Wnd_Plot->sx - Wnd_Plot->setka.sx_center;//граница правая
		Wnd_Plot->y_TT = Wnd_Plot->setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев большой сетки
		Wnd_Plot->x_LL5 = ((Wnd_Plot->x_LL / Wnd_Plot->setka.h5_setka) - 1) * Wnd_Plot->setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot->y_BB5 = ((Wnd_Plot->y_BB / Wnd_Plot->setka.h5_setka) - 1) * Wnd_Plot->setka.h5_setka;

		break;
	case 1:
		//КООРДИНАТЫ КРАЕВ
		Wnd_Plot->x_LL = -(Wnd_Plot->setka.sx_center);//**приведение типов -  координаты
		Wnd_Plot->y_BB = -(Wnd_Plot->sy - Wnd_Plot->setka.sy_center);//**приведение типов -  координаты
		Wnd_Plot->x_RR = Wnd_Plot->sx - Wnd_Plot->setka.sx_center;//граница правая
		Wnd_Plot->y_TT = Wnd_Plot->setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев
		Wnd_Plot->x_LL5 = ((Wnd_Plot->x_LL / Wnd_Plot->setka.h5_setka) + 1) * Wnd_Plot->setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot->y_BB5 = ((Wnd_Plot->y_BB / Wnd_Plot->setka.h5_setka) + 1) * Wnd_Plot->setka.h5_setka;
		break;
	case 2:
		Plotting_edges_upd(1, Wnd_Plot, Myplot);
		Wnd_Plot->setka.LLeft = Wnd_Plot->x_LL * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.RRight = Wnd_Plot->x_RR * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.TTop = Wnd_Plot->y_TT * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.BBottom = Wnd_Plot->y_BB * Wnd_Plot->setka.unit_to_pixel;

		break;
	}
	return;
}
void FirstPlotting(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot)
{

	Myplot.picsel.clear();
	Myplot.myvec_xy.clear();
	Pointer point;
	long double y;
	int i = 0;
	for (double x = Wnd_Plot->setka.Left_Wide_Vec;
		x < Wnd_Plot->setka.Right_Wide_Vec;
		x += Wnd_Plot->setka.unit_to_pixel) {
		point.x = x;
		try {
			y = Function_String_to_Double(Wnd_Plot->text_, &x);
			point.y = y;
		}
		catch (double err)
		{
			point.y = err;
		}

		Myplot.myvec_xy.push_back(point);
		++i;
	}

	for (int i = 0; i < Myplot.myvec_xy.size(); i++)
	{
		Myplot.picsel.push_back({});
		Myplot.picsel[i].x = Myplot.myvec_xy[i].x * Wnd_Plot->setka.kxy_zoom;
		Myplot.picsel[i].y = Myplot.myvec_xy[i].y * Wnd_Plot->setka.kxy_zoom;
	}
}
void RedrawPlot(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot)
{
	if (strlen(Wnd_Plot->text_) == 0) return;
	Myplot.picsel.clear();
	Myplot.myvec_xy.clear();
	Pointer point;
	long double y;
	int i = 0;
	for (double x = Wnd_Plot->setka.Left_Wide_Vec;
		x < Wnd_Plot->setka.Right_Wide_Vec;
		x += Wnd_Plot->setka.unit_to_pixel) {
		point.x = x;
		try {
			y = Function_String_to_Double(Wnd_Plot->text_, &x);
			point.y = y;
		}
		catch (double err)
		{
			point.y = NAN;
		}

		Myplot.myvec_xy.push_back(point);
		++i;
	}

	for (int i = 0; i < Myplot.myvec_xy.size(); i++)
	{
		Myplot.picsel.push_back({});
		Myplot.picsel[i].x = Myplot.myvec_xy[i].x * Wnd_Plot->setka.kxy_zoom;
		Myplot.picsel[i].y = Myplot.myvec_xy[i].y * Wnd_Plot->setka.kxy_zoom;
	}
}
