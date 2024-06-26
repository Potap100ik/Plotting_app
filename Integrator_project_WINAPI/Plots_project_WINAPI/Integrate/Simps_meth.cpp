#include "Simps_meth.h"
#include "../Main_files/type.h"
double Simps_method(double a, double b, char* str, double (*Function_Count)(char*, double*, int, bool))
{
	double r{};
	int flags;
	if (b < a) {
		//std::cout << "b < a - ���������" << std::endl;
		return 0;
	}
	else if (b == a) {
		//std::cout << "b = a - ���������" << std::endl;
		return 0;
	}
	double x = (a + b) / 2;
	try {
		r = (b - a) / 6 * (Function_Count(str, &a, 1, false) + 4 * Function_Count(str, &x, 1, false) + Function_Count(str, &b, 1, false));
	}
	catch (double err) {
		//if (isnan(err) || isinf(err))
			//throw(err);
		throw(a);
	}
	catch (ERROR_STRUCT err_msg)
	{
		ERROR_STRUCT nani = err_msg;
		throw(nani);
	}
	return r;
}
double Integrator(double a, double b, double h, char* str, double (*Function_Count)(char*, double*, int, bool), double(*Method)(double, double, char*, double (*Function_Count)(char*, double*, int, bool)))
{
	double sum = 0;
	int flags;
	for (double i = a; i <= b; i += h)//�������� ��� ������������ �� a �� b � ����� h
	{
		try {
			sum += Method(i, i + h, str, Function_Count);
		}
		catch (double err)
		{
			//if (isnan(err) || isinf(err))
			//throw(err);
			throw(i);
		}
		catch (ERROR_STRUCT err_msg)
		{
			ERROR_STRUCT nani = err_msg;
			throw(nani);
		}
	}
	int ii = (b - a) / h;
	try {
		sum += Method(ii * h + a, b, str, Function_Count);//���� b-a �� ������� ��� ������� �� h - ���� ��������� ��������� �������
	}
	catch (double err)
	{
		//if (isnan(err) || isinf(err))
		//	throw(err);
		throw(b);
	}
	catch (ERROR_STRUCT err_msg)
	{
		ERROR_STRUCT nani = err_msg;
		throw(nani);
	}
	return sum;
}
