#pragma once
//Комментируем процесс разработки, сохраняем неудачные дубли - об удачах говорить никто не будет
//Жаль я догадался сделать это лишь ближе к концу проекта
/*
-------
подглядел я где-то использование wstring в винапи программе...
НЕ РАБОТАЮТ МЕТОДЫ. СОВСЕМ. wstr.size() равняетя нулю, хотя отладчик видит в строке значени. То же самое со всеми остальными методами. Это после получения значения из  GetText. Ну почему это не работает. И почему я думаю, что работать должно. Кому  должно? Почему отладчик может прочесть переменную, а ее же методы - нет. Вот почему.
few hours later
if (wcschr(COMMA_, Checkstr[i]) == 0); - точка-запятую видишь? а она ЕСТЬ
Checkstr[i] == DOT_; вот как такое происходит. Уму не постижимо. вместо знака равно проверка равенства. И как жить после этого
-------
НРАВОУЧЕНИЕ СЕБЕ
о благодать, сошедшая откуда-то 
я догодался, именно догодался, что там происходит и почему приложение лагало при нажатии н кнопку домой и при скрпллинге больших цифр
просто потмоу что не умею делсть нормально дебаггинг и отслеживать состояние переменных в прямом эфире
без консоли
хотя, судя по характеру проблемы, можно было бы сделать что-то вроде вывода имен функций, вызываемых приложением
-------
ебаный gdi+ - почему его так сложно активировать
-------
100 лет прошло. а с помощью стандартного GDI картинки и иконки так и не выводятся
-------
ну вот, года не прошло и появилась синкхронизация с гитом - ураааа
------- DrawLine(a,x1,y,x2,y2) DrawLine(a,x1 + Wnd_Plot->setka.sx_center,y*(-1) + Wnd_Plot->setka.sy_center,x2 + Wnd_Plot->setka.sx_center,y2*(-1) + Wnd_Plot->setka.sy_center)
это понималось очень долго в отношении moveto и lineto - надо было всего то поставить скобки внутри функций - и все бы заработало
textout - дефайны системы заменяют  сам текстаут на textoutW поэтому с этим дефайном тыкался не меньше полутора часов (и откуда у меня столько времени)
//КОСТЫЛИ ДЛЯ DEFINE - НУ УСТАЛ Я ИСКАТЬ КАК С ЭТИМ БОРОТЬСЯ -- 2 ЧАСА ушло на понимание того, что чтоб сработал макрос, надо поставить скобочки
-------
оказывается, с использованием проверки ifinf и ifnan программа не может найти перегрузку , если проверяется переменная типа int - долго же до меня это доходило
-------
благодаря таймеру получилось узнать, что использование cachedbitmap ускоряет вывод графика на битмап сетки в почти три раза (от -10 до 10 с шагом 0,001 log(x)) - фпс изменился с 20-30 на 50-60
-------
std::stod которая переводит значения строки в double решила вдруг ПЕРЕСТАТЬ считать числа с точкой за вещественные - новая мода на запятые - почему так произошло???
-------
//char txt[100];
LPWSTR lptext = (LPWSTR)malloc(MAX_LOADSTRING);
std::wstring text;//ошибка считывания GetWindowText при вводе log(x)+tan(x)
-------
мучался бы с переводом из аски в юникод до скончания времен, если б ни туториалы - так я и не понял, посредством чего эти все преобразования происходят
проверка строки на пустоту еше не решена - длина строки всегда РАВНА нулю - всегда, даже когда отладка НЕ показывает в переменной "" 
то ::wstrint.size() показывает чепуху  ::wstrint.empty() тоже 
-------
			//Myplot.myvec_xy_picsel.reserve((int)(Wnd_Plot->setka.Br - Wnd_Plot->setka.Ar) / Wnd_Plot->setka.Hr + 1);//+1 - а оно вообше надо?
			//Myplot.myvec_xy.reserve((int)(Wnd_Plot->setka.Br - Wnd_Plot->setka.Ar) / Wnd_Plot->setka.Hr + 1);//+1 - а оно вообше надо?
-------
//MessageBox(NULL, L"Нельзя так числа вводить!", L"Информация", MB_ICONINFORMATION | MB_OK);
MessageBox какого-то хера не показывается сам - надо ткнуть ctrl или выйти и зайти в окно - потом он выскакивает на передний план
-------
void transform(HDC hdc)
{
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, Wnd_Plot->sx, -Wnd_Plot->sy, NULL);//установка  логические размеры - в пикселах - влияет на размеры текста и проч "писельные" переменные
	SetViewportExtEx(hdc, Wnd_Plot->sx, Wnd_Plot->sy, NULL);//ОБЛАСТЬ ВЫВОДА  -  физические размеры области вывода в пикселах
	SetViewportOrgEx(hdc, Wnd_Plot->setka.sx_center, Wnd_Plot->setka.sy_center, NULL);
}
не хочет эта шняга нормально работать, придется самому костыли делать для перевода систем координат 
-------
написать функцию и скопировать ее в код забыв убрать void и мучиться пол часа а хули ничего не поменялось и не заработало
-------
break; - он должен быть после операторов моего избранного case, а не перед ними сразу за case 1:break;~~~~~
-------
вот это все заменяем картинками
	//	CreateWindowEx(0, L"STATIC", L"Поле для уравнения", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 15, 280, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"F(x) = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 42, 40, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"A = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst2, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"B = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 40, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"H. = ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 140, 82, 40, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"Интегралушка ну посчитайся ", WS_CHILD | SS_LEFT | WS_VISIBLE, edit_otst1 + 100, 240, 200, 20, hWnd, nullptr, nullptr, nullptr);
	//	CreateWindowEx(0, L"STATIC", L"\
	//Писать только так и никак иначе:\n\
	//- + * / ( )\t e = 2.7\n\
	// 'x - икс'\t'pi = 3.1415...'\n\
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
замена доп окна с выводом на консоль - оказзывается ею тоже можно пользоваться используя привычные std::cout 
-------
переполнение меня забуллило - хз как это решить пусть try catch ловят
-------
				HWND hStatic = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | SS_LEFT | WS_VISIBLE, 305, 120, 70, 40, hWnd, nullptr, nullptr, nullptr);
				std::wstring str = L"Введите\nчисла\n";
				SetWindowText(hStatic, str.c_str());
				Sleep(1000);
				DestroyWindow(hStatic);
				break;
ну допустим теперь месседж боксы норм работают
-------
с обработками бесконечностей и бесконечных несоответствий типов данных в throw, try-catch разобрались
-------
пора бы и понять  почему InvalidateRect(Wnd_Plot->hWnd, NULL, TRUE); не хочет перерисовывать окно когда я создаю график. 





*/
