#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"

int Get_STATIC_FUNC_doordinates(int i)
{
	switch (i)
	{
	case 1: return 8;
	case 2: return 8;
	case 3: return 274;
	case 4: return 69;
	}
	return 0;
}
int Get_EDIT_FUNC_koordinates(int i)
{
	switch (i)
	{
	case 1: return 59;
	case 2: return 32;
	case 3: return 215;
	case 4: return 45;
	}
	return 0;
}
int Get_STATIC_ABH_koordinates(char ch, int i)
{
	switch (i)
	{
	case 1:
		switch (ch)
		{
		case 'A': return 8;
		case 'B': return 102;
		case 'H': return 196;
		}

		return 59;

	case 2: return 87;// 104;
	case 3: return 85;
	case 4: return 45;
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
int Get_STATIC_INTEGRAL_koordinates(int i)
{
	switch (i)
	{
	case 1: return 8;
	case 2: return 244;
	case 3: return 269;
	case 4: return 38;
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
int Get_STATIC_ERRORS_koordinates(int i)
{
	switch (i)
	{
	case 1: return 8;
	case 2: return 302;
	case 3: return 267;
	case 4: return 34;
	}
	return 0;
}
int Get_EDIT_ERRORS_koordinates(int i)
{
	switch (i)
	{
	case 1: return 15;
	case 2: return 302;
	case 3: return 260;
	case 4: return 34;
	}
	return 0;
}

int Get_MEMORY_CARD_koordinates(int i)
{
	switch (i)
	{
	case 1: return 8;
	case 2: return 344;
	case 3: return 267;
	case 4: return 150;
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
		case HWNDBUTTON_CLEARPLOT: return 8;
		case HWNDBUTTON_HOME:  return 8;

		case HWNDBUTTON_INTEGER: return 56;
		case HWNDBUTTON_ENTER: return 56;
		}
	case 2: //верхняя граница - y
		switch (id)
		{
		case HWNDBUTTON_HOME:    return 141;
		case HWNDBUTTON_ENTER: return 141;

		case HWNDBUTTON_CLEARPLOT:       return 191;
		case HWNDBUTTON_INTEGER: return 191;
		}
	case 3: //ширина - х
		switch (id)
		{
		case HWNDBUTTON_CLEARPLOT: return 40;
		case HWNDBUTTON_HOME:  return 40;

		case HWNDBUTTON_INTEGER:return 225;
		case HWNDBUTTON_ENTER:return 225;
		}
	case 4: //высота - y
		switch (id)
		{
		case HWNDBUTTON_HOME:      return 40;
		case HWNDBUTTON_ENTER: return 40;

		case HWNDBUTTON_CLEARPLOT:    return 40;
		case HWNDBUTTON_INTEGER:return 40;
		}
	}
	return 0;
}

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

Gdiplus::Bitmap* CreateBitmapFor_MAINWND(int img_height, int img_width)
{

	Gdiplus::Bitmap* buffer = new (Gdiplus::Bitmap)(img_height, img_width);
	Gdiplus::Graphics* graph = new (Gdiplus::Graphics)(buffer);

	Gdiplus::Bitmap* img_for_BASE_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_BASE);
	Gdiplus::Bitmap* img_for_A_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_A);
	Gdiplus::Bitmap* img_for_B_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_B);
	Gdiplus::Bitmap* img_for_H_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_H);
	Gdiplus::Bitmap* img_for_INTEGAL_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_INTEGRAL);
	Gdiplus::Bitmap* img_for_ERRORS_edit = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_INTEGRAL);
	Gdiplus::Bitmap* img_for_MEMORY_CARD = Gdiplus::Bitmap::FromFile(IMAGE_FOR_EDIT_INTEGRAL);



	graph->Clear(BACKGROUND_COLOR);
	
	graph->DrawImage(img_for_BASE_edit,
		Get_STATIC_FUNC_doordinates(1),
		Get_STATIC_FUNC_doordinates(2),
		Get_STATIC_FUNC_doordinates(3),
		Get_STATIC_FUNC_doordinates(4));

	graph->DrawImage(img_for_A_edit,
		Get_STATIC_ABH_koordinates('A', 1),
		Get_STATIC_ABH_koordinates('A', 2),
		Get_STATIC_ABH_koordinates('A', 3),
		Get_STATIC_ABH_koordinates('A', 4));
	graph->DrawImage(img_for_B_edit,
		Get_STATIC_ABH_koordinates('B', 1),
		Get_STATIC_ABH_koordinates('B', 2),
		Get_STATIC_ABH_koordinates('B', 3),
		Get_STATIC_ABH_koordinates('B', 4));
	graph->DrawImage(img_for_H_edit,
		Get_STATIC_ABH_koordinates('H', 1),
		Get_STATIC_ABH_koordinates('H', 2),
		Get_STATIC_ABH_koordinates('H', 3),
		Get_STATIC_ABH_koordinates('H', 4));

	graph->DrawImage(img_for_INTEGAL_edit,
		Get_STATIC_INTEGRAL_koordinates(1),
		Get_STATIC_INTEGRAL_koordinates(2),
		Get_STATIC_INTEGRAL_koordinates(3),
		Get_STATIC_INTEGRAL_koordinates(4));

	graph->DrawImage(img_for_INTEGAL_edit,
		Get_STATIC_ERRORS_koordinates(1),
		Get_STATIC_ERRORS_koordinates(2),
		Get_STATIC_ERRORS_koordinates(3),
		Get_STATIC_ERRORS_koordinates(4));

	graph->DrawImage(img_for_INTEGAL_edit,
		Get_MEMORY_CARD_koordinates(1),
		Get_MEMORY_CARD_koordinates(2),
		Get_MEMORY_CARD_koordinates(3),
		Get_MEMORY_CARD_koordinates(4));

	delete graph;

	delete img_for_BASE_edit;
	delete img_for_A_edit;
	delete img_for_B_edit;
	delete img_for_H_edit;
	delete img_for_INTEGAL_edit;
	delete img_for_ERRORS_edit;
	delete 	img_for_MEMORY_CARD;

	return buffer;
}
Gdiplus::Image* CreateImageFor_MAINWND(int img_height, int img_width)
{

	Gdiplus::Bitmap* buffer = new (Gdiplus::Bitmap)(img_height, img_width);
	Gdiplus::Graphics* graph = new (Gdiplus::Graphics)(buffer);

	Gdiplus::Image* img_for_BASE_edit = Gdiplus::Image::FromFile(IMAGE_FOR_EDIT_BASE);
	Gdiplus::Image* img_for_A_edit = Gdiplus::Image::FromFile(IMAGE_FOR_EDIT_A);
	Gdiplus::Image* img_for_B_edit = Gdiplus::Image::FromFile(IMAGE_FOR_EDIT_B);
	Gdiplus::Image* img_for_H_edit = Gdiplus::Image::FromFile(IMAGE_FOR_EDIT_H);
	Gdiplus::Image* img_for_INTEGAL_edit = Gdiplus::Image::FromFile(IMAGE_FOR_EDIT_INTEGRAL);
	Gdiplus::Image* img_for_ERRORS_edit = Gdiplus::Image::FromFile(IMAGE_FOR_EDIT_INTEGRAL);
	Gdiplus::Image* img_for_MEMORY_CARD = Gdiplus::Image::FromFile(IMAGE_FOR_EDIT_INTEGRAL);



	graph->Clear(BACKGROUND_COLOR);

	graph->DrawImage(img_for_BASE_edit,
		Get_STATIC_FUNC_doordinates(1),
		Get_STATIC_FUNC_doordinates(2),
		Get_STATIC_FUNC_doordinates(3),
		Get_STATIC_FUNC_doordinates(4));

	graph->DrawImage(img_for_A_edit,
		Get_STATIC_ABH_koordinates('A', 1),
		Get_STATIC_ABH_koordinates('A', 2),
		Get_STATIC_ABH_koordinates('A', 3),
		Get_STATIC_ABH_koordinates('A', 4));
	graph->DrawImage(img_for_B_edit,
		Get_STATIC_ABH_koordinates('B', 1),
		Get_STATIC_ABH_koordinates('B', 2),
		Get_STATIC_ABH_koordinates('B', 3),
		Get_STATIC_ABH_koordinates('B', 4));
	graph->DrawImage(img_for_H_edit,
		Get_STATIC_ABH_koordinates('H', 1),
		Get_STATIC_ABH_koordinates('H', 2),
		Get_STATIC_ABH_koordinates('H', 3),
		Get_STATIC_ABH_koordinates('H', 4));

	graph->DrawImage(img_for_INTEGAL_edit,
		Get_STATIC_INTEGRAL_koordinates(1),
		Get_STATIC_INTEGRAL_koordinates(2),
		Get_STATIC_INTEGRAL_koordinates(3),
		Get_STATIC_INTEGRAL_koordinates(4));

	graph->DrawImage(img_for_INTEGAL_edit,
		Get_STATIC_ERRORS_koordinates(1),
		Get_STATIC_ERRORS_koordinates(2),
		Get_STATIC_ERRORS_koordinates(3),
		Get_STATIC_ERRORS_koordinates(4));

	graph->DrawImage(img_for_INTEGAL_edit,
		Get_MEMORY_CARD_koordinates(1),
		Get_MEMORY_CARD_koordinates(2),
		Get_MEMORY_CARD_koordinates(3),
		Get_MEMORY_CARD_koordinates(4));

	delete graph;

	delete img_for_BASE_edit;
	delete img_for_A_edit;
	delete img_for_B_edit;
	delete img_for_H_edit;
	delete img_for_INTEGAL_edit;
	delete img_for_ERRORS_edit;
	delete 	img_for_MEMORY_CARD;

	return buffer;
}

