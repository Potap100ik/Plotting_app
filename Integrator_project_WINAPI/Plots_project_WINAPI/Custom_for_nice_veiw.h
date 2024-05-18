#pragma once
#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"

const int FONTSIZE = 16;
const int FONTWIDTH = FW_BLACK;

const WCHAR ENTER_BTN_STR[] = L"Построить график";
const WCHAR CLEAR_BTN_STR[] = L"Убрать данные графика";

const Gdiplus::Color BACKGROUND_COLOR = Gdiplus::Color(255,11, 24, 69);

int Get_EDIT_FUNC_koordinates(int i);
int Get_EDIT_ABH_koordinates(char ch, int i);
int Get_EDIT_INTEGRAL_koordinates(int i);
int Get_EDIT_ERRORS_koordinates(int i);

int Get_STATIC_FUNC_doordinates(int i);
int Get_STATIC_ABH_koordinates(char ch, int i);
int Get_STATIC_INTEGRAL_koordinates(int i);
int Get_STATIC_ERRORS_koordinates(int i);
int Get_MEMORY_CARD_koordinates(int i);

int Get_BUTTON_ENTER_koordinates(CTL_ID id, int i);

void SetEditTypingCenter(HWND hWnd, int(*Koord_func)(int));
void SetEditTypingCenter(HWND hWnd, char, int(*Koord_func)(char, int));

Gdiplus::Bitmap* CreateBitmapFor_MAINWND(int img_height, int img_width);
Gdiplus::Image* CreateImageFor_MAINWND(int img_height, int img_width);

const WCHAR Side_image_adress[] = L"BACKSTAGE.jpg";
const WCHAR Image_Home_btn[] = L"Home_btn.png";
const WCHAR Image_INTEGRAL_btn[] = L"Integer_btn.png";

const WCHAR IMAGE_FOR_EDIT_BASE[] =  L"Bitmaps/Edit_BASE.png";
const WCHAR IMAGE_FOR_EDIT_A[] =  L"Bitmaps/Edit_A.png" ;
const WCHAR IMAGE_FOR_EDIT_B[] =  L"Bitmaps/Edit_B.png" ;
const WCHAR IMAGE_FOR_EDIT_H[] =  L"Bitmaps/Edit_H.png" ;
const WCHAR IMAGE_FOR_EDIT_INTEGRAL[] =  L"Bitmaps/Edit_INTEGRAL.png";

const WCHAR IMAGE_FOR_EDIT_ERRORS[] = L"Edit_ERRORS.png";
const WCHAR	IMAGE_FOR_MEMORY_CARD[] = L"Memory_CARD.png";

const WCHAR IMAGE_FOR_BUTTONS_ENTER[3][MAX_LOADSTRING] = {{L"Bitmaps/selected_btn_ENTER.png"},{L"Bitmaps/hot_btn_ENTER.png"},{L"Bitmaps/default_btn_ENTER.png"} };
const WCHAR IMAGE_FOR_BUTTONS_CLEAR[3][MAX_LOADSTRING] = { {L"Bitmaps/selected_btn_CLEAR.png"},{L"Bitmaps/hot_btn_CLEAR.png"},{L"Bitmaps/default_btn_CLEAR.png"} };
const WCHAR IMAGE_FOR_BUTTONS_HOME[3][MAX_LOADSTRING] = { {L"Bitmaps/selected_btn_HOME.png"},{L"Bitmaps/hot_btn_HOME.png"},{L"Bitmaps/default_btn_HOME.png"} };
const WCHAR IMAGE_FOR_BUTTONS_INTEGRAL[3][MAX_LOADSTRING] = { {L"Bitmaps/selected_btn_INTEGRAL.png"},{L"Bitmaps/hot_btn_INTEGRAL.png"},{L"Bitmaps/default_btn_INTEGRAL.png"} };


const int Left_Plot_Edge = 300;//растояние в пикселях левой границы экрана с графиком
const int Right_img_edge = Left_Plot_Edge - 10;


const int MINIMUM_BASE_WND_HEIGHT = 550;
const int MINIMUM_BASE_WND_WIDTH = 850;

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
void CustomBTN_SET_IMAGE(HWND& hwnd, LPNMHDR some_item, Gdiplus::Bitmap** img);


