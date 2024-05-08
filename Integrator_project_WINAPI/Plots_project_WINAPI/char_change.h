#pragma once
//��������� ������������ ����� � ��������� ������������� �������
#define MAX_STRLENGTH 100
#include <stdio.h>
#define CANSELWORDS "()1234567890*/-+.expabslog10lnpowpisincostan"//�� ��� ������ �������, ���� ������� � ������ ������


char* char_to_clear(char* str, char chh);
char* char_to_swap(char* str, double x, char chh);
char* char_to_delete(char* str, int index);

char* char_to_swap(char* str, double x, char chh)
{

	char* ch_x = (char*)malloc(sizeof(double));
	sprintf(ch_x, "%lf", x);

	char* ch = (char*)malloc(MAX_STRLENGTH);
	char* buf = (char*)malloc(MAX_STRLENGTH);
	while (ch = strchr(str, chh))
	{

		strcpy(buf, ch + 1);
		memcpy(ch, ch_x, sizeof(x));
		memmove(ch + sizeof(x), buf, strlen(buf) + 1);
	}
	return str;
}

char* char_to_clear(char* str, char chh)
{
	if (strchr(CANSELWORDS, chh) != 0)
	{
		char_to_delete(str, strchr(str, chh) - str);
		return str;
	}

	char* ch = (char*)malloc(MAX_STRLENGTH);
	char* buf = (char*)malloc(MAX_STRLENGTH);
	while (ch = strchr(str, chh))
	{
		strcpy(buf, ch + 1);
		memmove(ch, buf, strlen(buf) + 1);
	}
	return str;
}

char* char_to_delete(char* str, int index)
{
	memmove(str + index, str + index + 1, strlen(str) - index + 1);
	return str;
}
