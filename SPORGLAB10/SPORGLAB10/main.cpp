#include <windows.h> // підключення бібліотеки з функціями API
#include "resource.h"
#include <stdio.h>
// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "123";

// Попередній опис функцій

STARTUPINFO si1 = { sizeof(si1) };
PROCESS_INFORMATION pi1;

STARTUPINFO si2 = { sizeof(si2) };
PROCESS_INFORMATION pi2;

STARTUPINFO si3 = { sizeof(si3) };
PROCESS_INFORMATION pi3;

STARTUPINFO si4 = { sizeof(si4) };
PROCESS_INFORMATION pi4;

STARTUPINFO si5 = { sizeof(si5) };
PROCESS_INFORMATION pi5;

STARTUPINFO si6 = { sizeof(si6) };
PROCESS_INFORMATION pi6;

STARTUPINFO si7 = { sizeof(si7) };
PROCESS_INFORMATION pi7;

STARTUPINFO si8 = { sizeof(si8) };
PROCESS_INFORMATION pi8;

STARTUPINFO si9 = { sizeof(si9) };
PROCESS_INFORMATION pi9;


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
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); 				//визначення меню
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
        1920, 			// розмір по Х
        1000, 			// розмір по Y
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

void CreateLabComboBox(HWND hWndParent, int x, int y)
{
    HWND hComboBox = CreateWindowEx(0, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
        x, y, 150, 200, hWndParent, NULL, GetModuleHandle(NULL), NULL);

    // Додаємо елементи випадаючого списку
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB1");
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB2");
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB3");
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB4");
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB5");
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB6");
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB7");
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB8");
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"LAB9");
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
}

