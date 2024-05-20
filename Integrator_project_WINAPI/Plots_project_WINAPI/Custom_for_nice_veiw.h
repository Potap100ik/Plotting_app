#pragma once
#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"
/////////////////////////////////////////////////////////
// ��������� ��� ���� ���������
const int BASE_H_SETKA_INT = 8;//������ � �������� ������ ������ ���������� ��������� ��������
const int MIN_H_SETKA_INT = 2;
const int MAX_H_SETKA_INT = 16;
const int KOL_OF_SETKA_SQARES5 = 5;
//��������� ��� ���� �������
const int BASE_H_SETKA = 10;//������ � �������� ������ ������ ���������� ��������� ��������
const int MIN_H_SETKA = 2;
const int MAX_H_SETKA = 20;
const int BASE_U5_SETKA = 2;
//#define MINIMUM_H_SETKA 3
//#define MAXIMUM_H_SETKA 20


/////////////////////////////////////////////////////
//��������� ��� �������� ����
const int SYSTEMMETRICS = GetSystemMetrics(SM_CXSCREEN);
const Gdiplus::Color BACKGROUND_COLOR = Gdiplus::Color(255,11, 24, 69);
//������� ������������ �������� ����
//������������ ��������� ��������� (� ��������)
int Get_EDIT_FUNC_koordinates(int i);
int Get_EDIT_ABH_koordinates(char ch, int i);
int Get_EDIT_INTEGRAL_koordinates(int i);
int Get_EDIT_ERRORS_koordinates(int i);
int Get_BUTTON_ENTER_koordinates(CTL_ID id, int i);
//������� ������������ ��������� ������ ������ � ������
void SetEditTypingCenter(HWND hWnd, int(*Koord_func)(int));
void SetEditTypingCenter(HWND hWnd, char, int(*Koord_func)(char, int));
//����� �������� ��� ������ � ����������
const WCHAR Side_image_adress[] = L"BACKSTAGE.jpg";
const WCHAR Image_Home_btn[] = L"home.png";
const WCHAR Image_CLEAR_btn[] = L"clear.png";
//���������� ��� ���� � ��������
const int Left_Wnd_Plot_Board = 300;//��������� � �������� ����� ������� ������ � ��������
const int Width_for_background_image = Left_Wnd_Plot_Board - 10;//������ �������� ��� ����������
const int len_till_main_wnd_board = 5;//���������� �� ���� ���� � �������� �� ���� �������� ����
//����������� ������� ����
const int MINIMUM_BASE_WND_HEIGHT = 650;
const int MINIMUM_BASE_WND_WIDTH = 850;
///////////////////////////////////////////////////////////////////
//������������ ������
const COLORREF BTN_COLOR = RGB(66, 144, 218);
enum CUSTOM_BTN {
	SELECTBRUSH,
	HOTBRUSH,
	DEFAULTBRUSH,
	LEFT,
	RIGHT,
	GRADIENT,
	SOLID
};
Gdiplus::Pen* GetPen_for_Main_Plot();
Gdiplus::Pen* GetPen_for_Integral();
COLORREF GetGradColor_for_btn(CUSTOM_BTN brush, CUSTOM_BTN side);
COLORREF GetSolidColor_for_btn(CUSTOM_BTN brush);
HBRUSH CreateGradientBrush_in_horizont(COLORREF left, COLORREF right, LPNMCUSTOMDRAW item);
HBRUSH CreateGradientBrush_in_vertical(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item);
void CustomPushBTN(HWND& hwnd, LPNMHDR some_item, HBRUSH selectbrush, HBRUSH hotbrush, HBRUSH& defaultbrush,CUSTOM_BTN Brush_type, Gdiplus::Image* img = nullptr);


