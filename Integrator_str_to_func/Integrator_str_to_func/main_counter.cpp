//#include <iostream>
//#include <stdio.h>
#include "..\\..\\Integrator_project_WINAPI\\Plots_project_WINAPI\\Str_to_double\\str_to_double.h"
#include "..\\..\\Integrator_project_WINAPI\\Plots_project_WINAPI\\Str_to_double\\char_change.h"
//#include "X_change.h"
using namespace std;

int main()
{
	//������ ������ ��-�� ������������� ������������ �����
	setlocale(LC_ALL, "RUS");


	char* str = new char[100];

		double x = 4.63;


		long double c;
		
		while (true)
		{
			cout << "������� ������ ��� �� �����������:" << endl;
			cin >> str;
			cout << endl;
			try {
				c = Function_String_to_Double(str, &x);
			}
			catch (double error)
			//catch (char * str1)
			{
				//c = atof(str1);
				//cout << str << " = " << c <<"     �������� �����" << endl;
				c = error;
				cout <<" c = " << c << "   �������� �����" << endl;
				if (isnan(c))cout << "������������ isnan" << endl;
				if (isinf(c))cout << "������������ isinf" << endl;

			}
			cout << str << " = " << c << endl;
		}







	system("pause");

	return 0;
}