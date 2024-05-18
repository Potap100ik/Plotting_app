#pragma once
//константы
#define MAX_LOADSTRING 100
//Типы данных
enum CTL_ID {
	HWNDBUTTON_ENTER,
	HWNDBUTTON_HOME,
	HWNDBUTTON_CLEARPLOT,
	HWNDBUTTON_INTEGER,
	HWNDEDIT_INTEGER,
	HWNDEDIT_ERROR,
	HWNDEDIT_BASE,
	HWNDEDIT_A,
	HWNDEDIT_B,
	HWNDEDIT_H
};
enum DRAWING_WAY {
	SIMPLE_PLOTTING,
	DRAW_INTEGRAL
};
struct Pointer {
	double x, y;
};
struct Pointer_lng_double {
	long double x, y;
};
typedef struct Ploting_struct {
	std::vector<Pointer> picsel;//вектор хранит пиксельные координаты x,y 
	std::vector<Pointer> myvec_xy;//вектор хранит реальные координаты x,y для каждой точки графика

};
typedef struct Integral_struct {
	Ploting_struct vec;
	Ploting_struct integral_plot;
	double A, B, H;//получаемые из окна границы графика
};
typedef struct Setka {
	int sx_center, sy_center;//мировые координаты центра СК
	double LLeft, RRight, TTop, BBottom;//МЕСТНЫЕ координаты края экрана графика [УСЛ ЕД] u_HHH;
	int x_LL, y_BB, x_RR, y_TT, x_LL5, y_BB5;//МЕСТНЫЕ координаты границы экрана графика [ПИКСЕЛ]

	int h_setka, h5_setka;//расстояние между квадратами сетки [пиксели]
	double u5_setka;//ширина большого квадрата [УСЛ ЕД]
	int mantissa;//мантисса для чисел сетки графика
	double kxy_zoom;//количество пикселей на условную единицу [ПИКСЕЛ/1 УСЛ ЕД]
	double unit_to_pixel;//количество условных единиц на 1 пиксел [УСЛ ЕД/1 ПИКСЕЛ]
	int Wide_Vec, Left_Wide_Vec, Right_Wide_Vec;//расстояние в количествах элементов вектора до границы вектора (для предотвращения запаздывания пересчета вектора при скроллинге и зуме)
	
}MySetka;
typedef struct Wnd_Plot_struct {
	HWND hWnd;
	MySetka setka;
	int sx, sy;//размеры текущего окна
	DRAWING_WAY Draw_way;
	LPSTR text_;
}MyWnd_Plot;
typedef struct SMouseMove {
	POINT Prev_mouse_point{};
	BOOL Flag_for_mouse;
}MouseMove;


