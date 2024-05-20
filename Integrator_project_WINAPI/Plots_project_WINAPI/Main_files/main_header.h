#pragma once
#include "lib_struct.h"
#include "STD/stdafx.h"
#include "STD/Standard.h"

//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
//исполнительные функции
void Plotting_edges_upd(int, MyWnd_Plot*);
double Setka_UNIT_CHANGE(double get_value);//придвигает кратность юнита сетки графика к 1,2 или 5
LPSTR Wide_into_Ascii(LPCWSTR sw);
void SetkaStructUpdate(MyWnd_Plot* Wnd_Plot, int new_h_setka, double new_u5_setka);
void StructPlotInit(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot);
void StructIntegralInit(MyWnd_Plot* Wnd_Plot, Integral_struct& Myintegr);
void Wide_for_vector_upd(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot);

void CorrectSetkaPos(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot, int h_min, int h_max, int h_baza);
void MousePos(BOOL, int, int, MouseMove&);
void FirstPlotting(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot);
void RedrawPlot(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot);
double FillIntegralVector(Integral_struct& Myintegr, MyWnd_Plot* Wnd_Plot, double& correct_x, double& correct_y);
int CheckValues_of_edit(double A, double B, double H, HWND hWnd, HWND hWndEdit_Integral, LPSTR text_);

//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
//char* char_to_swap(char* str, double x, char chh);
//char* char_to_clear(char* str, char chh);
//char* char_to_delete(char* str, int index);

