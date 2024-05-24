#pragma once
#include "STD/stdafx.h"
#define MAX_LOADSTRING 100
const int WM_DRAW_MAIN_PLOT = WM_USER;
const int WM_HOME_BTN_CLICKED = WM_USER + 1;
const int WM_CLEAR_PLOT = WM_USER + 2;
const int WM_RESIZE_PLOT = WM_USER + 3;

/////////////////////////////////////////////////////////
//КОНСТАНТЫ ДЛЯ ПРОРИСОВКИ ОКНА ГРАФИКА И ИНТЕГРАЛА
const int POINTS_TO_ONE_PICEL = 10;//количество рассчитываемых значений графика на 1 пиксель экрана
const int SYSTEMMETRICS = GetSystemMetrics(SM_CXSCREEN) * POINTS_TO_ONE_PICEL;
const int TOCHNOST_FOR_TANGENS_INF = 100;
const int COUNT_FOR_ZOOM_SQARES_TO_REDRAW = 3 - 1;//при сравнении исп. > поэтому число будет расно двум если вычесть единицу
const int ZOOM_SMOOTH_COUNT = 120;//ОТ НУЛЯ ДО 120 ПРИ РАБОТЕ КОЛЕСИКОМ МЫШКИ
// КОНСТАНТЫ ДЛА СЕТКИ ИНТЕГРАЛА
const int BASE_H_SETKA_INT = 8;//размер в пикселях ширины одного маленького сеточного квадрата
const int MIN_H_SETKA_INT = 2;
const int MAX_H_SETKA_INT = 16;
const int KOL_OF_SETKA_SQARES5 = 5;
//КОНСТАНТЫ ДЛЯ СЕТКИ ГРАФИКА
const int BASE_H_SETKA = 10;//размер в пикселях ширины одного маленького сеточного квадрата
const int MIN_H_SETKA = 2;
const int MAX_H_SETKA = 20;
const int BASE_U5_SETKA = 2;