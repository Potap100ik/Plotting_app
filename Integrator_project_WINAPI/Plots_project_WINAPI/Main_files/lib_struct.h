#pragma once
#include "STD/stdafx.h"
#include "const_sys.h"
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
enum ERROR_STR_TO_DOUBLE {
	CHAR_ERR,
	EXPRESSION_ERR,
	EMPTY_ERR,
	WHATS_APP_ERR,
	BRACKET_ERR,
	OTHER_ERR
};
struct ERROR_STRUCT {
	enum ERROR_STR_TO_DOUBLE error_type;
	char char_err;
	char str_err[MAX_LOADSTRING];
};
struct Pointer_int {
	int x, y;
};
struct Pointer {
	double x, y;
};

typedef enum CTL_ID CTL_ID;
typedef enum DRAWING_REBUILD DRAWING_REBUILD;
typedef struct Pointer_int Pointer_int;
typedef struct Pointer Pointer;


struct Ploting_struct {
	std::vector<struct Pointer_int> picsel;//вектор хранит пиксельные координаты x,y 
	std::vector<struct Pointer> myvec_xy;//вектор хранит реальные координаты x,y для каждой точки графика
	enum DRAWING_REBUILD Redraw;
};
struct Integral_struct {
	struct Ploting_struct vec;
	struct Ploting_struct integral_plot;
	double A, B, H;//получаемые из окна границы графика
};
struct Setka {
	int sx_center, sy_center;//мировые координаты центра СК
	double u_x_Left, u_x_Right, u_y_Top, u_y_Bottom;//МЕСТНЫЕ координаты края экрана графика [УСЛ ЕД] u_HHH;
	int p_x_Left, p_y_Bottom, p_x_Right, p_y_Top, p_x_LLeft5, p_y_BBottom5;//МЕСТНЫЕ координаты границы экрана графика [ПИКСЕЛ]

	int h_setka, h5_setka;//расстояние между квадратами сетки [пиксели]
	double u5_setka;//ширина большого квадрата [УСЛ ЕД]
	int mantissa;//мантисса для чисел сетки графика
	double kxy_zoom;//количество пикселей на условную единицу [ПИКСЕЛ/1 УСЛ ЕД]
	double unit_to_pixel;//количество условных единиц на 1 пиксел [УСЛ ЕД/1 ПИКСЕЛ]
	double unit_to_draw;

	int Wide_for_Vec_capasity;
	double Left_Wide_Vec_UNIT, Right_Wide_Vec_UNIT;//расстояние в количествах элементов вектора до границы вектора (для предотвращения запаздывания пересчета вектора при скроллинге и зуме)
	

};
struct Wnd_Plot_struct {
	HWND hWnd;//дескриптор окна для графика
	struct Setka setka;//информация о сетке окна дла графика
	int sx, sy;//размеры текущего окна для графика
	LPSTR text_;//функция после ввода вводе
};
struct SMouseMove {
	POINT Prev_mouse_point;//отслеживание движения  мыши 
	BOOL Flag_for_mouse;//после нажатия правой кнопки происходит захват координат и график шевелится
};


