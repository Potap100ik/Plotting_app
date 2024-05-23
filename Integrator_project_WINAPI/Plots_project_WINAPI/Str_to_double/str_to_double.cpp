#include "str_to_double.h"
#include "../Main_files/type.h"

void StrCut(char*& str1, char*& str2, int const& index2, int const& size2)
{
	strncpy(str1, str2, index2);//������ 1 - ������ ��� ��������� �� ����� * �� ����� +-
	str1[index2] = '\0';
	memmove(str2, str2 + index2 + 1, size2 - index2 + 1);//�������� ������ 1 �� str � �������� ������� � str2 � ����������� ����� +-
}
char* StrCut(char* str, double* x, int y, int const index, FUNC en) {//����������� � ���������� � ������� - ���� ������, �������� ������, ����� ������, ����� ������ �� �����
	if (index == 0)
	{
#ifdef DEBUG
		cout << "ERROR 1 - ������ �������������� ���� �������" << endl;
		return 0;
#else
		ERROR_STRUCT nani;
		free(str);
		nani.error_type = EMPTY_ERR;
		throw(nani);
#endif //DEBUG
	}


	char* str1 = (char*)malloc(MAX_LOADSTRING),
		* str2 = (char*)malloc(MAX_LOADSTRING);
	strcpy(str2, str + 1);
	str2[index - 1] = '\0';
	try {

		switch (en)
		{
		case EXP:
			sprintf(str1, "%lf", y * exp(Function_String_to_Double(str2, x)));
			break;
		case ABS:
			sprintf(str1, "%lf", y * abs(Function_String_to_Double(str2, x)));
			break;
		case LOG:
			sprintf(str1, "%lf", y * log(Function_String_to_Double(str2, x)));
			break;
		case LOG10:
			sprintf(str1, "%lf", y * log10(Function_String_to_Double(str2, x)));
			break;
		case POW:
		{
			int index2 = strcspn(str, ";");
			strcpy(str1, str);
			str1[index2] = '\0';
			char* str_ = (char*)malloc(MAX_LOADSTRING); strcpy(str_, str2 + index2); free(str2);
			char* str_2 = (char*)malloc(MAX_LOADSTRING); strcpy(str_2, str1);
			sprintf(str1, "%lf", y * pow(Function_String_to_Double(str_2, x), Function_String_to_Double(str_, x)));
		}
		break;
		case SQRT:
			sprintf(str1, "%lf", y * sqrt(Function_String_to_Double(str2, x)));
			break;
		case SIN:
			sprintf(str1, "%lf", y * sin(Function_String_to_Double(str2, x)));
			break;
		case COS:
			sprintf(str1, "%lf", y * cos(Function_String_to_Double(str2, x)));
			break;
		case TAN:
		{
			double fx = Function_String_to_Double(str2, x);
			int k = 100;
			if ((int)(((int)((fx + M_PI2) / M_PI) - (fx + M_PI2) / M_PI) * k) == 0) {
				double nani = NAN;
				throw(nani);
			}
			else
				sprintf(str1, "%lf", y * tan(fx));
		}
		break;
		case ATAN:
			sprintf(str1, "%lf", y * atan(Function_String_to_Double(str2, x)));
			break;
		case ASIN:
			sprintf(str1, "%lf", y * asin(Function_String_to_Double(str2, x)));
			break;
		case ACOS:
			sprintf(str1, "%lf", y * acos(Function_String_to_Double(str2, x)));
			break;
		case BRAKET:
			sprintf(str1, "%lf", y * Function_String_to_Double(str2, x));
			break;
		default:
		{
#ifdef DEBUG
			//MessageBox(0, L"��������� ������\n��� �����?!!!\n�� ���� ��������� �������", L"��������, ������", MB_RETRYCANCEL | MB_ICONSTOP);
			cout << "ERROR 6 - ����������� ��������������� �������� - �������� ������� � ������� ��� �� ������� � ���" << endl;
			return 0;
#else
			free(str);
			free(str1);
			ERROR_STRUCT nani;
			nani.char_err = '?';
			nani.error_type = WHATS_APP_ERR;
			throw(nani);
#endif //DEBUG
		}
		return 0;
		}
	}
	catch (ERROR_STRUCT err_msg)
	{
		free(str1);
		free(str);
		throw(err_msg);
	}
	//sprintf(str1, "%lf", Function_Count(str2 + 1, x, y));//����������� ��������������� ��������� 1 � ������������ ����� � �������� � str1
	bool fl;
	fl = (strncmp(str1, "+nan(ind)", 4) == 0 || strncmp(str1, "-nan(ind)", 4) == 0 || strncmp(str1, "nan", 3) == 0 || strcmp(str1, "nan)") == 0 || strcmp(str1, "-inf") == 0 || strcmp(str1, "+inf") == 0 || strcmp(str1, "inf") == 0);
	if (fl)
	{
		double nani = NAN;
		free(str1); free(str);
		throw(nani);
		//throw(str1);
	}
	memcpy(str1 + strlen(str1), str + index + 1, strlen(str) - index);
	//memcpy(str1 + strlen(str1), str + index, strlen(str) - index + 1); //������ ��� ������ (2+2)*2
	//str1 + strlen(str1)		- ������ �������� '\0', ���������� �� �������� ������� 
	//str + index + 1 			- ������ ������ ������ �������������� ������
	//strlen(str) - index = 	- ���������� �������������� ������, ������� '\0'
	free(str);
	return str1;
}
char* StrCut(char* str, double* x, int y, FUNC en) {//����������� � ���������� � ������� - ���� ������, �������� ������, ����� ������, ����� ������ �� �����
	char* str1 = (char*)malloc(MAX_LOADSTRING);
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
	{

#ifdef DEBUG
		//MessageBox(0, L"��������� ������\n��� �����?!!!\n�� ���� ��������� �������", L"��������, ������", MB_RETRYCANCEL | MB_ICONSTOP);
		cout << "ERROR 6 - ����������� ��������������� �������� - �������� ������� � ������� ��� �� ������� � ���" << endl;
		return 0;
#else
		free(str);
		free(str1);
		ERROR_STRUCT nani;
		nani.char_err = '?';
		nani.error_type = WHATS_APP_ERR;
		throw(nani);
#endif //DEBUG
	}
	return 0;
	}
	strcat(str1, str);
	free(str);
	return str1;
}
int Index_of_smth(char* str, char ch1, char ch2, char ch3, char ch4)
{
	int count = 0;
	char ch = str[0];
	int index2 = 0;
	int i = 0;//������ ��� ������� ���� - ��������
	while (ch != '\0')
	{
		ch = str[i];

		if (ch == ch1 || ch == ch2 || ch == ch3 || ch == ch4)//������ ������ ������ ���� +- ��� */
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
int Index_of_smth(char* str, char ch1, char ch2, char ch3)
{
	int count = 0;
	char ch = str[0];
	int index2 = 0;
	int i = 0;//������ ��� ������� ���� - ��������
	while (ch != '\0')
	{
		ch = str[i];

		if (ch == ch1 || ch == ch2 || ch == ch3)//������ ������ ������ ���� +- ��� */
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
double Function_String_to_Double(char* str, double* x, int y, bool can_delete_str)
{
	if (strcspn(str, "1234567890") == 0)//���� ������ ���� ������ - �����
	{
		int size = strlen(str);
		int index = strcspn(str, "*+-/^");
		if (size == index) {//���� � ������ �� ������ ���� ���������, �������, �������� ��� ���������
			if (strspn(str, "1234567890.,.,") == size && size != 0)
			{
				double mydouble = stod(str);
				if (can_delete_str)free(str);
				return y * mydouble;//������ ������ ������� �� ���� � �������� ������ - �� ����� ���������� ������������ �����
			}
			else
			{
				index = strspn(str, "1234567890.,.,");
#ifdef DEBUG
				cout << "ERROR 1 - ������ �������������� ���� �������" << endl;
				return 0;
#else

				ERROR_STRUCT nani;
				if (size == 0)
				{
					//if (can_delete_str)������ ��������, �� ��� ���� � ������ ������ ������... ���� �����-��
					//	free(str);
					nani.error_type = EMPTY_ERR;
				}
				else {
					nani.char_err = str[index];
					if (can_delete_str)
						free(str);
					nani.error_type = CHAR_ERR;
				}
				throw(nani);
#endif //DEBUG
			}
		}
		else//�� ����� �����-�� ����� - ���� ��������� ������ � ����������� ���������� ����������
		{

			char* str1 = (char*)malloc(MAX_LOADSTRING);
			char* str2 = (char*)malloc(MAX_LOADSTRING);

			strncpy(str1, str, index);//������ 1 - ��� �����
			str1[index] = '\0';
			memcpy(str2, str + index + 1, size - index + 1);//�������� ������ 1 �� str � �������� ������� � str2 �� ����������� ����� *-+/

			char ch = str[index];
			if (can_delete_str)free(str);
			switch (ch)
			{
			case '^':
			{
				int size2 = strlen(str2); //�������� ����� ������ 2

				//���� ����� +  �  -
				//���� ����� ���� � ����� ����������, � ����� ������ �� �����


				int index2 = Index_of_smth(str2, '+', '-', '*', '/');
				if (index2 != 0) {//���� � ������ 2 ������� �����  �������� ��� ��������� - ���� ���������� ���������� ��� �������������� ��������

					double d = y * atof(str1);
					char ch = str2[index2];//��������� ��������� ����
					StrCut(str1, str2, index2, size2);//�������� ������ 1 �� str2 � �������� ������� � str2 � ����������� ����� */

					switch (ch)
					{
					case '+': return pow(d, Function_String_to_Double(str1, x)) + Function_String_to_Double(str2, x);
					case '-': return pow(d, Function_String_to_Double(str1, x)) - Function_String_to_Double(str2, x);
					case '*': return pow(d, Function_String_to_Double(str1, x)) * Function_String_to_Double(str2, x);
					case '/': return pow(d, Function_String_to_Double(str1, x)) / Function_String_to_Double(str2, x);
					}
					//Function_Count(str1, x) - ��������� 1, �� ������� ���� �������� ��� ��������� d ����� ��� ��� ���������� ��� �������� ��������� 2
					//Function_Count(str2, x) - ��������� 2, ������� ������������� ��������
				}
				else
				{
					double mydouble = atof(str1);
					free(str1);
					return pow(y * mydouble, Function_String_to_Double(str2, x));
				}
			}
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
					double mydouble = atof(str1);
					free(str1);
					return y * mydouble * Function_String_to_Double(str2, x);
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
					double mydouble = atof(str1);
					free(str1);
					return y * mydouble / Function_String_to_Double(str2, x);
				}
			}
			case '+':
			{
				int size2 = strlen(str2); //�������� ����� ������ 2
				int index2 = Index_of_smth(str2, '*', '/', '^');
				if (index2 != 0) {//���� � ������ 2 ������� �����  ��������� � ������� - ���� ���������� ���������� ��� �������������� ��������

					double d = y * atof(str1);
					char ch = str2[index2];//��������� ��������� ����
					StrCut(str1, str2, index2, size2); //�������� ������ 1 �� str2 � �������� ������� � str2 � ����������� ����� +-

					switch (ch)
					{
					case '*': return d + (Function_String_to_Double(str1, x) * Function_String_to_Double(str2, x));
					case '/': return d + (Function_String_to_Double(str1, x) / Function_String_to_Double(str2, x));
					case '^': return d + pow(Function_String_to_Double(str1, x), Function_String_to_Double(str2, x));
					}
					//Function_Count(str1) - ��������� 1, �� ������� ���� �������� ��� ��������� d ����� ��� ��� ���������� ��� �������� ��������� 2
					//Function_Count(str2) - ��������� 2, ������� ������������� ��������
				}

				else
				{
					double mydouble = atof(str1);
					free(str1);
					return y * mydouble + Function_String_to_Double(str2, x);
				}
			}
			case '-':
			{
				int size2 = strlen(str2); //�������� ����� ������ 2
				int index2 = Index_of_smth(str2, '*', '/', '^');
				if (index2 != 0) {//���� � ������ 2 ������� �����  ��������� � ������� - ���� ���������� ���������� ��� �������������� ��������

					double d = y * atof(str1);
					char ch = str2[index2];//��������� ��������� ����
					StrCut(str1, str2, index2, size2); //�������� ������ 1 �� str2 � �������� ������� � str2 � ����������� ����� +-

					switch (ch)
					{
					case '*': return d - (Function_String_to_Double(str1, x) * Function_String_to_Double(str2, x));
					case '/': return d - (Function_String_to_Double(str1, x) / Function_String_to_Double(str2, x));
					case '^': return d - pow(Function_String_to_Double(str1, x), Function_String_to_Double(str2, x));
					}
					//Function_Count(str1) - ��������� 1, �� ������� ���� �������� ��� ��������� d ����� ��� ��� ���������� ��� �������� ��������� 2
					//Function_Count(str2) - ��������� 2, ������� ������������� ��������
				}

				else
				{
					double mydouble = atof(str1);
					free(str1);
					return y * mydouble - Function_String_to_Double(str2, x);
				}
			}
			default:
			{
#ifdef DEBUG
				cout << "ERROR 1 - ������ �������������� ����: " << str[index] << " ����� �����" << str1 << endl << "�������? (1/0)" << endl;
				return 0;
#else

				ERROR_STRUCT nani;
				free(str1);
				free(str2);
				nani.error_type = WHATS_APP_ERR;
				throw(nani);
#endif //DEBUG
			}
			}
		}
	}
	else if (str[0] == 'x') {
		char* str_send = (char*)malloc(MAX_LOADSTRING); strcpy(str_send, str + 1); if (can_delete_str)free(str);
		return Function_String_to_Double(StrCut(str_send, x, 1, XX), x, y);
	}
	else if (str[0] == '(')
	{

		int index = Index_of_smth(str);
		if (strlen(str) == index + 1) {//����������� �������� ������ ��������� ���� ��������� � ������ - ����� ��� �� � ����������, �� ��� ������
			str[index] = '\0';
			char* str_ = (char*)malloc(MAX_LOADSTRING); strcpy(str_, str + 1); if (can_delete_str)free(str);
			return y * Function_String_to_Double(str_, x);
		}
		else if (index == 1)
		{
#ifdef DEBUG
			cout << "ERROR 4 - ����������� ��������� ������ ������, ������� ������" << endl << "�������? (1/0)" << endl;
			return 0;
#endif //DEBUG)
			char* str_ = (char*)malloc(MAX_LOADSTRING); strcpy(str_, str + 2); if (can_delete_str)free(str);
			return Function_String_to_Double(str_, x, y);
		}
		else if (index == 0)
		{

#ifdef DEBUG
			cout << "ERROR 3 - ������ �������������� ���� � ������ ������ � ���� �������� �������� (" << endl << "�������?(1/0)" << endl;
			return 0;
#else

			ERROR_STRUCT nani;
			nani.char_err = str[0]; if (can_delete_str)free(str);
			nani.error_type = BRACKET_ERR;
			throw(nani);
#endif //DEBUG

		}
		else//����������� �������� ��������� ���������� - ������ ���������� ��������� �� �������� � �������� ������, ������� � �������
		{
			return Function_String_to_Double(StrCut(str, x, y, index, BRAKET), x, y);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////0 ��� 1
	else if (strcspn(str, "ealpsct") == 0)
	{
		char* str_ = (char*)malloc(MAX_LOADSTRING);
		switch (str[0])
		{
		case'e':
		{
			if (strncmp(str, "exp(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				strcpy(str_, str + 3); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_/*��c������� exp*/, x, y, index, EXP), x);
			}
			else
			{
				strcpy(str_, str + 1); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, 1, E), x, y);//�� ����� ����������
			}
		}
		break;
		case'a':
		{

			if (strncmp(str, "abs(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				strcpy(str_, str + 3); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, ABS), x);
			}
			else if (strncmp(str, "arctan(", 7) == 0)
			{
				int index = Index_of_smth(str + 6);
				strcpy(str_, str + 6); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, ATAN), x);
			}
			else if (strncmp(str, "arcsin(", 7) == 0)
			{
				int index = Index_of_smth(str + 6);
				strcpy(str_, str + 6); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, ASIN), x);
			}
			else if (strncmp(str, "arccos(", 7) == 0)
			{
				int index = Index_of_smth(str + 6);
				strcpy(str_, str + 6); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, ACOS), x);
			}
		}
		break;
		case'l':
		{
			if (strncmp(str, "log(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				strcpy(str_, str + 3); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, LOG), x);
			}
			else if (strncmp(str, "ln(", 3) == 0)
			{
				int index = Index_of_smth(str + 2);
				strcpy(str_, str + 2); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, LOG), x);
			}
			else if (strncmp(str, "log10(", 6) == 0)
			{
				int index = Index_of_smth(str + 5);
				strcpy(str_, str + 5); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, LOG10), x);
			}
		}
		break;
		case'p':
		{
			if (strncmp(str, "pow(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				strcpy(str_, str + 3); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, POW), x);
			}
			else if (strncmp(str, "pi", 2) == 0)
			{
				strcpy(str_, str + 2); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, 1, PI), x, y);
			}
		}
		break;
		case's':
		{
			if (strncmp(str, "sin(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				strcpy(str_, str + 3); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, SIN), x);
			}
			else if (strncmp(str, "sqrt(", 5) == 0)
			{
				int index = Index_of_smth(str + 4);
				strcpy(str_, str + 4); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, SQRT), x);
			}
		}
		break;
		case'c':
		{
			if (strncmp(str, "cos(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				strcpy(str_, str + 3); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, COS), x);
			}
			else if (strncmp(str, "ctan(", 5) == 0)
			{
				int index = Index_of_smth(str + 4);
				strcpy(str_, str + 4); if (can_delete_str)free(str);
				return 1.0 / (Function_String_to_Double(StrCut(str_, x, y, index, TAN), x));
			}
			else if (strncmp(str, "ctg(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				strcpy(str_, str + 3); if (can_delete_str)free(str);
				return 1.0 / (Function_String_to_Double(StrCut(str_, x, y, index, TAN), x));
			}
		}
		break;
		case't':
		{
			if (strncmp(str, "tan(", 4) == 0)
			{
				int index = Index_of_smth(str + 3);
				strcpy(str_, str + 3); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, TAN), x);
			}
			else if (strncmp(str, "tg(", 3) == 0)
			{
				int index = Index_of_smth(str + 2);
				strcpy(str_, str + 2); if (can_delete_str)free(str);
				return Function_String_to_Double(StrCut(str_, x, y, index, TAN), x);
			}
		}
		break;
		default:
			break;
		}
