#pragma once
//������������ ������� ����������, ��������� ��������� ����� - �� ������ �������� ����� �� �����
//���� � ��������� ������� ��� ���� ����� � ����� �������
/*
-------
��������� � ���-�� ������������� wstring � ������ ���������...
�� �������� ������. ������. wstr.size() �������� ����, ���� �������� ����� � ������ �������. �� �� ����� �� ����� ���������� ��������. ��� ����� ��������� �������� ��  GetText. �� ������ ��� �� ��������. � ������ � �����, ��� �������� ������. ����  ������? ������ �������� ����� �������� ����������, � �� �� ������ - ���. ��� ������.
few hours later
if (wcschr(COMMA_, Checkstr[i]) == 0); - �����-������� ������? � ��� ����
Checkstr[i] == DOT_; ��� ��� ����� ����������. ��� �� ���������. ������ ����� ����� �������� ���������. � ��� ���� ����� �����
-------
����������� ����
� ���������, �������� ������-�� 
� ���������, ������ ���������, ��� ��� ���������� � ������ ���������� ������ ��� ������� � ������ ����� � ��� ���������� ������� ����
������ ������ ��� �� ���� ������ ��������� ��������� � ����������� ��������� ���������� � ������ �����
��� �������
����, ���� �� ��������� ��������, ����� ���� �� ������� ���-�� ����� ������ ���� �������, ���������� �����������
-------
������ gdi+ - ������ ��� ��� ������ ������������
-------
100 ��� ������. � � ������� ������������ GDI �������� � ������ ��� � �� ���������
-------
�� ���, ���� �� ������ � ��������� �������������� � ����� - ������
------- DrawLine(a,x1,y,x2,y2) DrawLine(a,x1 + Wnd_Plot->setka.sx_center,y*(-1) + Wnd_Plot->setka.sy_center,x2 + Wnd_Plot->setka.sx_center,y2*(-1) + Wnd_Plot->setka.sy_center)
��� ���������� ����� ����� � ��������� moveto � lineto - ���� ���� ����� �� ��������� ������ ������ ������� - � ��� �� ����������
textout - ������� ������� ��������  ��� �������� �� textoutW ������� � ���� �������� ������� �� ������ �������� ����� (� ������ � ���� ������� �������)
//������� ��� DEFINE - �� ����� � ������ ��� � ���� �������� -- 2 ���� ���� �� ��������� ����, ��� ���� �������� ������, ���� ��������� ��������
-------
�����������, � �������������� �������� ifinf � ifnan ��������� �� ����� ����� ���������� , ���� ����������� ���������� ���� int - ����� �� �� ���� ��� ��������
-------
��������� ������� ���������� ������, ��� ������������� cachedbitmap �������� ����� ������� �� ������ ����� � ����� ��� ���� (�� -10 �� 10 � ����� 0,001 log(x)) - ��� ��������� � 20-30 �� 50-60
-------
std::stod ������� ��������� �������� ������ � double ������ ����� ��������� ������� ����� � ������ �� ������������ - ����� ���� �� ������� - ������ ��� ���������???
-------
//char txt[100];
LPWSTR lptext = (LPWSTR)malloc(MAX_LOADSTRING);
std::wstring text;//������ ���������� GetWindowText ��� ����� log(x)+tan(x)
-------
������� �� � ��������� �� ���� � ������ �� ��������� ������, ���� � �� ��������� - ��� � � �� �����, ����������� ���� ��� ��� �������������� ����������
�������� ������ �� ������� ��� �� ������ - ����� ������ ������ ����� ���� - ������, ���� ����� ������� �� ���������� � ���������� "" 
�� ::wstrint.size() ���������� ������  ::wstrint.empty() ���� 
-------
			//Myplot.myvec_xy_picsel.reserve((int)(Wnd_Plot->setka.Br - Wnd_Plot->setka.Ar) / Wnd_Plot->setka.Hr + 1);//+1 - � ��� ������ ����?
			//Myplot.myvec_xy.reserve((int)(Wnd_Plot->setka.Br - Wnd_Plot->setka.Ar) / Wnd_Plot->setka.Hr + 1);//+1 - � ��� ������ ����?
-------
//MessageBox(NULL, L"������ ��� ����� �������!", L"����������", MB_ICONINFORMATION | MB_OK);
MessageBox ������-�� ���� �� ������������ ��� - ���� ������ ctrl ��� ����� � ����� � ���� - ����� �� ����������� �� �������� ����
-------
void transform(HDC hdc)
{
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, Wnd_Plot->sx, -Wnd_Plot->sy, NULL);//���������  ���������� ������� - � �������� - ������ �� ������� ������ � ���� "���������" ����������
	SetViewportExtEx(hdc, Wnd_Plot->sx, Wnd_Plot->sy, NULL);//������� ������  -  ���������� ������� ������� ������ � ��������
	SetViewportOrgEx(hdc, Wnd_Plot->setka.sx_center, Wnd_Plot->setka.sy_center, NULL);
}
�� ����� ��� ����� ��������� ��������, �������� ������ ������� ������ ��� �������� ������ ��������� 
-------
�������� ������� � ����������� �� � ��� ����� ������ void � �������� ��� ���� � ���� ������ �� ���������� � �� ����������
-------
break; - �� ������ ���� ����� ���������� ����� ���������� case, � �� ����� ���� ����� �� case 1:break;~~~~~
-------
��� ��� ��� �������� ����������
	//	CreateWindowEx(0, L"STATIC", L"���� ��� ���������", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 15, 280, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"F(x) = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 42, 40, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"A = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"B = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 40, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"H. = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 140, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"������������ �� ���������� ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 100, 240, 200, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"\
	//������ ������ ��� � ����� �����:\n\
	//- + * / ( )\t e = 2.7\n\
	// 'x - ���'\t'pi = 3.1415...'\n\
	//exp(  )\tabs(  )\tlog(  )\n\
	//log10(  )\tpow( ; )\n\
	//sin(  )\tcos(  )\ttan(  ),",
	//WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1, 300, 300, 200, hWnd, nullptr, nullptr, nullptr);

		//hStat = CreateWindow(L"static", L"static", WS_VISIBLE,
		//	10, 10, 400, 400, NULL, NULL, NULL, NULL);
-------
		//countpaint++;
		//str = std::to_wstring(countpaint);
		//
		//str += L"\nWnd_Plot.setka.sy_center: ";
		//str += std::to_wstring(Wnd_Plot->setka.sy_center);
		//str += L"\nWnd_Plot.sy: ";
		//str += std::to_wstring(Wnd_Plot->sy);
		//if (Wnd_Plot->setka.sy_center < 50)
		//{
		//	str += L"\nWOWOWOWOWOOWOWOWWOWOOWOWOWooooooo ";
		//}
		//SetWindowText(hStat, str.c_str());
������ ��� ���� � ������� �� ������� - ������������ �� ���� ����� ������������ ��������� ��������� std::cout 
-------
������������ ���� ��������� - �� ��� ��� ������ ����� try catch �����
-------
				HWND hStatic = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | SS_LEFT | WS_VISIBLE, 305, 120, 70, 40, hWnd, nullptr, nullptr, nullptr);
				std::wstring str = L"�������\n�����\n";
				SetWindowText(hStatic, str.c_str());
				Sleep(1000);
				DestroyWindow(hStatic);
				break;
�� �������� ������ ������� ����� ���� ��������
-------
� ����������� �������������� � ����������� �������������� ����� ������ � throw, try-catch �����������
-------
���� �� � ������  ������ InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE); �� ����� �������������� ���� ����� � ������ ������. 





*/