bool LaunchProcess(const char* exePath, const char* windowTitle, HWND hWnd, int x, int y, int width, int height)
{
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (CreateProcess(exePath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        WaitForInputIdle(pi.hProcess, INFINITE);
        HWND hChildWnd = FindWindow(NULL, windowTitle);
        if (hChildWnd)
        {
            SetParent(hChildWnd, hWnd);
            MoveWindow(hChildWnd, x, y, width, height, TRUE);
            InvalidateRect(hChildWnd, NULL, TRUE);
            return true;
        }
    }
    return false;
}


LRESULT CALLBACK ChildWndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    static HWND hChildWnd = NULL;

    switch (message)
    {
    case WM_ERASEBKGND:
    {
        hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
        return 1;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);

        if (wmEvent == CBN_SELCHANGE)
        {
            HWND hComboBox = (HWND)lParam;
            int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

            const char* exePaths[] = {
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB1-main\\x64\\Debug\\SPROGLAB1FINAL.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB2-main\\x64\\Debug\\SPROGLAB2.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB3-main\\x64\\Debug\\SPROGLAB32.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB4-main\\x64\\Debug\\SPROGLAB4.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB5-main\\x64\\Debug\\SPROGLAB5.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB6-main\\x64\\Debug\\SPROGLAB6.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB7-main\\x64\\Debug\\SPROGLAB7.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB8-main\\Debug\\SPROGLAB8.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB9-main\\Debug\\SPROGLAB9.exe"
            };

            const char* windowTitles[] = { "LAB1", "LAB2", "LAB3", "LAB4", "LAB5", "LAB6", "LAB7", "LAB8", "LAB9" };

            if (selectedIndex >= 0 && selectedIndex <= 9)
            {
                LaunchProcess(exePaths[selectedIndex], windowTitles[selectedIndex], hWnd, 10, 10, 800, 600);
            }
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ChildWndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    static HWND hChildWnd = NULL;

    switch (message)
    {
    case WM_ERASEBKGND:
    {
        hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
        return 1;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);

        if (wmEvent == CBN_SELCHANGE)
        {
            HWND hComboBox = (HWND)lParam;
            int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

            const char* exePaths[] = {
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB1-main\\x64\\Debug\\SPROGLAB1FINAL.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB2-main\\x64\\Debug\\SPROGLAB2.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB3-main\\x64\\Debug\\SPROGLAB32.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB4-main\\x64\\Debug\\SPROGLAB4.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB5-main\\x64\\Debug\\SPROGLAB5.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB6-main\\x64\\Debug\\SPROGLAB6.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB7-main\\x64\\Debug\\SPROGLAB7.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB8-main\\Debug\\SPROGLAB8.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB9-main\\Debug\\SPROGLAB9.exe"
            };

            const char* windowTitles[] = { "LAB1", "LAB2", "LAB3", "LAB4", "LAB5", "LAB6", "LAB7", "LAB8", "LAB9" };

            if (selectedIndex >= 0 && selectedIndex < _countof(exePaths))
            {
                LaunchProcess(exePaths[selectedIndex], windowTitles[selectedIndex], hWnd, 10, 10, 800, 600);
            }
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ChildWndProc3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    static HWND hChildWnd = NULL;

    switch (message)
    {
    case WM_ERASEBKGND:
    {
        hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
        return 1;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);

        if (wmEvent == CBN_SELCHANGE)
        {
            HWND hComboBox = (HWND)lParam;
            int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

            const char* exePaths[] = {
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB1-main\\x64\\Debug\\SPROGLAB1FINAL.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB2-main\\x64\\Debug\\SPROGLAB2.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB3-main\\x64\\Debug\\SPROGLAB32.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB4-main\\x64\\Debug\\SPROGLAB4.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB5-main\\x64\\Debug\\SPROGLAB5.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB6-main\\x64\\Debug\\SPROGLAB6.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB7-main\\x64\\Debug\\SPROGLAB7.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB8-main\\Debug\\SPROGLAB8.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB9-main\\Debug\\SPROGLAB9.exe"
            };

            const char* windowTitles[] = { "LAB1", "LAB2", "LAB3", "LAB4", "LAB5", "LAB6", "LAB7", "LAB8", "LAB9" };

            if (selectedIndex >= 0 && selectedIndex < _countof(exePaths))
            {
                LaunchProcess(exePaths[selectedIndex], windowTitles[selectedIndex], hWnd, 10, 10, 800, 600);
            }
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK ChildWndProc4(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    static HWND hChildWnd = NULL;

    switch (message)
    {
    case WM_ERASEBKGND:
    {
        hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
        return 1;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);

        if (wmEvent == CBN_SELCHANGE)
        {
            HWND hComboBox = (HWND)lParam;
            int selectedIndex = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);

            const char* exePaths[] = {
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB1-main\\x64\\Debug\\SPROGLAB1FINAL.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB2-main\\x64\\Debug\\SPROGLAB2.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB3-main\\x64\\Debug\\SPROGLAB32.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB4-main\\x64\\Debug\\SPROGLAB4.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB5-main\\x64\\Debug\\SPROGLAB5.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB6-main\\x64\\Debug\\SPROGLAB6.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB7-main\\x64\\Debug\\SPROGLAB7.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB8-main\\Debug\\SPROGLAB8.exe",
                    "C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB9-main\\Debug\\SPROGLAB9.exe"
            };

            const char* windowTitles[] = { "LAB1", "LAB2", "LAB3", "LAB4", "LAB5", "LAB6", "LAB7", "LAB8", "LAB9" };

            if (selectedIndex >= 0 && selectedIndex < _countof(exePaths))
            {
                LaunchProcess(exePaths[selectedIndex], windowTitles[selectedIndex], hWnd, 10, 10, 800, 600);
            }
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rt;
    static HWND childWnd1 = NULL;
    static HWND childWnd2 = NULL;
    static HWND childWnd3 = NULL;
    static HWND childWnd4 = NULL;
    HWND hComboBox1 = NULL;
    HWND hComboBox2 = NULL;
    HWND hComboBox3 = NULL;
    HWND hComboBox4 = NULL;
    static HWND hChildWnd1 = NULL;
    static HWND hChildWnd2 = NULL;
    static HWND hChildWnd3 = NULL;
    static HWND hChildWnd4 = NULL;
    static HWND hChildWnd5 = NULL;
    static HWND hChildWnd6 = NULL;
    static HWND hChildWnd7 = NULL;
    static HWND hChildWnd8 = NULL;
    static HWND hChildWnd9 = NULL;
    RECT mainRect;
    int mainWidth, mainHeight;
    switch (message)
    {
    case WM_CREATE:

        break;

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {

        case ID_MENU_LAB1: {

            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB1-main\\x64\\Debug\\SPROGLAB1FINAL.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi1.hProcess, INFINITE);
                hChildWnd1 = FindWindow(NULL, "LAB1");
                if (hChildWnd1)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd1, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd1, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;
        case ID_MENU_LAB2: {
            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB2-main\\x64\\Debug\\SPROGLAB2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi2.hProcess, INFINITE);
                hChildWnd2 = FindWindow(NULL, "LAB2");
                if (hChildWnd2)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd2, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd2, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;
        case ID_MENU_LAB3: {
            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB3-main\\x64\\Debug\\SPROGLAB32.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si3, &pi3))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi3.hProcess, INFINITE);
                hChildWnd3 = FindWindow(NULL, "LAB3");
                if (hChildWnd3)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd3, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd3, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;
        case ID_MENU_LAB4: {
            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB4-main\\x64\\Debug\\SPROGLAB4.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si4, &pi4))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi4.hProcess, INFINITE);
                hChildWnd4 = FindWindow(NULL, "LAB4");
                if (hChildWnd4)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd4, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd4, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;
        case ID_MENU_LAB5: {
            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB5-main\\x64\\Debug\\SPROGLAB5.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si5, &pi5))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi5.hProcess, INFINITE);
                hChildWnd5 = FindWindow(NULL, "LAB5");
                if (hChildWnd5)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd5, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd5, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;
        case ID_MENU_LAB6: {
            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB6-main\\x64\\Debug\\SPROGLAB6.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si6, &pi6))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi6.hProcess, INFINITE);
                hChildWnd6 = FindWindow(NULL, "LAB6");
                if (hChildWnd6)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd6, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd6, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;
        case ID_MENU_LAB7: {
            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB7-main\\x64\\Debug\\SPROGLAB7.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si7, &pi7))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi7.hProcess, INFINITE);
                hChildWnd7 = FindWindow(NULL, "LAB7");
                if (hChildWnd7)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd7, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd7, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;
        case ID_MENU_LAB8: {
            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB8-main\\Debug\\SPROGLAB8.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si8, &pi8))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi8.hProcess, INFINITE);
                hChildWnd8 = FindWindow(NULL, "LAB8");
                if (hChildWnd8)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd8, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd8, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;
        case ID_MENU_LAB9: {
            if (CreateProcess("C:\\Users\\Kovalik\\source\\repos\\SPROGLAB10\\SPROGLAB9-main\\Debug\\SPROGLAB9.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si9, &pi9))
            {
                // Отримуємо дескриптор головного вікна запущеної програми
                WaitForInputIdle(pi9.hProcess, INFINITE);
                hChildWnd9 = FindWindow(NULL, "LAB9");
                if (hChildWnd9)
                {
                    // Встановлюємо вікно дочірнім вікном для нашого основного вікна
                    SetParent(hChildWnd9, hWnd);
                    // Розміщуємо вікно іншої програми в потрібній області нашого основного вікна
                    MoveWindow(hChildWnd9, 10, 10, 800, 600, TRUE);
                }
            }
        }
                         break;

        case ID_MENU_SWITCH: {
            DestroyWindow(hChildWnd1);
            DestroyWindow(hChildWnd2);
            DestroyWindow(hChildWnd3);
            DestroyWindow(hChildWnd4);
            DestroyWindow(hChildWnd5);
            DestroyWindow(hChildWnd6);
            DestroyWindow(hChildWnd7);
            DestroyWindow(hChildWnd8);
            DestroyWindow(hChildWnd9);

            // Отримуємо розміри основного вікна
            GetClientRect(hWnd, &mainRect);
            // Створюємо чотири дочірні вікна, кожне з яких займає рівну область основного вікна
            childWnd1 = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE, 0, 0, mainRect.right / 2, mainRect.bottom / 2, hWnd, NULL, GetModuleHandle(NULL), NULL);
            SetWindowLongPtr(childWnd1, GWLP_WNDPROC, (LONG_PTR)ChildWndProc1);
            hComboBox1 = CreateWindowEx(0, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 10, 150, 200, childWnd1, NULL, GetModuleHandle(NULL), NULL);
            // Додаємо елементи випадаючого списку
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB1");
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB2");
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB3");
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB4");
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB5");
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB6");
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB7");
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB8");
            SendMessage(hComboBox1, CB_ADDSTRING, 0, (LPARAM)"LAB9");
            SendMessage(hComboBox1, CB_SETCURSEL, 0, 0);

            childWnd2 = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE, mainRect.right / 2, 0, mainRect.right / 2, mainRect.bottom / 2, hWnd, NULL, GetModuleHandle(NULL), NULL);
            SetWindowLongPtr(childWnd2, GWLP_WNDPROC, (LONG_PTR)ChildWndProc2);
            hComboBox2 = CreateWindowEx(0, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 10, 150, 200, childWnd2, NULL, GetModuleHandle(NULL), NULL);

            // Додаємо елементи випадаючого списку
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB1");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB2");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB3");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB4");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB5");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB6");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB7");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB8");
            SendMessage(hComboBox2, CB_ADDSTRING, 0, (LPARAM)"LAB9");
            SendMessage(hComboBox2, CB_SETCURSEL, 0, 0);

            childWnd3 = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE, 0, mainRect.bottom / 2, mainRect.right / 2, mainRect.bottom / 2, hWnd, NULL, GetModuleHandle(NULL), NULL);
            SetWindowLongPtr(childWnd3, GWLP_WNDPROC, (LONG_PTR)ChildWndProc3);
            hComboBox3 = CreateWindowEx(0, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 10, 150, 200, childWnd3, NULL, GetModuleHandle(NULL), NULL);

            // Додаємо елементи випадаючого списку
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB1");
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB2");
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB3");
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB4");
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB5");
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB6");
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB7");
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB8");
            SendMessage(hComboBox3, CB_ADDSTRING, 0, (LPARAM)"LAB9");
            SendMessage(hComboBox3, CB_SETCURSEL, 0, 0);

            childWnd4 = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE, mainRect.right / 2, mainRect.bottom / 2, mainRect.right / 2, mainRect.bottom / 2, hWnd, NULL, GetModuleHandle(NULL), NULL);
            SetWindowLongPtr(childWnd4, GWLP_WNDPROC, (LONG_PTR)ChildWndProc4);
            CreateLabComboBox(childWnd4, 10, 10); // Додаємо випадаюче вікно до дочірнього вікна 4
            hComboBox4 = CreateWindowEx(0, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, 10, 10, 150, 200, childWnd4, NULL, GetModuleHandle(NULL), NULL);

            // Додаємо елементи випадаючого списку
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB1");
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB2");
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB3");
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB4");
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB5");
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB6");
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB7");
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB8");
            SendMessage(hComboBox4, CB_ADDSTRING, 0, (LPARAM)"LAB9");
            SendMessage(hComboBox4, CB_SETCURSEL, 0, 0);


            break;
        }

            case ID_MENU_RETURN: {
                if (childWnd1) DestroyWindow(childWnd1);
                if (childWnd2) DestroyWindow(childWnd2);
                if (childWnd3) DestroyWindow(childWnd3);
                if (childWnd4) DestroyWindow(childWnd4);
                if (hComboBox1) DestroyWindow(hComboBox1);
                if (hComboBox2) DestroyWindow(hComboBox2);
                if (hComboBox3) DestroyWindow(hComboBox3);
                if (hComboBox4) DestroyWindow(hComboBox4);
            }
                break;
        }
    }
        break;
    case WM_PAINT: 				//Перемалювати вікно
        hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
        // Оновлення дочірніх вікон
        EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
        break;

    case WM_DESTROY:
        // Закриваємо дочірні вікна при закритті основного вікна
        if (childWnd1) DestroyWindow(childWnd1);
        if (childWnd2) DestroyWindow(childWnd2);
        if (childWnd3) DestroyWindow(childWnd3);
        if (childWnd4) DestroyWindow(childWnd4);
        PostQuitMessage(0);
        break;
    default:
        //Обробка повідомлень, які не оброблені користувачем
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}