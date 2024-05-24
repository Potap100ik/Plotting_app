#pragma once
#include "Main_files/type.h"
#include "Main_files/STD/stdafx.h"
/////////////////////////////////////////////////////
//КОНСТАНТЫ ДЛЯ  КАСТОМА ГЛАВНОГО ОКНА
const Gdiplus::Color BACKGROUND_COLOR = Gdiplus::Color(255,11, 24, 69);
/////////////////////////////////////////////////////////////////////////////////
//АДРЕС КАРТИНОК ДЛЯ КНОПОК И БЭКГРАУНДА
const WCHAR Side_image_adress[] = L"BACKSTAGE.jpg";
const WCHAR Image_Home_btn[] = L"home.png";
const WCHAR Image_CLEAR_btn[] = L"clear.png";
//КООРДИНАТЫ ДЛЯ ОКНА С ГРИФИКОМ
const int Left_Wnd_Plot_Board = 300;//растояние в пикселях левой границы экрана с графиком
const int Width_for_background_image = Left_Wnd_Plot_Board - 10;//ШИРИНА картинки для бэкграунда
const int len_till_main_wnd_board = 5;//расстояние от края окна с графиком до края главного окна
//МИНИМАЛЬНЫЕ РАЗМЕРЫ РАБОЧЕГО ОКНА
const int MINIMUM_BASE_WND_HEIGHT = 650;
const int MINIMUM_BASE_WND_WIDTH = 850;
///////////////////////////////////////////////////////////////////
// ГРАФИК И ЕГО ЦВЕТА
const COLORREF BTN_COLOR = RGB(66, 144, 218);//БАЗОВЫЙ ЦВЕТ КНОПОК
//
const int WIDTH_OF_PEN_FOR_MAIN_PLOT = 3;
const Gdiplus::Color COLOR_FOR_MAIN_PLOT(255, 56, 160, 70);
//56, 140, 70
// 199, 68, 64
//rgb(45,112,179) - СИНИЙ В DESMOS
//rgb(96,66,166) - ФИОЛЕТКА
const int WIDTH_OF_PEN_FOR_INTEGRAL = 3;
const Gdiplus::Color COLOR_FOR_INTEGRAL(255, 240, 68, 64);
//
const COLORREF BIG_SETKA_SQARE_COLOR = RGB(153, 153, 153);
const COLORREF  SMALL_SETKA_SQARE_COLOR = RGB(224, 224, 224);
const COLORREF OSI_SETKA_COLOR = RGB(47, 47, 47);
const COLORREF BCKGRND_SETKA_COLOR = RGB(255, 255, 255);
///////////////////////////////////////////////////////////////////
//КНОПКИ И КОНТРОЛЫ
//КОНСТАНТЫ
const int EDIT_FUNC_KOORDINATES[4] =		{59,32,215,43};
const int EDIT_ABH_KOORDINATES[2][3] = {	{43,
/*											*/136,
/*											*/230},//LEFT X ABH KOORD
/*											 */{104,50,25}};
const int EDIT_INTEGRAL_KOORDINATES[4] =	{94,244,183,38};
const int BUTTON_ENTER_KOORDINATES[4] =		{61,145,216,32};
const int BUTTON_INTEGRAL_KOORDINATES[4] =	{61,193,216,32};
const int BUTTON_CLEARPLOT_KOORDINATES[4] = {13,193,32,32};
const int BUTTON_HOME_KOORDINATES[4] =		{13,145,32,32};
const COLORREF BTN_SELECT_COLOR = RGB(23, 76, 144);
const COLORREF BTN_SELECT_LEFT_COLOR = RGB(23, 76, 144);
const COLORREF BTN_SELECT_RIGHT_COLOR = RGB(23, 76, 144);

const COLORREF BTN_HOT_COLOR = RGB(66, 144, 255);
const COLORREF BTN_HOT_LEFT_COLOR = RGB(23, 76, 144);
const COLORREF BTN_HOT_RIGHT_COLOR = RGB(66, 144, 218);

const COLORREF BTN_DEFAULT_COLOR = RGB(66, 144, 218);
const COLORREF BTN_DEFAULT_LEFT_COLOR = RGB(66, 144, 218);
const COLORREF BTN_DEFAULT_RIGHT_COLOR = RGB(23, 76, 144);
//////////////////////////////////////////////////////////////////////
//ФУНКЦИИ
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
//ФУНКЦИИ КАСТОМИЗАЦИИ ГЛАВНОГО ОКНА
//УСТАНОВЛЕНИЕ КООРДИНАТ КОНТРОЛОВ (В ПИКСЕЛЯХ)
int Get_EDIT_FUNC_koordinates(int i);
int Get_EDIT_ABH_koordinates(char ch, int i);
int Get_EDIT_INTEGRAL_koordinates(int i);
int Get_EDIT_ERRORS_koordinates(int i);
int Get_BUTTON_ENTER_koordinates(CTL_ID id, int i);
//ФУНКЦИИ УСТАНОВЛЕНИЯ КООРДИНАТ ВЫВОДА ТЕКСТА В ЭДИТАХ
void SetEditTypingCenter(HWND hWnd, int(*Koord_func)(int));
void SetEditTypingCenter(HWND hWnd, char, int(*Koord_func)(char, int));

