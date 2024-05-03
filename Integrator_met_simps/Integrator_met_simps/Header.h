#pragma once
#include <cmath>
#include <iostream>

double func1(double x)
{
	return log(x);
}

double func2(double x)
{
	return -x / log(x) + 1 / x;
}
double func3(double x)
{
	return pow(x, 2) * pow(sin(x), 3);
}
double Simps_method(double a, double b, double (*F)(double))
{
	
	if (b < a) {
		std::cout << "b < a - непорядок" << std::endl;
		return 0;
	}
	else if (b == a) {
		std::cout << "b = a - непорядок" << std::endl;
		return 0;
	}
	double r = (b - a) / 6 * (F(a) + 4 * F((a + b) / 2) + F(b));
	if (isnan(r) || isinf(r)) return 0;
	return r;
}

double Integrator(double a, double b, double h,double (*Func)(double), double(*Method)(double, double, double (*F)(double)))
{
	double sum = 0;
	for (double i = a; i <= b; i += h)//проходим все дискретности от a до b с шагом h
	{
		sum += Method(i, i + h, Func);
	}
	int ii = (b - a) / h;
	sum += Method(ii*h+a, b, Func);//если b-a не делится без остатка на h - надо вычислить последний кусочек
	return sum;
}
