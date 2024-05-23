#pragma once
#include "STD/stdafx.h"
#include "const_sys.h"
//���� ������
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
	std::vector<struct Pointer_int> picsel;//������ ������ ���������� ���������� x,y 
	std::vector<struct Pointer> myvec_xy;//������ ������ �������� ���������� x,y ��� ������ ����� �������
	enum DRAWING_REBUILD Redraw;
};
struct Integral_struct {
	struct Ploting_struct vec;
	struct Ploting_struct integral_plot;
	double A, B, H;//���������� �� ���� ������� �������
};
struct Setka {
	int sx_center, sy_center;//������� ���������� ������ ��
	double u_x_Left, u_x_Right, u_y_Top, u_y_Bottom;//������� ���������� ���� ������ ������� [��� ��] u_HHH;
	int p_x_Left, p_y_Bottom, p_x_Right, p_y_Top, p_x_LLeft5, p_y_BBottom5;//������� ���������� ������� ������ ������� [������]

	int h_setka, h5_setka;//���������� ����� ���������� ����� [�������]
	double u5_setka;//������ �������� �������� [��� ��]
	int mantissa;//�������� ��� ����� ����� �������
	double kxy_zoom;//���������� �������� �� �������� ������� [������/1 ��� ��]
	double unit_to_pixel;//���������� �������� ������ �� 1 ������ [��� ��/1 ������]
	double unit_to_draw;

	int Wide_for_Vec_capasity;
	double Left_Wide_Vec_UNIT, Right_Wide_Vec_UNIT;//���������� � ����������� ��������� ������� �� ������� ������� (��� �������������� ������������ ��������� ������� ��� ���������� � ����)
	

};
struct Wnd_Plot_struct {
	HWND hWnd;//���������� ���� ��� �������
	struct Setka setka;//���������� � ����� ���� ��� �������
	int sx, sy;//������� �������� ���� ��� �������
	LPSTR text_;//������� ����� ����� �����
};
struct SMouseMove {
	POINT Prev_mouse_point;//������������ ��������  ���� 
	BOOL Flag_for_mouse;//����� ������� ������ ������ ���������� ������ ��������� � ������ ���������
};


