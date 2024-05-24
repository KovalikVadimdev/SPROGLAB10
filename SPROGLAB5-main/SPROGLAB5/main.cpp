#include <windows.h> // підключення бібліотеки з функціями API
#include <stdio.h>
#include "resource.h"

// Глобальні змінні:
HINSTANCE hInst; // Дескриптор програми
LPCTSTR szWindowClass = "Kovalik";
LPCTSTR szTitle = "LAB5";

HANDLE hThread = NULL;
DWORD threadId = 0;
BOOL isMouseButtonDown = FALSE;

// Попередній опис функцій

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
	wcex.style = CS_HREDRAW | CS_VREDRAW; // стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc;  // віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;                          // дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_HAND);               // визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);          // визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); // установка фону
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);                            // визначення меню
	wcex.lpszClassName = szWindowClass;                  // ім’я класу
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex); // реєстрація класу вікна
}

// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;                       // зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass,       // ім’я класу вікна
		szTitle,             // назва програми
		WS_OVERLAPPEDWINDOW, // стиль вікна
		CW_USEDEFAULT,       // положення по Х
		CW_USEDEFAULT,       // положення по Y
		800,       // розмір по Х
		600,       // розмір по Y
		NULL,                // дескриптор батьківського вікна
		NULL,                // дескриптор меню вікна
		hInstance,           // дескриптор програми
		NULL);               // параметри створення.

	if (!hWnd) // Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); // Показати вікно
	UpdateWindow(hWnd);         // Оновити вікно
	return TRUE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	HWND hWnd = (HWND)lpParam;
	POINT pt;
	int counter = 0;
	while (GetCursorPos(&pt))
	{
		ScreenToClient(hWnd, &pt);
		HDC hdc = GetDC(hWnd);
		char buffer[10];
		sprintf_s(buffer, "%d", counter++);
		TextOut(hdc, pt.x, pt.y, buffer, strlen(buffer));
		ReleaseDC(hWnd, hdc);
		Sleep(100);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{

	case WM_COMMAND: // Обробка меню
	{
		switch (LOWORD(wParam))
		{
			case ID_CREATEPROCESS: {
				STARTUPINFO cif;
				PROCESS_INFORMATION pi;
				ZeroMemory(&cif, sizeof(STARTUPINFO));
				cif.cb = sizeof(STARTUPINFO);
				ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
				// open notepad
				CreateProcess("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi);
				break;
			}
			case ID_STOPPROCESS: {
				HWND hwnd = FindWindow(NULL, "Untitled - Notepad");
				if (hwnd != NULL)
				{
					SendMessage(hwnd, WM_CLOSE, 0, 0);
				}
				else {
					MessageBox(hWnd, "There is no such process. Please launch your editor first", "Error", MB_OK);
				}
				break;
			}
			case ID_STOPWORKING: {
				HWND hwnd = FindWindow(NULL, "Untitled - Notepad");
				if (hwnd != NULL)
				{
					SendMessage(hwnd, WM_CLOSE, 0, 0);
				}
				// Завершити роботу програми
				PostQuitMessage(0);
				break;
			}
		}
		break;
	}
		
	case WM_LBUTTONDOWN:
	{
		if (!isMouseButtonDown) // Якщо кнопка миші була відпущена
		{
			isMouseButtonDown = TRUE; // Встановити прапорець, що кнопка миші натиснута
			if (!hThread) // Якщо потік не створений, створити його
			{
				hThread = CreateThread(NULL, 0, ThreadProc, (LPVOID)hWnd, 0, &threadId); // Створення потоку
			}
		}
		else // Якщо кнопка миші була натиснута знову
		{
			if (hThread) // Якщо потік створений, зупинити його
			{
				TerminateThread(hThread, 0);
				CloseHandle(hThread);
				hThread = NULL;
			}
			isMouseButtonDown = FALSE;
		}
		break;
	}

	case WM_PAINT: // Перемалювати вікно
	{
		hdc = BeginPaint(hWnd, &ps); // Почати графічний вивід
		GetClientRect(hWnd, &rt);    // Область вікна для малювання
		EndPaint(hWnd, &ps); // Закінчити графічний вивід
		break;
	}

	case WM_DESTROY: // Завершення роботи
	{
		PostQuitMessage(0);
		break;
	}
	default:
	{
		// Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}