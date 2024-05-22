#include <windows.h> // підключення бібліотеки з функціями API
#include <stdio.h>
#include <vector>
#include <string>
#include "resource.h"
// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "Kovalik";
LPCTSTR szTitle = "LAB3";
int data[4] = { 110, 0, 0, 0 };
// Попередній опис функцій

struct Student {
	std::string name;
	bool defended;
};

// Оголосіть масив студентів
std::vector<Student> first_students = {
	{"Boyko Dmitry Yurievich", true},
	{"Boyko Marina Nikolaevna", true},
	{"Borisova Daria Yevhenivna", false},
	{"Volk Daria Maksymivna", false},
	{"Zadorozhnyi Artem Oleksandrovych", true},
	{"Kardash Artem Evgenievich", true},
	{"Klimovsky Alexander Anatolyevich", false},
	{"Kovalik Vadim Valerievich", true},
	{"Korobka Vladislav Vitalievich", false},
	{"Korkh Oleg Sergiyovych", false},
	{"Latysh Oleg Vitalievich", false},
	{"Litvinenko Dmitry Nikolaevich", true},
	{"Nazarova Iryna Oleksandrivna", false},
	{"Obolonik Yan Vitaliyovych", true},
	{"Pestretsov Timofey Vladimirovich", false},
	{"Prudnikov Konstantin Valerievich", true},
	{"Savenko Roman Evgenievich", true},
	{"Sereda Oleksandr Vitaliyovych", true},
	{"Cheryak Danylo Dmytrovych", false},
	{"Shchapov Alexander Ivanovich", true}
};

std::vector<Student> second_students = {
	{"Boyko Dmitry Yurievich", true},
	{"Boyko Marina Nikolaevna", false},
	{"Borisova Daria Yevhenivna", false},
	{"Volk Daria Maksymivna", false},
	{"Zadorozhnyi Artem Oleksandrovych", false},
	{"Kardash Artem Evgenievich", false},
	{"Klimovsky Alexander Anatolyevich", false},
	{"Kovalik Vadim Valerievich", true},
	{"Korobka Vladislav Vitalievich", false},
	{"Korkh Oleg Sergiyovych", false},
	{"Latysh Oleg Vitalievich", false},
	{"Litvinenko Dmitry Nikolaevich", false},
	{"Nazarova Iryna Oleksandrivna", false},
	{"Obolonik Yan Vitaliyovych", false},
	{"Pestretsov Timofey Vladimirovich", false},
	{"Prudnikov Konstantin Valerievich", false},
	{"Savenko Roman Evgenievich", false},
	{"Sereda Oleksandr Vitaliyovych", false},
	{"Cheryak Danylo Dmytrovych", false},
	{"Shchapov Alexander Ivanovich", false}
};

// Оголосіть масив студентів
std::vector<Student> third_students = {
	{"Boyko Dmitry Yurievich", false},
	{"Boyko Marina Nikolaevna", true},
	{"Borisova Daria Yevhenivna", false},
	{"Volk Daria Maksymivna", false},
	{"Zadorozhnyi Artem Oleksandrovych", false},
	{"Kardash Artem Evgenievich", true},
	{"Klimovsky Alexander Anatolyevich", false},
	{"Kovalik Vadim Valerievich", false},
	{"Korobka Vladislav Vitalievich", false},
	{"Korkh Oleg Sergiyovych", false},
	{"Latysh Oleg Vitalievich", true},
	{"Litvinenko Dmitry Nikolaevich", false},
	{"Nazarova Iryna Oleksandrivna", true},
	{"Obolonik Yan Vitaliyovych", false},
	{"Pestretsov Timofey Vladimirovich", false},
	{"Prudnikov Konstantin Valerievich", false},
	{"Savenko Roman Evgenievich", true},
	{"Sereda Oleksandr Vitaliyovych", false},
	{"Cheryak Danylo Dmytrovych", false},
	{"Shchapov Alexander Ivanovich", true}
};

