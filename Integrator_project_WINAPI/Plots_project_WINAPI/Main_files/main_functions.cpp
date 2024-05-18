#include "../Main_files/STD/stdafx.h"
#include "../Main_files/STD/Standard.h"
using namespace Gdiplus;



//глобальные переменные
//const int Wide_of_Screen = GetSystemMetrics(SM_CXSCREEN);
//int countpaint = 0;
//std::wstring str;
//MouseMove MyMouse{};
//HDC hdc{};
extern HWND//ну не хочу пока я разбираться как это перемещать между срр файлами по-другому
hWndButton_enter,
hWndButton_clearPlot,
hWndButton_Integral,
hWndButton_home,
hWndEdit_base,
hWndEdit_A,
hWndEdit_B,
hWndEdit_H,
hWndEdit_Integral,
hWndEdit_Erroors,
hWnd_Integer_Wnd;

LPSTR text_this;//для передачи в другой файл
void Text_Init(LPSTR text_)
{
	text_this = text_;
}
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
void StructInit(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot, Integral_struct& Myintegr)
{
	Wnd_Plot->text_ = (LPSTR)"";
	Wnd_Plot->setka.h_setka = 10;
	Wnd_Plot->setka.h5_setka = Wnd_Plot->setka.h_setka * 5; //50
	Wnd_Plot->setka.u5_setka = 2;
	Wnd_Plot->setka.mantissa = 1;
	Wnd_Plot->setka.kxy_zoom = Wnd_Plot->setka.h5_setka / Wnd_Plot->setka.u5_setka;//25
	Wnd_Plot->setka.unit_to_pixel = 1.0 / Wnd_Plot->setka.kxy_zoom;
	Plotting_edges_upd(1, Wnd_Plot);
	Wnd_Plot->setka.LLeft = Wnd_Plot->setka.x_LL * Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.RRight = Wnd_Plot->setka.x_RR * Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.TTop = Wnd_Plot->setka.y_TT * Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.BBottom = Wnd_Plot->setka.y_BB * Wnd_Plot->setka.unit_to_pixel;



	Wnd_Plot->setka.Wide_Vec = 4000 + GetSystemMetrics(SM_CXSCREEN);
	Wnd_Plot->setka.Left_Wide_Vec = -(Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.Right_Wide_Vec = (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;

	//Wnd_Plot->setka.u_HHH = 2;//шаг рисовки - 2 пикселя
	Myintegr.A = -10;
	Myintegr.B = 10;
	Myintegr.H = 0.1;
	SetWindowText(hWndEdit_base, L"sin(x)");//log(x)//sin(x)*abs(x)//x*x/10
	SetWindowText(hWndEdit_A, L"0");// std::to_wstring(Myintegr.A).c_str()
	SetWindowText(hWndEdit_B, L"10");
	SetWindowText(hWndEdit_H, L"0.1");
	SetWindowText(hWndEdit_Integral, L"Ку-ку епта");

	Myplot.picsel.reserve(Wnd_Plot->setka.Wide_Vec + 1);
	Myplot.myvec_xy.reserve(Wnd_Plot->setka.Wide_Vec + 1);

	Myintegr.vec.myvec_xy.reserve(Wnd_Plot->setka.Wide_Vec + 1);
	Myintegr.vec.picsel.reserve(Wnd_Plot->setka.Wide_Vec + 1);

	Myintegr.integral_plot.myvec_xy.reserve(Wnd_Plot->setka.Wide_Vec + 1);
	Myintegr.integral_plot.picsel.reserve(Wnd_Plot->setka.Wide_Vec + 1);
}
void MousePos(BOOL fl, int x, int y, MyWnd_Plot* Wnd_Plot, MouseMove& MyMouse)
{
	MyMouse.Flag_for_mouse = fl;
	MyMouse.Prev_mouse_point.x = x;
	MyMouse.Prev_mouse_point.y = y;
}
void CorrectSetkaPos(int a, MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot, int h_min, int h_max, int h_baza)
{
	static char count_resizing = 0;

	if (Wnd_Plot->setka.h_setka <= h_min)
		Wnd_Plot->setka.h_setka = h_min;
	else if (Wnd_Plot->setka.h_setka >= h_max)
	{
		count_resizing++;
		Wnd_Plot->setka.h_setka = h_baza;
		Wnd_Plot->setka.u5_setka = Setka_unit(Wnd_Plot->setka.u5_setka / 2.1);
	}
	else if (Wnd_Plot->setka.h_setka < h_baza)
	{
		count_resizing++;
		Wnd_Plot->setka.h_setka = h_max-1;
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

	Plotting_edges_upd(2, Wnd_Plot);

	if (Wnd_Plot->Draw_way == DRAW_INTEGRAL) return;
	if (Wnd_Plot->setka.LLeft < Wnd_Plot->setka.Left_Wide_Vec || Wnd_Plot->setka.RRight > Wnd_Plot->setka.Right_Wide_Vec || count_resizing > 3)
	{
		Wnd_Plot->setka.Left_Wide_Vec = Wnd_Plot->setka.LLeft - (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.Right_Wide_Vec = Wnd_Plot->setka.LLeft + (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
		count_resizing = 0;
		RedrawPlot(Wnd_Plot, Myplot);
	}
	return;
}
void Plotting_edges_upd(int draw_h5_inside_or_not, MyWnd_Plot* Wnd_Plot)
{
	switch (draw_h5_inside_or_not)
	{
	case 0:
		//КООРДИНАТЫ СЕТОЧНЫХ КРАЕВ
		Wnd_Plot->setka.x_LL = -(Wnd_Plot->setka.sx_center / Wnd_Plot->setka.h_setka + 1) * Wnd_Plot->setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot->setka.y_BB = -((Wnd_Plot->sy - Wnd_Plot->setka.sy_center + 1) / Wnd_Plot->setka.h_setka) * Wnd_Plot->setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot->setka.x_RR = Wnd_Plot->sx - Wnd_Plot->setka.sx_center;//граница правая
		Wnd_Plot->setka.y_TT = Wnd_Plot->setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев большой сетки
		Wnd_Plot->setka.x_LL5 = ((Wnd_Plot->setka.x_LL / Wnd_Plot->setka.h5_setka) - 1) * Wnd_Plot->setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot->setka.y_BB5 = ((Wnd_Plot->setka.y_BB / Wnd_Plot->setka.h5_setka) - 1) * Wnd_Plot->setka.h5_setka;

		break;
	case 1:
		//КООРДИНАТЫ КРАЕВ
		Wnd_Plot->setka.x_LL = -(Wnd_Plot->setka.sx_center);//**приведение типов -  координаты
		Wnd_Plot->setka.y_BB = -(Wnd_Plot->sy - Wnd_Plot->setka.sy_center);//**приведение типов -  координаты
		Wnd_Plot->setka.x_RR = Wnd_Plot->sx - Wnd_Plot->setka.sx_center;//граница правая
		Wnd_Plot->setka.y_TT = Wnd_Plot->setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев
		Wnd_Plot->setka.x_LL5 = ((Wnd_Plot->setka.x_LL / Wnd_Plot->setka.h5_setka) + 1) * Wnd_Plot->setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot->setka.y_BB5 = ((Wnd_Plot->setka.y_BB / Wnd_Plot->setka.h5_setka) + 1) * Wnd_Plot->setka.h5_setka;
		break;
	case 2:
		Plotting_edges_upd(1, Wnd_Plot);
		Wnd_Plot->setka.LLeft = Wnd_Plot->setka.x_LL * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.RRight = Wnd_Plot->setka.x_RR * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.TTop = Wnd_Plot->setka.y_TT * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.BBottom = Wnd_Plot->setka.y_BB * Wnd_Plot->setka.unit_to_pixel;

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

int CheckValues_of_edit(double A, double B, double H, HWND hWnd, HWND hWndEdit_Integral, MyWnd_Plot* Wnd_Plot)
{
	double IntegerSum;
	if (A == B) {
		SetWindowText(hWndEdit_Erroors, L"Интеграл равен нулю");
		return 1;
	}
	if (H == 0)
	{
		SetWindowText(hWndEdit_Erroors, L"Шаг равен нулю");
		return 1;
	}
	if (A > B || H == 0 || H > (B - A))
	{
		MessageBox(hWnd, L"Уважаемый прогер\nВ числах беспорядки!!!\nИз чего интегралы строить", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
		SetWindowText(hWndEdit_Erroors, L"Интеграл пока не равен");
		return 1;
	}
	if (strlen(Wnd_Plot->text_) == 0)
	{
		MessageBox(hWnd, L"Уважаемый прогер\nГде ваша функция?", L"Внимание, котики", MB_RETRYCANCEL | MB_ICONSTOP);
		SetWindowText(hWndEdit_Erroors, L"Интеграл пока не равен");
		return 1;
	}
	try {
		IntegerSum = Integrator(A, B, H, Wnd_Plot->text_, Function_String_to_Double, Simps_method);
	}
	catch (double error_nan)
	{

		if (isinf(error_nan) || isnan(error_nan))
			SetWindowText(hWndEdit_Erroors, L"Найдена критическая точка/nПересмотрите границы интервала");
		else
			SetWindowText(hWndEdit_Erroors, L"Паранормальные явления в районе try-catch");
		return 1;
	}
	SetWindowText(hWndEdit_Integral, std::to_wstring(IntegerSum).c_str());
	return 0;
}
double FillIntegralVector(Integral_struct& Myintegr, MyWnd_Plot* Wnd_Plot, double & correct_x , double& correct_y)
{
	Myintegr.integral_plot.picsel.clear();
	Myintegr.integral_plot.myvec_xy.clear();
	Pointer point;
	double ux_max = 0, ux_min = 0;
	double uy_max = 0, uy_min = 0;
	int i = 0;
	while (Myintegr.vec.myvec_xy[i].x < Myintegr.A)
	{
		++i;
	}
	int j = i;
	while (Myintegr.vec.myvec_xy[j].x < Myintegr.B)
	{
		++j;
	}

	double x = Myintegr.vec.myvec_xy[i-1].x;
	double y = 0;

	for (; i < j; i++, x += Wnd_Plot->setka.unit_to_pixel) {

		point.x = x;
		point.y = y;

		if (ux_min > x) ux_min = x;
		if (ux_max < x) ux_max = x;

		if (uy_min > y) uy_min = y;
		if (uy_max < y) uy_max = y;

		Myintegr.integral_plot.myvec_xy.push_back(point);
		y += Myintegr.vec.myvec_xy[i - 1].y * Wnd_Plot->setka.unit_to_pixel;
	}

	for (int i = 0; i < Myintegr.integral_plot.myvec_xy.size(); i++)
	{
		Myintegr.integral_plot.picsel.push_back({});
		Myintegr.integral_plot.myvec_xy[i].y -= uy_max - (uy_max - uy_min) / 2;
		Myintegr.integral_plot.myvec_xy[i].x -= ux_max - (ux_max - ux_min) / 2;

		Myintegr.integral_plot.picsel[i].x = Myintegr.integral_plot.myvec_xy[i].x * Wnd_Plot->setka.kxy_zoom;
		Myintegr.integral_plot.picsel[i].y = Myintegr.integral_plot.myvec_xy[i].y * Wnd_Plot->setka.kxy_zoom;
	}

	correct_x = ux_max - (ux_max - ux_min) / 2;
	correct_y = uy_max - (uy_max - uy_min) / 2;
	printf("sx-sy [%d, %d]\n", Wnd_Plot->setka.sx_center, Wnd_Plot->setka.sy_center);
	return (ux_max - ux_min > uy_max - uy_min) ? ux_max - ux_min : uy_max - uy_min;
}
void RedrawIntegralVector(MyWnd_Plot* Wnd_Plot, Integral_struct& Myintegr)
{
	if (strlen(Wnd_Plot->text_) == 0) return;
	Myintegr.integral_plot.picsel.clear();
	Myintegr.integral_plot.myvec_xy.clear();
	Pointer point;
	long double y;
	int i = 0;

	for (int i = 0; i < Myintegr.integral_plot.myvec_xy.size(); i++)
	{
		Myintegr.integral_plot.picsel.push_back({});
		Myintegr.integral_plot.picsel[i].x = Myintegr.integral_plot.myvec_xy[i].x * Wnd_Plot->setka.kxy_zoom;
		Myintegr.integral_plot.picsel[i].y = Myintegr.integral_plot.myvec_xy[i].y * Wnd_Plot->setka.kxy_zoom;
	}

	for (int i = 0; i < Myintegr.integral_plot.myvec_xy.size(); i++)
	{
		Myintegr.integral_plot.picsel.push_back({});
		Myintegr.integral_plot.picsel[i].x = Myintegr.integral_plot.myvec_xy[i].x * Wnd_Plot->setka.kxy_zoom;
		Myintegr.integral_plot.picsel[i].y = Myintegr.integral_plot.myvec_xy[i].y * Wnd_Plot->setka.kxy_zoom;
	}
}

void StructInit(MyWnd_Plot* Wnd_Integral, Integral_struct& Myintegr)
{
	Wnd_Integral->hWnd = hWnd_Integer_Wnd;
	////////////////////
	/*	Wnd_Plot->text_ = (LPSTR)"";
	Wnd_Plot->setka.h_setka = 10;
	Wnd_Plot->setka.h5_setka = Wnd_Plot->setka.h_setka * 5; //50
	Wnd_Plot->setka.u5_setka = 2;
	Wnd_Plot->setka.mantissa = 1;
	Wnd_Plot->setka.kxy_zoom = Wnd_Plot->setka.h5_setka / Wnd_Plot->setka.u5_setka;//25
	Wnd_Plot->setka.unit_to_pixel = 1.0 / Wnd_Plot->setka.kxy_zoom;
	Plotting_edges_upd(1, Wnd_Plot);
	Wnd_Plot->setka.LLeft = Wnd_Plot->setka.x_LL / Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.RRight = Wnd_Plot->setka.x_RR / Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.TTop = Wnd_Plot->setka.y_TT / Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.BBottom = Wnd_Plot->setka.y_BB / Wnd_Plot->setka.unit_to_pixel;



	Wnd_Plot->setka.Wide_Vec = 4000 + GetSystemMetrics(SM_CXSCREEN);
	Wnd_Plot->setka.Left_Wide_Vec = -(Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;
	Wnd_Plot->setka.Right_Wide_Vec = (Wnd_Plot->setka.Wide_Vec / 2 - 1000) * Wnd_Plot->setka.unit_to_pixel;

	//Wnd_Plot->setka.u_HHH = 2;//шаг рисовки - 2 пикселя
	Myintegr.A = -10;
	Myintegr.B = 10;
	Myintegr.H = 0.1;
	SetWindowText(hWndEdit_base, L"x*x/10");//log(x)//sin(x)*abs(x)
	SetWindowText(hWndEdit_A, L"-10");// std::to_wstring(Myintegr.A).c_str()
	SetWindowText(hWndEdit_B, L"10");
	SetWindowText(hWndEdit_H, L"0,1");
	SetWindowText(hWndEdit_Integral, L"Ку-ку епта");

	Myplot.picsel.reserve(Wnd_Plot->setka.Wide_Vec + 1);
	Myplot.myvec_xy.reserve(Wnd_Plot->setka.Wide_Vec + 1);

	Myintegr.vec.myvec_xy.reserve(Wnd_Plot->setka.Wide_Vec + 1);
	Myintegr.vec.picsel.reserve(Wnd_Plot->setka.Wide_Vec + 1);

	Myintegr.integral_plot.myvec_xy.reserve(Wnd_Plot->setka.Wide_Vec + 1);
	Myintegr.integral_plot.picsel.reserve(Wnd_Plot->setka.Wide_Vec + 1);
}*/
	Wnd_Integral->setka.sx_center = Wnd_Integral->sx / 2;
	Wnd_Integral->setka.sy_center = Wnd_Integral->sy / 2;
	/////////////////////
	Wnd_Integral->text_ = text_this;

	Wnd_Integral->setka.h_setka = 10;
	Wnd_Integral->setka.h5_setka = Wnd_Integral->setka.h_setka * 5;
	//здесь мы говорим, что наш график будет состоять из 10 больших клеток
	Wnd_Integral->setka.u5_setka = Setka_unit((Myintegr.B - Myintegr.A) / 5);//пусть наш график торетически помещается в 8 клеток по ширине

	Wnd_Integral->setka.mantissa = floor(log10(Wnd_Integral->setka.u5_setka));
	Wnd_Integral->setka.kxy_zoom = Wnd_Integral->setka.h5_setka / Wnd_Integral->setka.u5_setka;
	Wnd_Integral->setka.unit_to_pixel = 1.0 / Wnd_Integral->setka.kxy_zoom;

	Plotting_edges_upd(1, Wnd_Integral);
	Wnd_Integral->setka.LLeft = Wnd_Integral->setka.x_LL * Wnd_Integral->setka.unit_to_pixel;
	Wnd_Integral->setka.RRight = Wnd_Integral->setka.x_RR * Wnd_Integral->setka.unit_to_pixel;
	Wnd_Integral->setka.TTop = Wnd_Integral->setka.y_TT * Wnd_Integral->setka.unit_to_pixel;
	Wnd_Integral->setka.BBottom = Wnd_Integral->setka.y_BB * Wnd_Integral->setka.unit_to_pixel;
	Wnd_Integral->setka.Wide_Vec = 4000 + GetSystemMetrics(SM_CXSCREEN);
	Wnd_Integral->setka.Left_Wide_Vec = -(Wnd_Integral->setka.Wide_Vec / 2 - 1000) * Wnd_Integral->setka.unit_to_pixel;
	Wnd_Integral->setka.Right_Wide_Vec = (Wnd_Integral->setka.Wide_Vec / 2 - 1000) * Wnd_Integral->setka.unit_to_pixel;
	Wnd_Integral->Draw_way = DRAW_INTEGRAL;

}
