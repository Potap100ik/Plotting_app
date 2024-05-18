#pragma once
#pragma warning (disable : 4996)
#include <iostream>
//#include <stdio.h>
#include <cmath>
#include <string.h>
#include <Windows.h>
#include "char_change.h"
//#define DEBUG
const double M_E = 2.71828182845904523;
const double M_PI = 3.1415926535897932;


using namespace std;

enum FUNC { EXP, ABS, LOG, LOG10, POW, SQRT, SIN, COS, TAN, BRAKET, E, PI, XX };

long double Function_String_to_Double(char* str, double* x, int y = 1);
int Index_of_smth(char* str);
int Index_of_smth(char* str, char ch1, char ch2);
int Index_of_smth(char* str, char ch1, char ch2, char ch3);
int Index_of_smth(char* str, char ch1, char ch2, char ch3, char ch4);
char* StrCut(char* str, double* x, int y, FUNC en);
char* StrCut(char* str, double* x, int y, int const index, FUNC en);
void StrCut(char*& str1, char*& str2, int const& index2, int const& size2);

