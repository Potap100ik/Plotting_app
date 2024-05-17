#pragma once
#include "lib_struct.h"
#include "STD/stdafx.h"
#include "STD/Standard.h"

//оконные создания
LPVOID CreateControls(HWND hWnd);
ATOM MyRegisterChildClass();
//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
//исполнительные функции
void Plotting_edges_upd(int, MyWnd_Plot*);
double Setka_unit(double get_value);//придвигает кратность юнита сетки графика к 1,2 или 5
LPSTR Wide_into_Ascii(LPCWSTR sw);
void StructInit(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot, Integral_struct& Myintegr);
void StructInit(MyWnd_Plot* Wnd_Integral, Integral_struct& Myintegr);
void CorrectSetkaPos(int a, MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot, int h_min = 3, int h_max = 20, int h_baza = 10);
void MousePos(BOOL, int, int, MyWnd_Plot*, MouseMove&);
void FirstPlotting(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot);
void RedrawPlot(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot);
double FillIntegralVector(Integral_struct& Myintegr, MyWnd_Plot*, double &);
int CheckValues_of_edit(double A, double B, double H, HWND hWnd, HWND hWndEdit_Integral, MyWnd_Plot* Wnd_Plot);
void Text_Init(LPSTR text_);
//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
//char* char_to_swap(char* str, double x, char chh);
//char* char_to_clear(char* str, char chh);
//char* char_to_delete(char* str, int index);

