#pragma once
#include "Main_files/STD/stdafx.h"
#include "Main_files/type.h"


void DrowSetka(HDC, Wnd_Plot_struct*);
void DrowCounts(HDC, Wnd_Plot_struct*, HFONT*);
void DrowGraphSmooth(HDC dc, Wnd_Plot_struct*, Ploting_struct&, Gdiplus::Pen* Pen_for_plot);
void DrowGraph(HDC, Wnd_Plot_struct*, Ploting_struct&);