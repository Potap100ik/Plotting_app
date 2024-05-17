#pragma once
#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"
using namespace Gdiplus;

void DrowSetka(HDC, Wnd_Plot_struct*);
void DrowCounts(HDC, Wnd_Plot_struct*);
void DrowGraphSmooth(HDC dc, Wnd_Plot_struct*, Ploting_struct&, Pen* Pen_for_plot);
void DrowGraph(HDC, Wnd_Plot_struct*, Ploting_struct&);