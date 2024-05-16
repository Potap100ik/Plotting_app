#pragma once
#include "lib_struct.h"
#include "STD/stdafx.h"
#include "STD/Standard.h"

//������� ��������
LPVOID CreateControls(HWND hWnd);
ATOM MyRegisterChildClass();
//������� ���������
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
//�������������� �������
void Plotting_edges_upd(int, MyWnd_Plot*, Ploting_struct&);
double Setka_unit(double get_value);//���������� ��������� ����� ����� ������� � 1,2 ��� 5
LPSTR Wide_into_Ascii(LPCWSTR sw);
void StructInit(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot, Integral_struct Myintegr);
void CorrectSetkaPos(int, MyWnd_Plot*, Ploting_struct&);
void MousePos(BOOL, int, int, MyWnd_Plot*);
void FirstPlotting(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot);
void RedrawPlot(MyWnd_Plot* Wnd_Plot, Ploting_struct& Myplot);


//������� ���������
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM	lParam);
LRESULT CALLBACK Win_Plot(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//
//char* char_to_swap(char* str, double x, char chh);
//char* char_to_clear(char* str, char chh);
//char* char_to_delete(char* str, int index);

