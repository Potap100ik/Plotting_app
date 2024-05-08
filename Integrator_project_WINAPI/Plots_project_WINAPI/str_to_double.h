#pragma once
#include <iostream>
//#include <stdio.h>
#include <cmath>
#include <string.h>
#include "char_change.h"
#define DEBUG
const double M_E = 2.71828182845904523;
const double M_PI = 3.1415926535897932;

using namespace std;

enum FUNC { EXP, ABS, LOG, LOG10, POW, SQRT, SIN, COS, TAN, BRAKET, E, PI, XX };

long double Function_String_to_Double(char* str, double* x, int y);
int Index_of_smth(char* str);
int Index_of_smth(char* str, char ch1, char ch2);
char* StrCut(char* str, double* x, int y, FUNC en);
char* StrCut(char* str, double* x, int y, int const index, FUNC en);
void StrCut(char*& str1, char*& str2, int const& index2, int const& size2);



void StrCut(char*& str1, char*& str2, int const& index2, int const& size2)
{
	strncpy(str1, str2, index2);//������ 1 - ������ ��� ��������� �� ����� * �� ����� +-
	str1[index2] = '\0';
	memmove(str2, str2 + index2 + 1, size2 - index2 + 1);//�������� ������ 1 �� str � �������� ������� � str2 � ����������� ����� +-
}
char* StrCut(char* str, double* x, int y, int const index, FUNC en) {//����������� � ���������� � ������� - ���� ������, �������� ������, ����� ������, ����� ������ �� �����

	char* str1 = new char[100],
		* str2 = new char[100];
	strcpy(str2, str);
	str2[index] = '\0';
	switch (en)
	{
	case EXP:
		sprintf(str1, "%lf", exp(Function_String_to_Double(str2 + 1, x, y)));
		break;
	case ABS:
		sprintf(str1, "%lf", abs(Function_String_to_Double(str2 + 1, x, y)));
		break;
	case LOG:
		sprintf(str1, "%lf", log(Function_String_to_Double(str2 + 1, x, y)));
		break;
	case LOG10:
		sprintf(str1, "%lf", log10(Function_String_to_Double(str2 + 1, x, y)));
		break;
	case POW:
	{
		int index2 = strcspn(str, ";");
		strcpy(str1, str);
		str1[index2] = '\0';
		sprintf(str1, "%lf", pow(Function_String_to_Double(str1 + 1, x, y), Function_String_to_Double(str2 + index2 + 1, x, y)));
	}
	break;
	case SQRT:
		sprintf(str1, "%lf", sqrt(Function_String_to_Double(str2 + 1, x, y)));
		break;
	case SIN:
		sprintf(str1, "%lf", sin(Function_String_to_Double(str2 + 1, x, y)));
		break;
	case COS:
		sprintf(str1, "%lf", cos(Function_String_to_Double(str2 + 1, x, y)));
		break;
	case TAN:
		sprintf(str1, "%lf", tan(Function_String_to_Double(str2 + 1, x, y)));
		break;
	case BRAKET:
		sprintf(str1, "%lf", Function_String_to_Double(str2 + 1, x, y));
		break;
	default:
		cout << "ERROR 6 - ����������� ��������������� �������� - �������� ������� � ������� ��� �� �������" << endl;
		return 0;
	}
	//sprintf(str1, "%lf", Function_Count(str2 + 1, x, y));//����������� ��������������� ��������� 1 � ������������ ����� � �������� � str1
	bool fl;
	fl = (strncmp(str1, "+nan(ind)", 4) == 0 || strncmp(str1, "-nan(ind)", 4) == 0 || strncmp(str1, "nan", 3) == 0 || strcmp(str1, "nan)") == 0 || strcmp(str1, "-inf") == 0 || strcmp(str1, "+inf") == 0 || strcmp(str1, "inf") == 0);
	if (fl)
	{
		double nani = NAN;
		throw(nani);
		//throw(str1);
	}
	memcpy(str1 + strlen(str1), str + index, strlen(str) - index + 1);
	//str1 + strlen(str1)		- ������ �������� '\0', ���������� �� �������� ������� 
	//str + index				- ������ ������ ������ �������������� ������
	//strlen(str) - index = 1	- ���������� �������������� ������, ������� '\0'
	delete[] str2;
	return str1;
}
char* StrCut(char* str, double* x, int y, FUNC en) {//����������� � ���������� � ������� - ���� ������, �������� ������, ����� ������, ����� ������ �� �����
	char* str1 = new char[100];
	switch (en)
	{
	case E:
		sprintf(str1, "%lf", M_E);
		break;
	case PI:
		sprintf(str1, "%lf", M_PI);
		break;
	case XX:
		sprintf(str1, "%lf", *x);
		break;
	default:
		cout << "ERROR 6 - ����������� ��������������� �������� - �������� ������� � ������� ��� �� �������" << endl;
		return 0;
	}
	strcat(str1, str);
	return str1;
}
int Index_of_smth(char* str, char ch1, char ch2)
{
	int count = 0;
	char ch = str[0];
	int index2 = 0;
	int i = 0;//������ ��� ������� ���� - ��������
	while (ch != '\0')
	{
		ch = str[i];

		if (ch == ch1 || ch == ch2)//������ ������ ������ ���� +- ��� */
		{
			if (count == 0)//� ����� ����������
			{
				index2 = i;//������� ������ ��������� �����
				ch = '\0';//������ �� �����
			}
		}
		else if (ch == '(')//��������� ������ ����������
		{
			count++;
		}
		else if (ch == ')')//��������� ������ ����������
		{
			count--;
		}
		i++;

	}
	return index2;
}
int Index_of_smth(char* str)
{
	int count = 0;
	char ch = str[0];
	int index = 0;//��� �������� �� ������������� ����������� ��������
	int i = 0;//������ ��� ������� ���� - ��������
	while (ch != '\0')
	{
		ch = str[i];
		if (ch == '(')
		{
			count++;
		}
		else if (ch == ')')
		{
			count--;
			if (count == 0)
			{
				index = i;
				ch = '\0';
			}
		}
		i++;

	}
	return index;
}


