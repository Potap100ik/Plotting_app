#include "Custom_for_nice_veiw.h"
#include "Main_files/type.h"
//////////////////////////////////////////////////////
//ЦВЕТ ДЛЯ ГРАФИКОВ
Gdiplus::Pen* GetPen_for_Integral()
{
	//цвет - это последние три знака
	//первый - прозрачность от 0 до 255
	//второй параметр - ширина ручки в пикселях
	return new Gdiplus::Pen(COLOR_FOR_INTEGRAL, WIDTH_OF_PEN_FOR_INTEGRAL);
}
Gdiplus::Pen* GetPen_for_Main_Plot()
{
	//цвет - это последние три знака
	//первый - прозрачность
	//второй параметр - ширина ручки в пикселях
	return new Gdiplus::Pen(Gdiplus::Color(255, 48, 188, 21), WIDTH_OF_PEN_FOR_INTEGRAL);
}
/////////////////////////////////////////////////////
//КООРДИНАТЫ ДЛЯ КОНТРОЛОВ
int Get_EDIT_FUNC_koordinates(int i)
{
	switch (i)
	{
	case 1: return EDIT_FUNC_KOORDINATES[0];
	case 2: return EDIT_FUNC_KOORDINATES[1];
	case 3: return EDIT_FUNC_KOORDINATES[2];
	case 4: return EDIT_FUNC_KOORDINATES[3];
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
		case 'A': return EDIT_ABH_KOORDINATES[0][0];
		case 'B': return EDIT_ABH_KOORDINATES[0][1];
		case 'H': return EDIT_ABH_KOORDINATES[0][2];
		}

		return 0;

	case 2: return EDIT_ABH_KOORDINATES[1][0];
	case 3: return EDIT_ABH_KOORDINATES[1][1];
	case 4: return EDIT_ABH_KOORDINATES[1][2];
	}
	return 0;
}
int Get_EDIT_INTEGRAL_koordinates(int i)
{
	switch (i)
	{
	case 1: return EDIT_INTEGRAL_KOORDINATES[0];
	case 2: return EDIT_INTEGRAL_KOORDINATES[1];
	case 3: return EDIT_INTEGRAL_KOORDINATES[2];
	case 4: return EDIT_INTEGRAL_KOORDINATES[3];
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
		case HWNDBUTTON_CLEARPLOT: return BUTTON_CLEARPLOT_KOORDINATES[i - 1];
		case HWNDBUTTON_HOME:  return BUTTON_HOME_KOORDINATES[i - 1];

		case HWNDBUTTON_INTEGER: return BUTTON_INTEGRAL_KOORDINATES[i-1];
		case HWNDBUTTON_ENTER: return BUTTON_ENTER_KOORDINATES[i-1];
		}
	case 2: //верхняя граница - y
		switch (id)
		{
		case HWNDBUTTON_HOME:    return BUTTON_HOME_KOORDINATES[i - 1];
		case HWNDBUTTON_ENTER: return BUTTON_ENTER_KOORDINATES[i - 1];

		case HWNDBUTTON_CLEARPLOT:       return BUTTON_CLEARPLOT_KOORDINATES[i - 1];
		case HWNDBUTTON_INTEGER: return BUTTON_INTEGRAL_KOORDINATES[i - 1];
		}
	case 3: //ширина - х
		switch (id)
		{
		case HWNDBUTTON_CLEARPLOT: return BUTTON_CLEARPLOT_KOORDINATES[i - 1];
		case HWNDBUTTON_HOME:  return BUTTON_HOME_KOORDINATES[i - 1];

		case HWNDBUTTON_INTEGER:return BUTTON_INTEGRAL_KOORDINATES[i - 1];
		case HWNDBUTTON_ENTER:return BUTTON_ENTER_KOORDINATES[i - 1];
		}
	case 4: //высота - y
		switch (id)
		{
		case HWNDBUTTON_HOME:      return BUTTON_HOME_KOORDINATES[i-1];
		case HWNDBUTTON_ENTER: return BUTTON_ENTER_KOORDINATES[i - 1];

		case HWNDBUTTON_CLEARPLOT:    return BUTTON_CLEARPLOT_KOORDINATES[i-1];
		case HWNDBUTTON_INTEGER:return BUTTON_INTEGRAL_KOORDINATES[i - 1];
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
			return BTN_SELECT_LEFT_COLOR;
		else if (side == RIGHT)
			return BTN_SELECT_RIGHT_COLOR;
	case HOTBRUSH:
		if (side == LEFT)
			return BTN_HOT_LEFT_COLOR;
		else if (side == RIGHT)
			return BTN_HOT_RIGHT_COLOR;
	case DEFAULTBRUSH:
		if (side == LEFT)
			return BTN_DEFAULT_LEFT_COLOR;
		else if (side == RIGHT)
			return BTN_DEFAULT_RIGHT_COLOR;
	}
	return RGB(255, 255, 255);
}
COLORREF GetSolidColor_for_btn(CUSTOM_BTN brush)
{
	switch (brush)
	{
	case SELECTBRUSH:
		return BTN_SELECT_COLOR;
	case HOTBRUSH:
		return BTN_HOT_COLOR;
	case DEFAULTBRUSH:
		return BTN_DEFAULT_COLOR;
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