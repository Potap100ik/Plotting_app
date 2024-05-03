#include "Header.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	double (*func)(double);
	double a = 0;
	double b = 1;
	double h;
	int t;
	func = func1;
	std::cout << "Введите точность t: ";
	std::cin >> t;
	h = (b - a) / (pow(10, t)+2);
	std::cout << "Ответ: " << Integrator(a, b, h, func, Simps_method) << std::endl << std::endl;


	return 0;
}