//#include <iostream>
//#include <stdio.h>
#include "main_counter.h"
//#include "X_change.h"
using namespace std;

int main()
{
	//������ ������ ��-�� ������������� ������������ �����
	setlocale(LC_ALL, "RUS");


	char* str = new char[100];

		double x = 4.63;


		double c;
		
		while (true)
		{
			cout << "������� ������ ��� �� �����������:" << endl;
			cin >> str;
			cout << endl;
			try {
				c = Function_Count(char_to_swap(str, x, 'x'),&x);
			}
			catch (char* str1)
			{
				c = atof(str1);
				cout << str << " = " << c <<"     �������� �����" << endl;
				if (isnan(c))cout << "������������ isnan" << endl;
				if (isinf(c))cout << "������������ isinf" << endl;

			}
			cout << str << " = " << c << endl;
		}







	system("pause");

	return 0;
}