#pragma once
#include <cmath>
double Simps_method(double a, double b, char* str, double (*Function_Count)(char*, double*, int, bool));
double Integrator(double a, double b, double h, char* str, double (*Function_Count)(char*, double*, int, bool), double(*Method)(double, double, char*, double (*Function_Count)(char*, double*, int, bool)));


