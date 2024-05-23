#include "main_header.h"

#include "../Custom_for_nice_veiw.h"
#include "../Str_to_double/str_to_double.h"
#include "../Integrate/Simps_meth.h"
#include "../Error.h"

extern HWND//ну не хочу пока я разбираться как это перемещать между срр файлами по-другому
hWndEdit_Erroors;

#ifdef CONSOLE
void PrintGlobal_mainfunc_cpp()
{
	printf("main_function\n");
	printf("hWndEdit_erroors = %llu\n", sizeof(hWndEdit_Erroors));
}
#endif //CONSOLE

//исполнительные функции
double Setka_UNIT_CHANGE(double get_value)
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



void MousePos(BOOL fl, int x, int y, SMouseMove& MyMouse)
{
	MyMouse.Flag_for_mouse = fl;
	MyMouse.Prev_mouse_point.x = x;
	MyMouse.Prev_mouse_point.y = y;
}
void CorrectSetkaPos(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot, int h_min, int h_max, int h_baza)
{
	static char count_resizing = 0;//ПОДСЧЕТ КОЛИЧЕСТВА ИЗМЕНЕНИЙ ДЛЯ ПЕРЕСЧЕТА ФУНКЦИИ ЧТОБЫ НЕ ТЕРЯТЬ ЕЕ ПЛАВНОСТЬ
	if (Wnd_Plot->setka.h_setka <= h_min)
		Wnd_Plot->setka.h_setka = h_min;
	else if (Wnd_Plot->setka.h_setka >= h_max)
	{
		count_resizing++;
		Wnd_Plot->setka.h_setka = h_baza;
		Wnd_Plot->setka.u5_setka = Setka_UNIT_CHANGE(Wnd_Plot->setka.u5_setka / 2.1);
	}
	else if (Wnd_Plot->setka.h_setka < h_baza)
	{
		count_resizing++;
		Wnd_Plot->setka.h_setka = h_max - 1;
		Wnd_Plot->setka.u5_setka = Setka_UNIT_CHANGE(Wnd_Plot->setka.u5_setka * 2.1);
	}

	SetkaStructUpdate(Wnd_Plot, Wnd_Plot->setka.h_setka, Wnd_Plot->setka.u5_setka);
	for (int i = 0; i < Myplot.picsel.size(); i++)
	{
		Myplot.picsel[i].x = Myplot.myvec_xy[i].x * Wnd_Plot->setka.kxy_zoom;
		Myplot.picsel[i].y = Myplot.myvec_xy[i].y * Wnd_Plot->setka.kxy_zoom;
	}
	Plotting_edges_upd(2, Wnd_Plot);
	if (Myplot.Redraw == ALLOW)
	{
		if (Wnd_Plot->setka.u_x_Left < Wnd_Plot->setka.Left_Wide_Vec_UNIT || Wnd_Plot->setka.u_x_Right > Wnd_Plot->setka.Right_Wide_Vec_UNIT || count_resizing > 3)
		{
			Wide_for_vector_upd(Wnd_Plot, Myplot);
			count_resizing = 0;
		}
	}
	return;
}
void Plotting_edges_upd(int draw_h5_inside_or_not, Wnd_Plot_struct* Wnd_Plot)
{
	switch (draw_h5_inside_or_not)
	{
	case 0:
		//КООРДИНАТЫ СЕТОЧНЫХ КРАЕВ В ПИКСЕЛЯХ
		Wnd_Plot->setka.p_x_Left = -(Wnd_Plot->setka.sx_center / Wnd_Plot->setka.h_setka + 1) * Wnd_Plot->setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot->setka.p_y_Bottom = -((Wnd_Plot->sy - Wnd_Plot->setka.sy_center + 1) / Wnd_Plot->setka.h_setka) * Wnd_Plot->setka.h_setka;//**приведение типов -  координаты
		Wnd_Plot->setka.p_x_Right = Wnd_Plot->sx - Wnd_Plot->setka.sx_center;//граница правая
		Wnd_Plot->setka.p_y_Top = Wnd_Plot->setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев большой сетки
		Wnd_Plot->setka.p_x_LLeft5 = ((Wnd_Plot->setka.p_x_Left / Wnd_Plot->setka.h5_setka) - 1) * Wnd_Plot->setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot->setka.p_y_BBottom5 = ((Wnd_Plot->setka.p_y_Bottom / Wnd_Plot->setka.h5_setka) - 1) * Wnd_Plot->setka.h5_setka;

		break;
	case 1:
		//КООРДИНАТЫ КРАЕВ В ПИКСЕЛЯХ ДЛЯ РИСОВАНИЯ ЧИСЕЛ
		Wnd_Plot->setka.p_x_Left = -(Wnd_Plot->setka.sx_center);//**приведение типов -  координаты
		Wnd_Plot->setka.p_y_Bottom = -(Wnd_Plot->sy - Wnd_Plot->setka.sy_center);//**приведение типов -  координаты
		Wnd_Plot->setka.p_x_Right = Wnd_Plot->sx - Wnd_Plot->setka.sx_center;//граница правая
		Wnd_Plot->setka.p_y_Top = Wnd_Plot->setka.sy_center;//граница нихняя
		//расстояние от центра СК до отрицательных краев
		Wnd_Plot->setka.p_x_LLeft5 = ((Wnd_Plot->setka.p_x_Left / Wnd_Plot->setka.h5_setka) + 1) * Wnd_Plot->setka.h5_setka;//переходим в рисование больших квадратов и чисел
		Wnd_Plot->setka.p_y_BBottom5 = ((Wnd_Plot->setka.p_y_Bottom / Wnd_Plot->setka.h5_setka) + 1) * Wnd_Plot->setka.h5_setka;
		break;
	case 2:
		Plotting_edges_upd(1, Wnd_Plot);
		//КООРДИНАТЫ КРАЕВ В УСЛОВНЫХ ЕДИНИЦАХ
		Wnd_Plot->setka.u_x_Left = Wnd_Plot->setka.p_x_Left * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.u_x_Right = Wnd_Plot->setka.p_x_Right * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.u_y_Top = Wnd_Plot->setka.p_y_Top * Wnd_Plot->setka.unit_to_pixel;
		Wnd_Plot->setka.u_y_Bottom = Wnd_Plot->setka.p_y_Bottom * Wnd_Plot->setka.unit_to_pixel;
		break;
	}
	return;
}
void Wide_for_vector_upd(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{
	Wnd_Plot->setka.Left_Wide_Vec_UNIT = Wnd_Plot->setka.u_x_Left - SYSTEMMETRICS * Wnd_Plot->setka.unit_to_draw;
	Wnd_Plot->setka.Right_Wide_Vec_UNIT = Wnd_Plot->setka.u_x_Left + SYSTEMMETRICS * Wnd_Plot->setka.unit_to_draw;
	RedrawPlot(Wnd_Plot, Myplot);
}


int FirstPlotting(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{//ПЕРВОЕ ЗАПОЛНЕНИЕ ДАННЫХ О ФУНКЦИИ
	//ОЧИЩАЮТСЯ ВЕКТОРА С СОХРАНЕНИЕМ НУЖНОЙ КАПАСИТИ
	Myplot.picsel.clear();
	Myplot.myvec_xy.clear();
	Pointer point;
	double y;
	int i = 0;
	for (double x = Wnd_Plot->setka.Left_Wide_Vec_UNIT;
		x < Wnd_Plot->setka.Right_Wide_Vec_UNIT;
		x += Wnd_Plot->setka.unit_to_draw) {
		point.x = x;
		try {
			y = Function_String_to_Double(Wnd_Plot->text_, &x, 1, false);
			point.y = y;
#ifdef VECTOR_OF_MAIN_PLOT_PRINT
			if (x >= 5.4)
				printf("x = %lf, y = %lf\n", x, y);
#endif //VECTOR_OF_MAIN_PLOT_PRINT
		}
		catch (double err)
		{
			point.y = err;
		}
		catch (ERROR_STRUCT err_msg)
		{
			CheckFunctionErrorMsg(err_msg, hWndEdit_Erroors, Wnd_Plot->hWnd);
			Myplot.picsel.clear();
			Myplot.myvec_xy.clear();
			return 1;
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
	return 0;
}
void RedrawPlot(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{
	Myplot.picsel.clear();
	Myplot.myvec_xy.clear();
	if (strlen(Wnd_Plot->text_) == 0) return;

	Pointer point;
	double y;
	int i = 0;

	for (double x = Wnd_Plot->setka.Left_Wide_Vec_UNIT;
		x < Wnd_Plot->setka.Right_Wide_Vec_UNIT;
		x += Wnd_Plot->setka.unit_to_draw) {
		point.x = x;
		try {
			y = Function_String_to_Double(Wnd_Plot->text_, &x, 1, false);
			point.y = y;
		}
		catch (double err)
		{
			point.y = NAN;
		}
		catch (ERROR_STRUCT err_msg)
		{
			CheckFunctionErrorMsg(err_msg, hWndEdit_Erroors, Wnd_Plot->hWnd);
			Myplot.picsel.clear();
			Myplot.myvec_xy.clear();
			return;
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

int CheckValues_of_edit(double A, double B, double H, HWND hWnd, HWND hWndEdit_Integral, LPSTR text_)
{
	double IntegerSum;

	if (A >= B && H <= 0)
	{
		MessageBox(hWnd, L"В числах беспорядки!!!\nИсправьте пожалуйста\nВСЁ...	", L"Внимание, котики", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
		SetWindowText(hWndEdit_Erroors, L"Исправьте значения A, B, H");
		return 1;
	}

	if (H < 0)
	{
		MessageBox(hWnd, L"В числах беспорядки!!!\nШаг - отрицательный", L"Внимание, котики", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
		SetWindowText(hWndEdit_Erroors, L"Исправьте поле \"Шаг\"");
		return 1;
	}
	if (H == 0)
	{
		MessageBox(hWnd, L"В числах беспорядки!!!\nШаг равен нулю", L"Внимание, котики", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
		SetWindowText(hWndEdit_Erroors, L"Исправьте поле \"Шаг\"");
		return 1;
	}

	if (A > B)
	{
		MessageBox(hWnd, L"В числах беспорядки!!!\nГраницы А и B перепутаны: A>B", L"Внимание, котики", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
		SetWindowText(hWndEdit_Erroors, L"Исправьте значения A или B");
		return 1;
	}


	if (H > (B - A))
	{
		MessageBox(hWnd, L"В числах беспорядки!!!\nШаг слишком велик: H > (B-A)", L"Внимание, котики", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
		SetWindowText(hWndEdit_Erroors, L"Исправьте значения A или B, или H");
		return 1;
	}

	if (strlen(text_) == 0)
	{
		MessageBox(hWnd, L"Уважаемый прогер\nГде ваша функция?", L"Внимание, котики", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
		SetWindowText(hWndEdit_Erroors, L"Введите функцию");
		return 1;
	}
	//Последний приоритет ошибочного проишествия
	if (A == B)
	{
		SetWindowText(hWndEdit_Integral, L"Интеграл равен нулю");
		SetWindowText(hWndEdit_Erroors, L"Границы равны: A = B");
		return 1;
	}
	try {
		IntegerSum = Integrator(A, B, H, text_, Function_String_to_Double, Simps_method);
	}
	catch (double error_nan)
	{
		if (isinf(error_nan) || isnan(error_nan))
			SetWindowText(hWndEdit_Erroors, L"Найдена критическая точка");
		else
			SetWindowText(hWndEdit_Erroors, L"Паранормальные явления в районе try-catch");
		return 1;
	}
	catch (ERROR_STRUCT err_msg)
	{
		CheckFunctionErrorMsg(err_msg, hWndEdit_Erroors, hWnd);
		SetWindowText(hWndEdit_Integral, L"Интеграл пока не равен");
		return 1;
	}
	SetWindowText(hWndEdit_Integral, std::to_wstring(IntegerSum).c_str());
	return 0;
}

double FillIntegralVector(Integral_struct& Myintegr, Wnd_Plot_struct* Wnd_Plot, double& correct_x, double& correct_y)
{
	Myintegr.integral_plot.picsel.clear();
	Myintegr.integral_plot.myvec_xy.clear();
	Pointer point;
	double ux_max = 0, ux_min = 0;
	double uy_max = 0, uy_min = 0;
	int i = 0;
	int j = Myintegr.vec.myvec_xy.size();
	double x = Myintegr.vec.myvec_xy[0].x - Wnd_Plot->setka.unit_to_draw;
	double y = 0;

	for (; i < j; i++, x += Wnd_Plot->setka.unit_to_draw) {

		point.x = x;
		point.y = y;

		if (ux_min > x) ux_min = x;
		if (ux_max < x) ux_max = x;

		if (uy_min > y) uy_min = y;
		if (uy_max < y) uy_max = y;

		Myintegr.integral_plot.myvec_xy.push_back(point);
		y += Myintegr.vec.myvec_xy[i].y * Wnd_Plot->setka.unit_to_draw;
	}
	//int x_in_center = ux_max - (ux_max - ux_min) / 2;
	//int y_in_center = uy_max - (uy_max - uy_min) / 2;
	for (int i = 0; i < Myintegr.integral_plot.myvec_xy.size(); i++)
	{
		Myintegr.integral_plot.picsel.push_back({});
		//Myintegr.integral_plot.myvec_xy[i].y -= y_in_center;
		//Myintegr.integral_plot.myvec_xy[i].x -= x_in_center;

		Myintegr.integral_plot.picsel[i].x = Myintegr.integral_plot.myvec_xy[i].x * Wnd_Plot->setka.kxy_zoom;
		Myintegr.integral_plot.picsel[i].y = Myintegr.integral_plot.myvec_xy[i].y * Wnd_Plot->setka.kxy_zoom;
	}
	//????????????????????????????????????????????
	correct_x = ux_max - (ux_max - ux_min) / 2;
	correct_y = uy_max - (uy_max - uy_min) / 2;
	//????????????????????????????????????????????
	//printf("sx-sy [%d, %d]\n", Wnd_Plot->setka.sx_center, Wnd_Plot->setka.sy_center);
	return (ux_max - ux_min > uy_max - uy_min) ? ux_max - ux_min : uy_max - uy_min;
}


void SetkaStructUpdate(Wnd_Plot_struct* Wnd_Plot, int new_h_setka, double new_u5_setka)
{
	Wnd_Plot->setka.h_setka = new_h_setka;
	Wnd_Plot->setka.u5_setka = new_u5_setka;

	Wnd_Plot->setka.h5_setka = Wnd_Plot->setka.h_setka * 5;
	Wnd_Plot->setka.kxy_zoom = Wnd_Plot->setka.h5_setka / Wnd_Plot->setka.u5_setka;
	Wnd_Plot->setka.unit_to_pixel = 1.0 / Wnd_Plot->setka.kxy_zoom;
	Wnd_Plot->setka.unit_to_draw = Wnd_Plot->setka.unit_to_pixel / POINTS_TO_ONE_PICEL;
	Wnd_Plot->setka.mantissa = floor(log10(Wnd_Plot->setka.u5_setka));
}
void StructPlotInit(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot)
{
	//ЗАПОЛНЕНИЕ ВСЕХ ПЕРЕМЕННЫХ СТРУКТУРЫ В ОДНОЙ ФУНКЦИИ
	Wnd_Plot->text_ = (LPSTR)"";
	Wnd_Plot->setka.sx_center = Wnd_Plot->sx / 2;//будут равны нулю
	Wnd_Plot->setka.sy_center = Wnd_Plot->sy / 2;

	SetkaStructUpdate(Wnd_Plot, BASE_H_SETKA, BASE_U5_SETKA);
	Plotting_edges_upd(2, Wnd_Plot);

	/////////////////////ПРОРАБОТАТЬ БЫ ЕЩЕ ЭТОТ МОМЕНТИК
	Wnd_Plot->setka.Wide_for_Vec_capasity = 3 * SYSTEMMETRICS + 1;//БЕРЕМ ПРО ЗАПАС 3 РАЗМЕРА ЭКРАНА В ПИКСЕЛЯХ
	Wnd_Plot->setka.Left_Wide_Vec_UNIT = -SYSTEMMETRICS * Wnd_Plot->setka.unit_to_draw;
	Wnd_Plot->setka.Right_Wide_Vec_UNIT = Wnd_Plot->setka.Left_Wide_Vec_UNIT +
		Wnd_Plot->setka.Wide_for_Vec_capasity * Wnd_Plot->setka.unit_to_draw;

	Myplot.picsel.reserve(Wnd_Plot->setka.Wide_for_Vec_capasity);
	Myplot.myvec_xy.reserve(Wnd_Plot->setka.Wide_for_Vec_capasity);

	Myplot.Redraw = ALLOW;
}
void StructIntegralInit(Wnd_Plot_struct* Wnd_Integral, Integral_struct& Myintegr)
{

	Wnd_Integral->setka.sx_center = Wnd_Integral->sx / 2;
	Wnd_Integral->setka.sy_center = Wnd_Integral->sy / 2;
	/////////////////////

	SetkaStructUpdate(Wnd_Integral, BASE_H_SETKA_INT, Setka_UNIT_CHANGE((Myintegr.B - Myintegr.A) / KOL_OF_SETKA_SQARES5));
	Plotting_edges_upd(2, Wnd_Integral);

	Wnd_Integral->setka.Wide_for_Vec_capasity = (Myintegr.B - Myintegr.A) / Wnd_Integral->setka.unit_to_draw + 1;
	Wnd_Integral->setka.Left_Wide_Vec_UNIT = Myintegr.A;
	Wnd_Integral->setka.Right_Wide_Vec_UNIT = Myintegr.B;

	Myintegr.vec.myvec_xy.reserve(Wnd_Integral->setka.Wide_for_Vec_capasity);
	Myintegr.vec.picsel.reserve(Wnd_Integral->setka.Wide_for_Vec_capasity);
	Myintegr.vec.Redraw = CANCEL;

	Myintegr.integral_plot.myvec_xy.reserve(Wnd_Integral->setka.Wide_for_Vec_capasity);
	Myintegr.integral_plot.picsel.reserve(Wnd_Integral->setka.Wide_for_Vec_capasity);
	Myintegr.integral_plot.Redraw = CANCEL;

}