// Оголосіть масив студентів
std::vector<Student> four_students = {
	{"Boyko Dmitry Yurievich", false},
	{"Boyko Marina Nikolaevna", false},
	{"Borisova Daria Yevhenivna", false},
	{"Volk Daria Maksymivna", false},
	{"Zadorozhnyi Artem Oleksandrovych", false},
	{"Kardash Artem Evgenievich", false},
	{"Klimovsky Alexander Anatolyevich", false},
	{"Kovalik Vadim Valerievich", false},
	{"Korobka Vladislav Vitalievich", false},
	{"Korkh Oleg Sergiyovych", false},
	{"Latysh Oleg Vitalievich", false},
	{"Litvinenko Dmitry Nikolaevich", false},
	{"Nazarova Iryna Oleksandrivna", false},
	{"Obolonik Yan Vitaliyovych", false},
	{"Pestretsov Timofey Vladimirovich", false},
	{"Prudnikov Konstantin Valerievich", false},
	{"Savenko Roman Evgenievich", false},
	{"Sereda Oleksandr Vitaliyovych", false},
	{"Cheryak Danylo Dmytrovych", false},
	{"Shchapov Alexander Ivanovich", false}
};

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// Основна програма 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;

	// Реєстрація класу вікна 
	MyRegisterClass(hInstance);

	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; 		//стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; 		//віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; 			//дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_HAND); 		//визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 	//визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //установка фону
	wcex.lpszMenuName = NULL; 				//визначення меню
	wcex.lpszClassName = szWindowClass; 		//ім’я класу
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); 			//реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, 	// ім’я класу вікна
		szTitle, 				// назва програми
		WS_OVERLAPPEDWINDOW,			// стиль вікна
		CW_USEDEFAULT, 			// положення по Х	
		CW_USEDEFAULT,			// положення по Y	
		800, 			// розмір по Х
		600, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		NULL, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1: {
			TCHAR str0[1024];
			GetDlgItemText(hDlg, IDC_EDIT1, str0, sizeof(str0));
			data[0] = atoi(str0) * 10;
			TCHAR str1[1024];
			GetDlgItemText(hDlg, IDC_EDIT2, str1, sizeof(str1));
			data[1] = atoi(str1) * 10;
			TCHAR str2[1024];
			GetDlgItemText(hDlg, IDC_EDIT3, str2, sizeof(str2));
			data[2] = atoi(str2) * 10;
			TCHAR str3[1024];
			GetDlgItemText(hDlg, IDC_EDIT4, str3, sizeof(str3));
			data[3] = atoi(str3) * 10;
		}
			break;
		case IDCANCEL: {
			EndDialog(hDlg, 0);
		}
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void ShowStudentList(HWND hWnd, int index) {
	std::vector<Student> students;
	switch (index) {
	case 0:
		students = first_students;
		break;
	case 1:
		students = second_students;
		break;
	case 2:
		students = third_students;
		break;
	case 3:
		students = four_students;
		break;
	case 4:
		students = first_students;
		break;
	case 5:
		students = second_students;
		break;
	case 6:
		students = third_students;
		break;
	case 7:
		students = four_students;
		break;
	
	}


	HDC hdc = GetDC(hWnd);

	int yPosition = 240;

	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);

	for (int i = 0; i < students.size(); ++i) {
		
		if (students[i].defended) {
			// Green color for defended students
			SetTextColor(hdc, RGB(0, 200, 0));
		}
		else {
			// Red color for not defended students
			SetTextColor(hdc, RGB(255, 0, 0));
		}

		// Use TextOut to display text
		TextOut(hdc, 10, yPosition, (students[i].name + " - " + (students[i].defended ? "defended" : "not defended")).c_str(), strlen((students[i].name + " - " + (students[i].defended ? "defended" : "not defended")).c_str()));

		
		yPosition += 20;
	}
	
	ReleaseDC(hWnd, hdc);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	

	switch (message)
	{
	case WM_CREATE: { 				//Повідомлення приходить при створенні вікна
		HMENU hMenu = CreateMenu(); 		// Створити меню
		AppendMenu(hMenu, MF_STRING, IDR_MENU1, "Select data");
		SetMenu(hWnd, hMenu); 			//Встановити меню для вікна
	}
		break;


	case WM_COMMAND: 				//Повідомлення від меню
		switch (LOWORD(wParam))
		{
		case IDR_MENU1: {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ENTERVALUE), hWnd, DialogProc);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		}
		break;

	case WM_LBUTTONDOWN: {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);

		for (int i = 0; i < 4; ++i) {
			RECT rect = { 30 + i * 40, 0, 69 + i * 40, 200 };
			RECT rect2 = { 335 + i * 40, 0, 374 + i * 40, 200 };
			if (PtInRect(&rect, pt)) {

				ShowStudentList(hWnd, i);
				break;
			}
			else if (PtInRect(&rect2, pt)) {

				ShowStudentList(hWnd, i + 4);
				break;
			}
		}
	}
					   break;

	case WM_PAINT: { 				//Перемалювати вікно

		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);

		static int x = 200;
		static int y = 100;

		const int countStudents = 19;
		

		HBRUSH originalBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

		for (int i = 0; i < 4; ++i) {
			SelectObject(hdc, originalBrush);

			if ((((countStudents * 2) / 3) * 10) < data[i]) {
				SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 0)));
			}
			else if (((countStudents / 3) * 10) < data[i]) {
				SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 0)));
			}
			else {
				SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
			}

			Rectangle(hdc, 30 + i * 40, 0, 69 + i * 40, 200);
			DeleteObject(SelectObject(hdc, originalBrush));
		}

		// Стовпчикова діаграма

		// Ліва лінія графіка

		MoveToEx(hdc, 20, 0, NULL);
		LineTo(hdc, 20, (y * 2) + 20);

		// Нижня лінія графіка

		MoveToEx(hdc, 0, y * 2, NULL);
		LineTo(hdc, (x - y) * 2, y * 2);


		TCHAR str[10];
		int add = 0;
		for (int i = 0; i < 11; i++)
		{
			MoveToEx(hdc, 20, (y * 2) - add, NULL);
			LineTo(hdc, ((x - y) * 2), (y * 2) - add);

			sprintf_s(str, "%d", add/10);
			TextOut(hdc, 0, (y * 2) - add, str, strlen(str));

			add += 20;
		}

		// Змінна для початкового x1 і x2
		int x1 = 40;
		int x2 = 60;
		for (int i = 1; i < 5; i++)
		{
			Rectangle(hdc, x1, 200 - data[i-1], x2, 200);
			x1 += 40;
			x2 += 40;
			sprintf_s(str, "%d", i);
			TextOut(hdc, x1 - 35, 205, str, strlen(str));

		}

		// Лінійчаста діаграма

		// Ліва лінія графіка

		MoveToEx(hdc, 320, 0, NULL);
		LineTo(hdc, 320, (y * 2) + 20);

		// Нижня лінія графіка
		MoveToEx(hdc, 300, y * 2, NULL);
		LineTo(hdc, ((x - y) * 2) + 300, y * 2);

		add = 0;
		for (int i = 0; i < 11; i++)
		{
			MoveToEx(hdc, 320, (y * 2) - add, NULL);
			LineTo(hdc, ((x - y) * 2) + 320, (y * 2) - add);

			sprintf_s(str, "%d", add / 10);
			TextOut(hdc, 300, 200 - add, str, strlen(str));

			add += 20;
		}
		originalBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

		for (int i = 0; i < 4; ++i) {
			SelectObject(hdc, originalBrush);

			if ((((countStudents * 2) / 3) * 10) < data[i]) {
				SelectObject(hdc, CreateSolidBrush(RGB(0, 255, 0)));
			}
			else if (((countStudents / 3) * 10) < data[i]) {
				SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 0)));
			}
			else {
				SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
			}

			Rectangle(hdc, 335 + i * 40, 0, 374 + i * 40, 200);
			DeleteObject(SelectObject(hdc, originalBrush));
		};

		x1 = 350;

		for (int i = 1; i < 4; i++)
		{
			MoveToEx(hdc, x1, 200 - data[i - 1], NULL);
			LineTo(hdc, x1 + 40, 200 - data[i]);
			x1 += 40;
		}

		x1 = 350;

		for (int i = 1; i < 5; i++)
		{
			// Підписи для вісі X
			sprintf_s(str, "%d", i);
			TextOut(hdc, x1, 205, str, strlen(str));
			x1 += 40;
		}

		EndPaint(hWnd, &ps);
	}
		break;

	case WM_DESTROY: 				//Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}