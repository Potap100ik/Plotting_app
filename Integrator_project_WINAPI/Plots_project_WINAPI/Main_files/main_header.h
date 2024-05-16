#pragma once
#include "stdafx.h"
#include "Standard.h"

//оконные создания
LPVOID CreateControls(HWND hWnd);
ATOM MyRegisterChildClass();
//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
//исполнительные функции
void Plotting_edges_upd(int);
double Setka_unit(double get_value);//придвигает кратность юнита сетки графика к 1,2 или 5
LPSTR Wide_into_Ascii(LPCWSTR sw);
void StructInit();
void CorrectSetkaPos(int);
void MousePos(BOOL, int, int);
void DrowSetka(HDC hdc);
void DrowCounts(HDC hdc);
void DrowGraphSmooth(HDC hdc);
void DrowGraph(HDC hdc);
void FirstPlotting();
void RedrawPlot();


//TCHAR WidMain_NAME[MAX_LOADSTRING] = _T("MainWindow");
//HINSTANCE hInst;


//оконные процедуры
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
//char* char_to_swap(char* str, double x, char chh);
//char* char_to_clear(char* str, char chh);
//char* char_to_delete(char* str, int index);

