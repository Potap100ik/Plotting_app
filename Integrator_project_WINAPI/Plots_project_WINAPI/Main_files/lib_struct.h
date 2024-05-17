#pragma once
#define MoveToEx(a, x, y, d); MoveToEx(a, x + Wnd_Plot->setka.sx_center, y*(-1) + Wnd_Plot->setka.sy_center, d);
#define LineTo(a, x, y); LineTo(a, x + Wnd_Plot->setka.sx_center, y*(-1) + Wnd_Plot->setka.sy_center);
#define TextOutW(dc, x, y, s, st); TextOutW(dc, x + Wnd_Plot->setka.sx_center, y*(-1) + Wnd_Plot->setka.sy_center, s, st);
//���������
#define MAX_LOADSTRING 100
#define edit_otst1 60
#define edit_otst2 20
//���� ������
enum CTL_ID {
	HWNDBUTTON_ENTER,
	HWNDBUTTON_CLEARPLOT,
	HWNDBUTTON_INTEGER,
	HWNDBUTTON_HOME,
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
	std::vector<Pointer> picsel;//������ ������ ���������� ���������� x,y 
	std::vector<Pointer> myvec_xy;//������ ������ �������� ���������� x,y ��� ������ ����� �������

};
typedef struct Integral_struct {
	Ploting_struct vec;
	Ploting_struct integral_plot;
	double A, B, H;//���������� �� ���� ������� �������
};
typedef struct Setka {
	int sx_center, sy_center;//������� ���������� ������ ��
	double LLeft, RRight, TTop, BBottom;//������� ���������� ���� ������ ������� [��� ��] u_HHH;
	int x_LL, y_BB, x_RR, y_TT, x_LL5, y_BB5;//������� ���������� ������� ������ ������� [������]

	int h_setka, h5_setka;//���������� ����� ���������� ����� [�������]
	double u5_setka;//������ �������� �������� [��� ��]
	int mantissa;//�������� ��� ����� ����� �������
	double kxy_zoom;//���������� �������� �� �������� ������� [������/1 ��� ��]
	double unit_to_pixel;//���������� �������� ������ �� 1 ������ [��� ��/1 ������]
	int Wide_Vec, Left_Wide_Vec, Right_Wide_Vec;//���������� � ����������� ��������� ������� �� ������� ������� (��� �������������� ������������ ��������� ������� ��� ���������� � ����)
	
}MySetka;
typedef struct Wnd_Plot_struct {
	HWND hWnd;
	MySetka setka;
	int sx, sy;//������� �������� ����
	DRAWING_WAY Draw_way;
	LPSTR text_;
}MyWnd_Plot;
typedef struct SMouseMove {
	POINT Prev_mouse_point{};
	BOOL Flag_for_mouse;
}MouseMove;


