#pragma once
#include "STD/stdafx.h"
#define MAX_LOADSTRING 100
const int WM_DRAW_MAIN_PLOT = WM_USER;
const int WM_HOME_BTN_CLICKED = WM_USER + 1;
const int WM_CLEAR_PLOT = WM_USER + 2;
const int WM_RESIZE_PLOT = WM_USER + 3;

const int POINTS_TO_ONE_PICEL = 10;//количество рассчитываемых значений графика на 1 пиксель экрана
const int SYSTEMMETRICS = GetSystemMetrics(SM_CXSCREEN) * POINTS_TO_ONE_PICEL;