//#include <iostream>
//#include <stdio.h>
#include "..\\..\\Integrator_project_WINAPI\\Plots_project_WINAPI\\Str_to_double\\str_to_double.h"
#include "..\\..\\Integrator_project_WINAPI\\Plots_project_WINAPI\\Str_to_double\\char_change.h"
#include "..\\..\\Integrator_project_WINAPI\\Plots_project_WINAPI\\Main_files\\type.h"
//#include "X_change.h"
#include "vld.h"
#pragma comment(lib, "vld.lib")
using namespace std;

int main()
{
	//������ ������ ��-�� ������������� ������������ �����
	setlocale(LC_ALL, "RUS");


	char* str = (char*)malloc(MAX_LOADSTRING);

		double x = 4.63;


		long double c = 1;
		
		while (strcmp(str, "000")!=0)
		{
			cout << "������� ������ ��� �� �����������:" << endl;
			cin >> str;
			cout << endl;
			try {
				c = Function_String_to_Double(str, &x, 1, false);
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
			catch (ERROR_STRUCT err_msg)
			{
				cout << "������ ERROR_STRUCT: "<<err_msg.char_err << endl;
			}
			cout << str << " = " << c << endl;
		}






	free(str);
	system("pause");

	return 0;
}