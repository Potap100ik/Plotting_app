#pragma once
#include "type.h"
#include "STD/stdafx.h"


//оконные процедуры

//исполнительные функции
void Plotting_edges_upd(int, Wnd_Plot_struct*,int x = 0, int y = 0);
double Setka_UNIT_CHANGE(double get_value);//придвигает кратность юнита сетки графика к 1,2 или 5
LPSTR Wide_into_Ascii(LPCWSTR sw);
void SetkaStructUpdate(Wnd_Plot_struct* Wnd_Plot, int new_h_setka, double new_u5_setka);
void StructPlotInit(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot);
void StructIntegralInit(Wnd_Plot_struct* Wnd_Plot, Integral_struct& Myintegr);
void Wide_for_vector_upd(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot);

void CorrectSetkaPos(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot, int h_min, int h_max, int h_baza, bool na_skoruyu_ruku = true);
void MousePos(BOOL, int, int, SMouseMove&);
int FirstPlotting(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot);
void RedrawPlot(Wnd_Plot_struct* Wnd_Plot, Ploting_struct& Myplot);
double FillIntegralVector(Integral_struct& Myintegr, Wnd_Plot_struct* Wnd_Plot, double& correct_x, double& correct_y);
int CheckValues_of_edit(double A, double B, double H, HWND hWnd, HWND hWndEdit_Integral, LPSTR text_);

//оконные процедуры
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
//char* char_to_swap(char* str, double x, char chh);
//char* char_to_clear(char* str, char chh);
//char* char_to_delete(char* str, int index);