// y - ���� ������� ����� � ������
long double Function_String_to_Double(char* str, double* x, int y = 1)
{


	if (strcspn(str, "1234567890") == 0)//���� ������ ���� ������ - �����
	{
		int size = strlen(str);
		int index = strcspn(str, "*+-/");
		if (size == index) {//���� � ������ �� ������ ���� ���������, �������, �������� ��� ���������
			return y * atof(str);//������ ������ ������� �� ���� � �������� ������ - �� ����� ���������� ������������ �����
		}
		else//�� ����� �����-�� ����� - ���� ��������� ������ � ����������� ���������� ����������
		{
			char* str1 = new char[100];
			char* str2 = new char[100];

			strncpy(str1, str, index);//������ 1 - ��� �����
			str1[index] = '\0';
			memcpy(str2, str + index + 1, size - index + 1);//�������� ������ 1 �� str � �������� ������� � str2 �� ����������� ����� *-+/


			switch (str[index])
			{
			case '*':
			{
				int size2 = strlen(str2); //�������� ����� ������ 2

				//���� ����� +  �  -
				//���� ����� ���� � ����� ����������, � ����� ������ �� �����


				int index2 = Index_of_smth(str2, '+', '-');
				if (index2 != 0) {//���� � ������ 2 ������� �����  �������� ��� ��������� - ���� ���������� ���������� ��� �������������� ��������

					double d = y * atof(str1);
					char ch = str2[index2];//��������� ��������� ����
					StrCut(str1, str2, index2, size2);//�������� ������ 1 �� str2 � �������� ������� � str2 � ����������� ����� */

					switch (ch)
					{
					case '+': return d * Function_String_to_Double(str1, x) + Function_String_to_Double(str2, x);
					case '-': return d * Function_String_to_Double(str1, x) - Function_String_to_Double(str2, x);
					}
					//Function_Count(str1, x) - ��������� 1, �� ������� ���� �������� ��� ��������� d ����� ��� ��� ���������� ��� �������� ��������� 2
					//Function_Count(str2, x) - ��������� 2, ������� ������������� ��������
				}
				else
				{
					return y * atof(str1) * Function_String_to_Double(str2, x);
				}
			}
			case '/':
			{
				int size2 = strlen(str2); //�������� ����� ������ 2
				int index2 = Index_of_smth(str2, '+', '-');

				if (index2 != 0) {//���� � ������ 2 ������� �����  �������� ��� ��������� - ���� ���������� ���������� ��� �������������� ��������

					double d = y * atof(str1);
					char ch = str2[index2];//��������� ��������� ����
					StrCut(str1, str2, index2, size2);//�������� ������ 1 �� str2 � �������� ������� � str2 � ����������� ����� */

					switch (ch)
					{
					case '+': return d / Function_String_to_Double(str1, x) + Function_String_to_Double(str2, x);
					case '-': return d / Function_String_to_Double(str1, x) - Function_String_to_Double(str2, x);
					}
					//Function_Count(str1, x) - ��������� 1, �� ������� ���� �������� ��� ��������� d ����� ��� ��� ���������� ��� �������� ��������� 2
					//Function_Count(str2, x) - ��������� 2, ������� ������������� ��������
				}
				else
				{
					return y * atof(str1) / Function_String_to_Double(str2, x);
				}
			}
			case '+':
			{
				int size2 = strlen(str2); //�������� ����� ������ 2
				int index2 = Index_of_smth(str2, '*', '/');
				if (index2 != 0) {//���� � ������ 2 ������� �����  ��������� � ������� - ���� ���������� ���������� ��� �������������� ��������

					double d = y * atof(str1);
					char ch = str2[index2];//��������� ��������� ����
					StrCut(str1, str2, index2, size2); //�������� ������ 1 �� str2 � �������� ������� � str2 � ����������� ����� +-

					switch (ch)
					{
					case '*': return d + (Function_String_to_Double(str1, x) * Function_String_to_Double(str2, x));
					case '/': return d + (Function_String_to_Double(str1, x) / Function_String_to_Double(str2, x));
					}
					//Function_Count(str1) - ��������� 1, �� ������� ���� �������� ��� ��������� d ����� ��� ��� ���������� ��� �������� ��������� 2
					//Function_Count(str2) - ��������� 2, ������� ������������� ��������
				}

				else
				{
					return y * atof(str1) + Function_String_to_Double(str2, x);
				}
			}
			case '-':
			{
				int size2 = strlen(str2); //�������� ����� ������ 2
				int index2 = Index_of_smth(str2, '*', '/');
				if (index2 != 0) {//���� � ������ 2 ������� �����  ��������� � ������� - ���� ���������� ���������� ��� �������������� ��������

					double d = y * atof(str1);
					char ch = str2[index2];//��������� ��������� ����
					StrCut(str1, str2, index2, size2); //�������� ������ 1 �� str2 � �������� ������� � str2 � ����������� ����� +-

					switch (ch)
					{
					case '*': return d - (Function_String_to_Double(str1, x) * Function_String_to_Double(str2, x));
					case '/': return d - (Function_String_to_Double(str1, x) / Function_String_to_Double(str2, x));
					}
					//Function_Count(str1) - ��������� 1, �� ������� ���� �������� ��� ��������� d ����� ��� ��� ���������� ��� �������� ��������� 2
					//Function_Count(str2) - ��������� 2, ������� ������������� ��������
				}

				else
				{
					return y * atof(str1) - Function_String_to_Double(str2, x);
				}
			}
			default:
			{
				cout << "ERROR 1 - ������ �������������� ����: " << str[index] << " ����� �����" << str1 << endl << "�������? (1/0)" << endl;
				int u = 1;
#ifdef DEBUG
				u = 0;
#endif //DEBUG
				if (u) {
					char_to_clear(str, str[index]);
					return Function_String_to_Double(str, x, y);
				}

				else {
					cout << "��� ��� ���" << endl;
					return Function_String_to_Double(str + 1, x, y);

				}
			}


			}
		}
	}
	else if (str[0] == '-')
	{
		return (-1)*Function_String_to_Double(str + 1, x);
	}
	else if (str[0] == 'x') {


		return Function_String_to_Double(StrCut(str + 1, x, y, XX), x, y);
	}
	else if (str[0] == '(')
	{

		int index = Index_of_smth(str);
		if (strlen(str) == index + 1) {//����������� �������� ������ ��������� ���� ��������� � ������ - ����� ��� �� � ����������, �� ��� ������
			str[index] = '\0';
			return Function_String_to_Double(str + 1, x, y);
		}
		else if (index == 1)
		{
			cout << "ERROR 4 - ����������� ��������� ������ ������, ������� ������" << endl << "�������? (1/0)" << endl;
			int u = 1;
#ifdef DEBUG
			u = 0;
#endif //DEBUG
			if (u) {
				char_to_delete(str, 0);
				char_to_delete(str, 1);
				return Function_String_to_Double(str, x, y);
			}

			else {
				cout << "��� ��� ���" << endl;
				return Function_String_to_Double(str + 2, x, y);

			};
			return Function_String_to_Double(str + 2, x, y);
		}
		else if (index == 0)
		{
			cout << "ERROR 3 - ������ �������������� ���� � ������ ������ � ���� �������� �������� (" << endl << "�������?(1/0)" << endl;
			int u = 1;
#ifdef DEBUG
			u = 0;
#endif //DEBUG
			if (u) {
				char_to_delete(str, index);
				return Function_String_to_Double(str, x, y);
			}
			else {
				return Function_String_to_Double(str + 1, x, y);
			}
		}
		else//����������� �������� ��������� ���������� - ������ ���������� ��������� �� �������� � �������� ������, ������� � �������
		{
			return Function_String_to_Double(StrCut(str, x, y, index, BRAKET), x, y);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////0 ��� 1
	else if (str[0] == '\0') { cout << "ERROR 0 - ������� ������ ������" << endl; return 0; }
	else if (strcspn(str, "ealpsct") == 0)
	{
		switch (str[0])
		{
		case'e':
			if (strncmp(str, "exp(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				return Function_String_to_Double(StrCut(str + 3/*��c������� exp*/, x, y, index, EXP), x, y);
			}
			else
			{
				return Function_String_to_Double(StrCut(str + 1, x, y, E), x, y);//�� ����� ����������
			}
			break;
		case'a':
			if (strncmp(str, "abs(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				return Function_String_to_Double(StrCut(str + 3, x, y, index, ABS), x, y);
			}
			break;
		case'l':
			if (strncmp(str, "log(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				return Function_String_to_Double(StrCut(str + 3, x, y, index, LOG), x, y);
			}
			else if (strncmp(str, "ln(", 3) == 0)
			{
				int index = Index_of_smth(str + 2);
				return Function_String_to_Double(StrCut(str + 2, x, y, index, LOG), x, y);
			}
			else if (strncmp(str, "log10(", 6) == 0)
			{
				int index = Index_of_smth(str + 5);
				return Function_String_to_Double(StrCut(str + 5, x, y, index, LOG10), x, y);
			}
			break;
		case'p':
			if (strncmp(str, "pow(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				return Function_String_to_Double(StrCut(str + 3, x, y, index, POW), x, y);
			}
			else if (strncmp(str, "pi", 2) == 0)
			{
				return Function_String_to_Double(StrCut(str + 2, x, y, PI), x, y);
			}
			break;
		case's':
			if (strncmp(str, "sin(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				return Function_String_to_Double(StrCut(str + 3, x, y, index, SIN), x, y);
			}
			break;
		case'c':
			if (strncmp(str, "cos(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				return Function_String_to_Double(StrCut(str + 3, x, y, index, COS), x, y);
			}
			break;
		case't':
			if (strncmp(str, "tan(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				return Function_String_to_Double(StrCut(str + 3, x, y, index, TAN), x, y);
			}
			break;
		}
		cout << "ERROR 2 - ������ �������������� ���� � ������ ������, ���������: " << str[0] << endl << "�������? (1/0)" << endl;
		int u = 1;
#ifdef DEBUG
		u = 0;
#endif //DEBUG
		if (u) {
			char_to_clear(str, str[0]);
			return Function_String_to_Double(str, x, y);
		}

		else {
			cout << "��� ��� ���" << endl;
			return Function_String_to_Double(str + 1, x, y);

		}
	}
	else
	{
		cout << "ERROR 2 - ������ �������������� ���� � ������ ������, ���������: " << str[0] << endl << "�������? (1/0)" << endl;
		int u;
#ifdef DEBUG
		u = 0;
#endif //DEBUG
		if (u) {
			char_to_clear(str, str[0]);
			return Function_String_to_Double(str, x, y);
		}

		else {
			cout << "��� ��� ���" << endl;
			return Function_String_to_Double(str + 1, x, y);

		}
	}
}

#pragma once
