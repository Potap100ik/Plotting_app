#pragma once
//константы
#define MAX_LOADSTRING 100
const int WM_DRAW_MAIN_PLOT = WM_USER;
const int WM_HOME_BTN_CLICKED = WM_USER + 1;
const int WM_CLEAR_PLOT = WM_USER + 2;
const int WM_RESIZE_PLOT = WM_USER + 3;


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
enum DRAWING_REBUILD {
	ALLOW,
	CANCEL
};
struct Pointer_int {
	int x, y;
};
struct Pointer {
	double x, y;
};

typedef struct Ploting_struct {
	std::vector<Pointer_int> picsel;//вектор хранит пиксельные координаты x,y 
	std::vector<Pointer> myvec_xy;//вектор хранит реальные координаты x,y для каждой точки графика
	DRAWING_REBUILD Redraw;
};
typedef struct Integral_struct {
	Ploting_struct vec;
	Ploting_struct integral_plot;
	double A, B, H;//получаемые из окна границы графика
};
typedef struct Setka {
	int sx_center, sy_center;//мировые координаты центра СК
	double u_x_Left, u_x_Right, u_y_Top, u_y_Bottom;//МЕСТНЫЕ координаты края экрана графика [УСЛ ЕД] u_HHH;
	int p_x_Left, p_y_Bottom, p_x_Right, p_y_Top, p_x_LLeft5, p_y_BBottom5;//МЕСТНЫЕ координаты границы экрана графика [ПИКСЕЛ]

	int h_setka, h5_setka;//расстояние между квадратами сетки [пиксели]
	double u5_setka;//ширина большого квадрата [УСЛ ЕД]
	int mantissa;//мантисса для чисел сетки графика
	double kxy_zoom;//количество пикселей на условную единицу [ПИКСЕЛ/1 УСЛ ЕД]
	double unit_to_pixel;//количество условных единиц на 1 пиксел [УСЛ ЕД/1 ПИКСЕЛ]
	int Wide_for_Vec_capasity;
	double Left_Wide_Vec_UNIT, Right_Wide_Vec_UNIT;//расстояние в количествах элементов вектора до границы вектора (для предотвращения запаздывания пересчета вектора при скроллинге и зуме)
	
}MySetka;
typedef struct Wnd_Plot_struct {
	HWND hWnd;//дескриптор окна для графика
	MySetka setka;//информация о сетке окна дла графика
	int sx, sy;//размеры текущего окна для графика
	LPSTR text_;//функция после ввода вводе
}MyWnd_Plot;
typedef struct SMouseMove {
	POINT Prev_mouse_point;//отслеживание движения  мыши 
	BOOL Flag_for_mouse;//после нажатия правой кнопки происходит захват координат и график шевелится
}MouseMove;