Gdiplus::Pen* GetPen_for_Integral()
{
	//цвет - это последние три знака
	//первый - прозрачность от 0 до 255
	//второй параметр - ширина ручки в пикселях
	return new Pen(Color(255, 255, 0, 0), 2);
}

Gdiplus::Pen* GetPen_for_Main_Plot()
{
	//цвет - это последние три знака
	//первый - прозрачность
	//второй параметр - ширина ручки в пикселях
	return new Pen(Color(255, 0, 255, 0), 2);
}

COLORREF GetGradColor_for_btn(CUSTOM_BTN brush, CUSTOM_BTN side)
{

	switch (brush)
	{
	case SELECTBRUSH:
		if (side == LEFT)
			return RGB(30, 150, 200);
		else if (side == RIGHT)
			return RGB(0, 222, 200);
	case HOTBRUSH:
		if (side == LEFT)
			return RGB(0, 200, 255);
		else if (side == RIGHT)
			return RGB(0, 150, 220);
	case DEFAULTBRUSH:
		if (side == LEFT)
			return RGB(0, 255, 245);
		else if (side == RIGHT)
			return RGB(0, 220, 255);
	}

	return RGB(255, 255, 255);
}
COLORREF GetSolidColor_for_btn(CUSTOM_BTN brush)
{

	switch (brush)
	{
	case SELECTBRUSH:
		return RGB(0, 222, 200);
	case HOTBRUSH:
		return RGB(0, 200, 180);
	case DEFAULTBRUSH:
		return RGB(0, 230, 255);
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

	if (item->uItemState & CDIS_SELECTED)
	{
		//Select our color when the button is selected
		if (selectbrush == NULL)
			if (Brush_type == GRADIENT)
				selectbrush = CreateGradientBrush_in_horizont(GetGradColor_for_btn(SELECTBRUSH, LEFT), GetGradColor_for_btn(SELECTBRUSH, RIGHT), item);
			else
				selectbrush = CreateSolidBrush(GetSolidColor_for_btn(SELECTBRUSH));
		//Create pen for button border
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		//Select our brush into hDC
		HGDIOBJ old_pen = SelectObject(item->hdc, pen);
		HGDIOBJ old_brush = SelectObject(item->hdc, selectbrush);

		//If you want rounded button, then use this, otherwise use FillRect().
		

		RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);
		int right = item->rc.right, left = item->rc.left, top = item->rc.top, bottom = item->rc.bottom;
		if (img != nullptr)
		{
			//LOGFONT lf;
			//memset(&lf, 0, sizeof(LOGFONT));
			//lstrcpy(lf.lfFaceName, L"Times new roman"); // Имя шрифта.
			//lf.lfWeight = FW_HEAVY;
			//lf.lfHeight = FONTSIZE; // По высоте.
			//HFONT hFont = CreateFontIndirect(&lf);
			//SelectObject(item->hdc, hFont);
			//SetBkMode(item->hdc, TRANSPARENT);
			//TextOut(item->hdc, 0, 10, L"Убрать", 5);
			Gdiplus::Graphics graph(item->hdc);
			graph.DrawImage(img, left, top, right, bottom);
		}
		//Clean up
		SelectObject(item->hdc, old_pen);
		SelectObject(item->hdc, old_brush);
		DeleteObject(pen);

		//Now, I don't want to do anything else myself (draw text) so I use this value for return:
		return;
		//Let's say I wanted to draw text and stuff, then I would have to do it before return with
		//DrawText() or other function and return CDRF_SKIPDEFAULT
	}
	else
	{
		if (item->uItemState & CDIS_HOT) //Our mouse is over the button
		{
			//Select our color when the mouse hovers our button
			if (hotbrush == NULL)
				if (Brush_type == GRADIENT)
					hotbrush = CreateGradientBrush_in_horizont(GetGradColor_for_btn(HOTBRUSH, LEFT), GetGradColor_for_btn(HOTBRUSH, RIGHT), item);
				else
					hotbrush = CreateSolidBrush(GetSolidColor_for_btn(HOTBRUSH));
			HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

			HGDIOBJ old_pen = SelectObject(item->hdc, pen);
			HGDIOBJ old_brush = SelectObject(item->hdc, hotbrush);

			RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

			int right = item->rc.right, left = item->rc.left, top = item->rc.top, bottom = item->rc.bottom;
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

		//Select our color when our button is doing nothing
		if (defaultbrush == NULL)
			if (Brush_type == GRADIENT)
				defaultbrush = CreateGradientBrush_in_horizont(GetGradColor_for_btn(DEFAULTBRUSH, LEFT), GetGradColor_for_btn(DEFAULTBRUSH, RIGHT), item);
			else
				defaultbrush = CreateSolidBrush(GetSolidColor_for_btn(DEFAULTBRUSH));
		HPEN pen = CreatePen(PS_INSIDEFRAME, 0, RGB(0, 0, 0));

		HGDIOBJ old_pen = SelectObject(item->hdc, pen);
		HGDIOBJ old_brush = SelectObject(item->hdc, defaultbrush);

		RoundRect(item->hdc, item->rc.left, item->rc.top, item->rc.right, item->rc.bottom, 5, 5);

		int right = item->rc.right, left = item->rc.left, top = item->rc.top, bottom = item->rc.bottom;
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


void CustomBTN_SET_IMAGE(HWND& hwnd, LPNMHDR some_item, Gdiplus::Bitmap** img)
{
	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	Gdiplus::Graphics* graph = new (Gdiplus::Graphics)(item->hdc);
	int right = item->rc.right, left = item->rc.left, top = item->rc.top, bottom = item->rc.bottom;
	Gdiplus::Bitmap* buffer = new (Gdiplus::Bitmap)(right, bottom);
	Gdiplus::Graphics* myGraphics = new (Gdiplus::Graphics)(buffer);
	if (img != nullptr)
	{

		if (item->uItemState & CDIS_SELECTED)
			myGraphics->DrawImage(img[0], left, top, right, bottom);
		else
			if (item->uItemState & CDIS_HOT)
				myGraphics->DrawImage(img[1], left, top, right, bottom);
			else
				myGraphics->DrawImage(img[2], left, top, right, bottom);
	}

	Gdiplus::CachedBitmap  cBitmap(buffer, graph);
	graph->DrawCachedBitmap(&cBitmap, 0, 0);
	delete buffer;
	delete graph;
	delete myGraphics;
	return;
}



