#pragma once
#include <cmath>
double Simps_method(double a, double b, char* str, long double (*Function_Count)(char*, double*, int));
double Integrator(double a, double b, double h, char* str, long double (*Function_Count)(char*, double*, int), double(*Method)(double, double, char*, long double (*Function_Count)(char*, double*, int)));