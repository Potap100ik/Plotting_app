#include "Main_files/STD/stdafx.h"
#include "Main_files/STD/Standard.h"

Gdiplus::Pen* GetPen_for_Integral()
{
	//���� - ��� ��������� ��� �����
	//������ - ������������
	//������ �������� - ������ ����� � ��������
	return new Pen(Color(1000, 255, 0, 0), 2);
}

Gdiplus::Pen* GetPen_for_Main_Plot()
{
	//���� - ��� ��������� ��� �����
	//������ - ������������
	//������ �������� - ������ ����� � ��������
	return new Pen(Color(1000, 0, 255, 0), 2);
}