#ifdef DEBUG
		cout << "ERROR 2 - ������ �������������� ���� � ������ ������, ���������: " << str[0] << endl << "�������? (1/0)" << endl;
		return 0;
#else
		ERROR_STRUCT nani;
		strcpy(nani.str_err, str);
		free(str_);
		if (can_delete_str)free(str);
		nani.error_type = EXPRESSION_ERR;
		throw(nani);
#endif //DEBUG
	}
	else if (str[0] == '-')
	{
		
		char* str_ = (char*)malloc(MAX_LOADSTRING); strcpy(str_, str + 1); if (can_delete_str)free(str);
		return Function_String_to_Double(str_, x, -1);
	}
	else if (str[0] == '\0') {
#ifdef DEBUG
		cout << "ERROR 0 - ������� ������ ������" << endl; return 0;
#else
		if (can_delete_str)free(str);
		char nani = '!';
		throw(nani);
#endif //DEBUG

	}
	else
	{
#ifdef DEBUG
		cout << "ERROR 2 - ������ �������������� ���� � ������ ������, ���������: " << str[0] << endl << "�������? (1/0)" << endl;
		return 0;
#else
		ERROR_STRUCT nani;
		nani.char_err = str[0];
		if (can_delete_str)free(str);
		nani.error_type = CHAR_ERR;
		throw(nani);
#endif //DEBUG
	}
}

#pragma once
