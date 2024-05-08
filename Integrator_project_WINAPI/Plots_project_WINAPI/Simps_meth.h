#pragma once
#include <limits.h>

double Simps_method(double a, double b, char* str, long double (*Function_Count)(char*, double*, int))
{
	long double r{};
	int flags;
	if (b < a) {
		//std::cout << "b < a - непорядок" << std::endl;
		return 0;
	}
	else if (b == a) {
		//std::cout << "b = a - непорядок" << std::endl;
		return 0;
	}
	double x = (a + b) / 2;
	try {
		r = (b - a) / 6 * (Function_Count(str, &a, 1) + 4 * Function_Count(str, &x, 1) + Function_Count(str, &b, 1));
	}
	catch (double err) {
		if (isnan(err) || isinf(err))
			throw(err);
	}
	return r;
}
double Integrator(double a, double b, double h, char* str, long double (*Function_Count)(char*, double*, int), double(*Method)(double, double, char*, long double (*Function_Count)(char*, double*, int)))
{
	long double sum = 0;
	int flags;
	for (double i = a; i <= b; i += h)//проходим все дискретности от a до b с шагом h
	{
		try {
			sum += Method(i, i + h, str, Function_Count);
		}
		catch (double err)
		{
			if (isnan(err) || isinf(err))
				throw(err);
		}

	}
	int ii = (b - a) / h;
	try {
		sum += Method(ii * h + a, b, str, Function_Count);//если b-a не делится без остатка на h - надо вычислить последний кусочек
	}
	catch (double err)
	{
		if (isnan(err) || isinf(err))
			throw(err);
	}
	return sum;
}
