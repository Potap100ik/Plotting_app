#pragma once

double Simps_method(double a, double b, char* str, double (*Function_Count)(char*, double*, int))
{
	double r{};
	if (b < a) {
		//std::cout << "b < a - непорядок" << std::endl;
		return 0;
	}
	else if (b == a) {
		//std::cout << "b = a - непорядок" << std::endl;
		return 0;
	}
	double x = (a + b) / 2;
	try	{
		r = (b - a) / 6 * (Function_Count(str, &a, 1) + 4 * Function_Count(str, &x, 1) + Function_Count(str, &b, 1));
	}
	catch (char*) {

		if (isnan(r) || isinf(r)) return 0;
	}
	return r;
}
double Integrator(double a, double b, double h, char* str, double (*Function_Count)(char*, double*, int), double(*Method)(double, double, char*, double (*Function_Count)(char*, double*, int)))
{
	double sum = 0;
	for (double i = a; i <= b; i += h)//проходим все дискретности от a до b с шагом h
	{
		sum += Method(i, i + h, str, Function_Count);
	}
	int ii = (b - a) / h;
	sum += Method(ii * h + a, b, str, Function_Count);//если b-a не делится без остатка на h - надо вычислить последний кусочек
	return sum;
}
