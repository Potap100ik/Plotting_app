#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"
//////////////////////////////////////////////////////
//ЦВЕТ ДЛЯ ГРАФИКОВ
Gdiplus::Pen* GetPen_for_Integral()
{
	//цвет - это последние три знака
	//первый - прозрачность от 0 до 255
	//второй параметр - ширина ручки в пикселях
	return new Gdiplus::Pen(Gdiplus::Color(255, 255, 0, 0), 2);
}
Gdiplus::Pen* GetPen_for_Main_Plot()
{
	//цвет - это последние три знака
	//первый - прозрачность
	//второй параметр - ширина ручки в пикселях
	return new Gdiplus::Pen(Gdiplus::Color(255, 48, 188, 21), 3);
}
/////////////////////////////////////////////////////
//КООРДИНАТЫ ДЛЯ КОНТРОЛОВ
int Get_EDIT_FUNC_koordinates(int i)
{
	switch (i)
	{
	case 1: return 59;
	case 2: return 32;
	case 3: return 215;
	case 4: return 43;
	}
	return 0;
}
int Get_EDIT_ABH_koordinates(char ch, int i)
{
	switch (i)
	{
	case 1:
		switch (ch)
		{
		case 'A': return 43;
		case 'B': return 136;
		case 'H': return 230;
		}

		return 59;

	case 2: return 104;
	case 3: return 50;
	case 4: return 25;
	}
	return 0;
}
int Get_EDIT_INTEGRAL_koordinates(int i)
{
	switch (i)
	{
	case 1: return 94;
	case 2: return 244;
	case 3: return 183;
	case 4: return 38;
	}
	return 0;
}
int Get_EDIT_ERRORS_koordinates(int i)
{
	switch (i)
	{
	case 1: return 13;
	case 2: return 299;
	case 3: return 265;
	case 4: return 41;
	}
	return 0;
}
int Get_BUTTON_ENTER_koordinates(CTL_ID id, int i)
{

	switch (i)
	{
	case 1: //левая граница - х
		switch (id)
		{
		case HWNDBUTTON_CLEARPLOT: return 13;
		case HWNDBUTTON_HOME:  return 13;

		case HWNDBUTTON_INTEGER: return 61;
		case HWNDBUTTON_ENTER: return 61;
		}
	case 2: //верхняя граница - y
		switch (id)
		{
		case HWNDBUTTON_HOME:    return 145;
		case HWNDBUTTON_ENTER: return 145;

		case HWNDBUTTON_CLEARPLOT:       return 193;
		case HWNDBUTTON_INTEGER: return 193;
		}
	case 3: //ширина - х
		switch (id)
		{
		case HWNDBUTTON_CLEARPLOT: return 32;
		case HWNDBUTTON_HOME:  return 32;

		case HWNDBUTTON_INTEGER:return 216;
		case HWNDBUTTON_ENTER:return 216;
		}
	case 4: //высота - y
		switch (id)
		{
		case HWNDBUTTON_HOME:      return 32;
		case HWNDBUTTON_ENTER: return 32;

		case HWNDBUTTON_CLEARPLOT:    return 32;
		case HWNDBUTTON_INTEGER:return 32;
		}
	}
	return 0;
}
//УСТАНОВКА КООРДИНАТ ДЛЯ ВЫВОДА В ЭДИТЫ (ВЕРТИКАЛЬНЫЙ ЦЕНТР)
void SetEditTypingCenter(HWND hWnd, int(*Koord_func)(int))
{
	//отступ сверху, высота шрифта = 20 пикселей
	int otst = (Koord_func(4) - 16)/2;
	RECT rc{}; 
	rc.left = 5;
	rc.top = otst;

	rc.right = Koord_func(3);
	rc.bottom = Koord_func(4);
	SendMessage(hWnd, EM_SETRECT, 0, (LPARAM)(RECT FAR*) & rc);

}
void SetEditTypingCenter(HWND hWnd, char ch, int(*Koord_func)(char, int))
{
	//отступ сверху, высота шрифта = 20 пикселей
	int otst = (Koord_func(ch,4) - 16) / 2;
	RECT rc{};
	rc.left = 5;
	rc.top = otst;

	rc.right = Koord_func(ch, 3);
	rc.bottom = Koord_func(ch, 4);
	SendMessage(hWnd, EM_SETRECT, 0, (LPARAM)(RECT FAR*) & rc);
}
//КАСТОМИЗАЦИЯ КНОПОК - УСТАНОВКА ЦВЕТА ДЛЯ ГРАДИЕНТА И СПЛОШНОГО ЦВЕТА
COLORREF GetGradColor_for_btn(CUSTOM_BTN brush, CUSTOM_BTN side)
{
	switch (brush)
	{
	case SELECTBRUSH:
		if (side == LEFT)
			return RGB(23, 76, 144);
		else if (side == RIGHT)
			return RGB(23, 76, 144);
	case HOTBRUSH:
		if (side == LEFT)
			return RGB(23, 76, 144);
		else if (side == RIGHT)
			return RGB(66, 144, 218);
	case DEFAULTBRUSH:
		if (side == LEFT)
			return RGB(66, 144, 218);
		else if (side == RIGHT)
			return RGB(23, 76, 144);
	}
	return RGB(255, 255, 255);
}
COLORREF GetSolidColor_for_btn(CUSTOM_BTN brush)
{
	switch (brush)
	{
	case SELECTBRUSH:
		return RGB(23, 76, 144);
	case HOTBRUSH:
		return RGB(66, 144, 255);
	case DEFAULTBRUSH:
		return RGB(66, 144, 218);
	}
	return RGB(255, 255, 255);
}
HBRUSH CreateGradientBrush_in_horizont(COLORREF left, COLORREF right, LPNMCUSTOMDRAW item)//делаем красиво и градиентно
{
	HBRUSH Brush = NULL;
	HDC hdcmem = CreateCompatibleDC(item->hdc);
	HBITMAP hbitmap = CreateCompatibleBitmap(item->hdc, item->rc.right - item->rc.left, item->rc.bottom - item->rc.top);
	SelectObject(hdcmem, hbitmap);

	int r1 = GetRValue(left), r2 = GetRValue(right), g1 = GetGValue(left), g2 = GetGValue(right), b1 = GetBValue(left), b2 = GetBValue(right);
	for (int i = 0; i < item->rc.right - item->rc.left; i++)
	{
		RECT temp;
		int r, g, b;
		r = int(r1 + double(i * (r2 - r1) / item->rc.right - item->rc.left));
		g = int(g1 + double(i * (g2 - g1) / item->rc.right - item->rc.left));
		b = int(b1 + double(i * (b2 - b1) / item->rc.right - item->rc.left));
		Brush = CreateSolidBrush(RGB(r, g, b));
		temp.left = i;
		temp.top = 0;
		temp.right = i + 1;
		temp.bottom = item->rc.bottom - item->rc.top;//попиксельно закрашиваем прямоугольник
		FillRect(hdcmem, &temp, Brush);
		DeleteObject(Brush);
	}
	HBRUSH pattern = CreatePatternBrush(hbitmap);
	DeleteDC(hdcmem);
	DeleteObject(Brush);
	DeleteObject(hbitmap);
	return pattern;
}
HBRUSH CreateGradientBrush_in_vertical(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item)//делаем красиво и градиентно
{
	HBRUSH Brush = NULL;
	HDC hdcmem = CreateCompatibleDC(item->hdc);
	HBITMAP hbitmap = CreateCompatibleBitmap(item->hdc, item->rc.right - item->rc.left, item->rc.bottom - item->rc.top);
	SelectObject(hdcmem, hbitmap);

	int r1 = GetRValue(top), r2 = GetRValue(bottom), g1 = GetGValue(top), g2 = GetGValue(bottom), b1 = GetBValue(top), b2 = GetBValue(bottom);
	for (int i = 0; i < item->rc.bottom - item->rc.top; i++)
	{
		RECT temp;
		int r, g, b;
		r = int(r1 + double(i * (r2 - r1) / item->rc.bottom - item->rc.top));
		g = int(g1 + double(i * (g2 - g1) / item->rc.bottom - item->rc.top));
		b = int(b1 + double(i * (b2 - b1) / item->rc.bottom - item->rc.top));
		Brush = CreateSolidBrush(RGB(r, g, b));
		temp.left = 0;
		temp.top = i;
		temp.right = item->rc.right - item->rc.left;
		temp.bottom = i + 1;
		FillRect(hdcmem, &temp, Brush);
		DeleteObject(Brush);
	}
	HBRUSH pattern = CreatePatternBrush(hbitmap);

	DeleteDC(hdcmem);
	DeleteObject(Brush);
	DeleteObject(hbitmap);

	return pattern;
}
void CustomPushBTN(HWND& hwnd, LPNMHDR some_item, HBRUSH selectbrush, HBRUSH hotbrush, HBRUSH& defaultbrush, CUSTOM_BTN Brush_type, Gdiplus::Image* img)
{
	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	int right = item->rc.right, left = item->rc.left, top = item->rc.top, bottom = item->rc.bottom;
	if (item->uItemState & CDIS_SELECTED)
	{
		if (selectbrush == NULL)
			if (Brush_type == GRADIENT)
				selectbrush = CreateGradientBrush_in_horizont(GetGradColor_for_btn(SELECTBRUSH, LEFT), GetGradColor_for_btn(SELECTBRUSH, RIGHT), item);
			else
				selectbrush = CreateSolidBrush(GetSolidColor_for_btn(SELECTBRUSH));

		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, BTN_COLOR);

		HGDIOBJ old_pen = SelectObject(item->hdc, pen);
		HGDIOBJ old_brush = SelectObject(item->hdc, selectbrush);

		Rectangle(item->hdc, left, top, right, bottom);
		
		if (img != nullptr)
		{
			Gdiplus::Graphics graph(item->hdc);
			graph.DrawImage(img, left, top, right, bottom);
		}

		SelectObject(item->hdc, old_pen);
		SelectObject(item->hdc, old_brush);
		DeleteObject(pen);
		return;
	}
	else
	{
		if (item->uItemState & CDIS_HOT)
		{
			if (hotbrush == NULL)
				if (Brush_type == GRADIENT)
					hotbrush = CreateGradientBrush_in_horizont(GetGradColor_for_btn(HOTBRUSH, LEFT), GetGradColor_for_btn(HOTBRUSH, RIGHT), item);
				else
					hotbrush = CreateSolidBrush(GetSolidColor_for_btn(HOTBRUSH));
			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, BTN_COLOR);

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

			Rectangle(item->hdc, left, top, right, bottom);
;
			if (img != nullptr)
			{
				Gdiplus::Graphics graph(item->hdc);
				graph.DrawImage(img, left, top, right, bottom);
			}
			SelectObject(item->hdc, old_pen);
			SelectObject(item->hdc, old_brush);
			DeleteObject(pen);

			return;
		}

		if (defaultbrush == NULL)
			//if (Brush_type == GRADIENT)
			//	defaultbrush = CreateGradientBrush_in_horizont(GetGradColor_for_btn(DEFAULTBRUSH, LEFT), GetGradColor_for_btn(DEFAULTBRUSH, RIGHT), item);
			//else
				defaultbrush = CreateSolidBrush(GetSolidColor_for_btn(DEFAULTBRUSH));
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, BTN_COLOR);

		HGDIOBJ old_pen = SelectObject(item->hdc, pen);
		HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

		Rectangle(item->hdc, left, top, right, bottom);

		if (img != nullptr)
		{
			Gdiplus::Graphics graph(item->hdc);
			graph.DrawImage(img, left, top, right, bottom);
		}

		SelectObject(item->hdc, old_pen);
		SelectObject(item->hdc, old_brush);
		DeleteObject(pen);
		return;
	}
}