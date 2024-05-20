#pragma once
//���������
#define MAX_LOADSTRING 100
const int WM_DRAW_MAIN_PLOT = WM_USER;
const int WM_HOME_BTN_CLICKED = WM_USER + 1;
const int WM_CLEAR_PLOT = WM_USER + 2;
const int WM_RESIZE_PLOT = WM_USER + 3;


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
struct Pointer_int {
	int x, y;
};
struct Pointer {
	double x, y;
};

typedef struct Ploting_struct {
	std::vector<Pointer_int> picsel;//������ ������ ���������� ���������� x,y 
	std::vector<Pointer> myvec_xy;//������ ������ �������� ���������� x,y ��� ������ ����� �������
	DRAWING_REBUILD Redraw;
};
typedef struct Integral_struct {
	Ploting_struct vec;
	Ploting_struct integral_plot;
	double A, B, H;//���������� �� ���� ������� �������
};
typedef struct Setka {
	int sx_center, sy_center;//������� ���������� ������ ��
	double u_x_Left, u_x_Right, u_y_Top, u_y_Bottom;//������� ���������� ���� ������ ������� [��� ��] u_HHH;
	int p_x_Left, p_y_Bottom, p_x_Right, p_y_Top, p_x_LLeft5, p_y_BBottom5;//������� ���������� ������� ������ ������� [������]

	int h_setka, h5_setka;//���������� ����� ���������� ����� [�������]
	double u5_setka;//������ �������� �������� [��� ��]
	int mantissa;//�������� ��� ����� ����� �������
	double kxy_zoom;//���������� �������� �� �������� ������� [������/1 ��� ��]
	double unit_to_pixel;//���������� �������� ������ �� 1 ������ [��� ��/1 ������]
	int Wide_for_Vec_capasity;
	double Left_Wide_Vec_UNIT, Right_Wide_Vec_UNIT;//���������� � ����������� ��������� ������� �� ������� ������� (��� �������������� ������������ ��������� ������� ��� ���������� � ����)
	
}MySetka;
typedef struct Wnd_Plot_struct {
	HWND hWnd;//���������� ���� ��� �������
	MySetka setka;//���������� � ����� ���� ��� �������
	int sx, sy;//������� �������� ���� ��� �������
	LPSTR text_;//������� ����� ����� �����
}MyWnd_Plot;
typedef struct SMouseMove {
	POINT Prev_mouse_point;//������������ ��������  ���� 
	BOOL Flag_for_mouse;//����� ������� ������ ������ ���������� ������ ��������� � ������ ���������
}MouseMove;


