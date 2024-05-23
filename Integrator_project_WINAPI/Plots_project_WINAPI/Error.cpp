#include "Error.h"

int CheckFunctionErrorMsg(ERROR_STRUCT& err_msg, HWND hWndEdit_Erroors, HWND hWnd)
{
	wchar_t* str = (wchar_t*)malloc(MAX_LOADSTRING);

	switch (err_msg.error_type)
	{
	case CHAR_ERR:
		if (err_msg.char_err == ' ')
			swprintf(str, L"������ ������ ������");
		else
			swprintf(str, L"�������������� �������: %c", err_msg.char_err);
		break;
	case EXPRESSION_ERR:
	{
		wchar_t* str2 = (wchar_t*)calloc(1, MAX_LOADSTRING);
		mbstowcs(str2, err_msg.str_err, strlen(err_msg.str_err));
		swprintf(str, L"�������������� ���������: %s", str2);
		free(str2);
	}
		break;
	case EMPTY_ERR:
		swprintf(str, L"������� ������ ���������");
		break;
	case WHATS_APP_ERR:
		swprintf(str, L"���������� ������� - ������ �����������");
		break;
	case BRACKET_ERR:
		swprintf(str, L"������� ������ ��������");
		break;
	case OTHER_ERR:
		swprintf(str, L"����� �� ������ ���� ���������");
		break;
	}
	MessageBox(hWnd, L"� �������� ����������!!!\n��������� ���������� �������", L"��������, ������", MB_OK | MB_ICONSTOP);
	SetWindowText(hWndEdit_Erroors, str);
	free(str);
	return 0;
}

int CheckOnlyNumbers(LPWSTR &A_wstr, LPWSTR &B_wstr, LPWSTR &H_wstr, HWND hWndEdit_Erroors, HWND hWnd, HWND hWndEdit_Integral)
{
	//int i = 0;
	//int size = A_wstr.size();
	//std::wstring DOT_ = L".";
	//std::wstring::iterator it = A_wstr.begin();
	//std::wstring::iterator it2 = A_wstr.end();
	//while (it < A_wstr.end()&&i<size)
	//{
	//	if (std::wcschr(NUMBERIC_STR, wchar_t(*it)) == 0)
	//		return 1;
	//	if ((wchar_t)*it == ',')
	//		A_wstr.replace(it, it + 1, DOT_);
	//	it++;
	//	i++;
	//}
	wchar_t DOT_ = '.';
	int i;

	i = 0;
	if (A_wstr[i] == '\0')
	{
		MessageBox(hWnd, L"� ������ ����������!!!\n������ ���������� �������� �", L"��������, ������", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"�������� ���� �� �����");
		SetWindowText(hWndEdit_Erroors, L"��������� �������� A");
		return 1;
	}
	while (A_wstr[i] != '\0' && i < sizeof(A_wstr)) {
		wchar_t ch = A_wstr[i];
		if (wcschr(NUMBERIC_STR, A_wstr[i]) == 0) {
			if (wcschr(COMMA_, A_wstr[i]) != 0)
				A_wstr[i] = DOT_;
			else
			{
				MessageBox(hWnd, L"� ������ ����������!!!\n������ ���������� �������� �", L"��������, ������", MB_OK | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"�������� ���� �� �����");
				SetWindowText(hWndEdit_Erroors, L"��������� �������� A");
				return 1;
			}
		}
		i++;
	}
	
	i = 0;
	if (B_wstr[i] == '\0')
	{
		MessageBox(hWnd, L"� ������ ����������!!!\n������ ���������� �������� B", L"��������, ������", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"�������� ���� �� �����");
		SetWindowText(hWndEdit_Erroors, L"��������� �������� B");
		return 1;
	}
	while (B_wstr[i] != '\0' && i < sizeof(B_wstr)) {
		wchar_t ch = B_wstr[i];
		if (wcschr(NUMBERIC_STR, B_wstr[i]) == 0) {
			if (wcschr(COMMA_, B_wstr[i]) != 0)
				B_wstr[i] = DOT_;
			else
			{
				MessageBox(hWnd, L"� ������ ����������!!!\n������ ���������� �������� B", L"��������, ������", MB_OK | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"�������� ���� �� �����");
				SetWindowText(hWndEdit_Erroors, L"��������� �������� B");
				return 1;
			}
		}
		i++;
	}

	i = 0;
	if (H_wstr[i] == '\0')
	{
		MessageBox(hWnd, L"� ������ ����������!!!\n������ ���������� �������� H", L"��������, ������", MB_OK | MB_ICONSTOP);
		SetWindowText(hWndEdit_Integral, L"�������� ���� �� �����");
		SetWindowText(hWndEdit_Erroors, L"��������� �������� H");
		return 1;
	}
	while (H_wstr[i] != '\0' && i < sizeof(H_wstr)) {
		wchar_t ch = H_wstr[i];
		if (wcschr(NUMBERIC_STR, H_wstr[i]) == 0) {
			if (wcschr(COMMA_, H_wstr[i]) != 0)
				H_wstr[i] = DOT_;
			else
			{
				MessageBox(hWnd, L"� ������ ����������!!!\n������ ���������� �������� H", L"��������, ������", MB_OK | MB_ICONSTOP);
				SetWindowText(hWndEdit_Integral, L"�������� ���� �� �����");
				SetWindowText(hWndEdit_Erroors, L"��������� �������� H");
				return 1;
			}
		}
		i++;
	}
	return 0;
}

int CheckImageOpening(Gdiplus::Bitmap* img_bck, Gdiplus::Bitmap* img_home, Gdiplus::Bitmap* img_clr, HWND hWnd)
{
	if (img_bck == NULL)
	{
		MessageBox(hWnd, L"� ��������� ����������!!!\n�������� ��� ���� ����������", L"��������, ������", MB_OK | MB_ICONSTOP);
		return 1;
	}
	if (img_home == NULL)
	{
		MessageBox(hWnd, L"� ��������� ����������!!!\n�������� ��� ������ ����������", L"��������, ������", MB_OK | MB_ICONSTOP);
		return 1;
	}
	if (img_clr == NULL)
	{
		MessageBox(hWnd, L"� ��������� ����������!!!\n�������� ����������", L"��������, ������", MB_OK | MB_ICONSTOP);
		return 1;
	}
	return 0;
}


