#include <windows.h> // підключення бібліотеки з функціями API
#include <string>
#include "resource.h"

RECT rectangle;
bool cursorInside;
std::string enteredText;

// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми
LPCTSTR szWindowClass = "Boyko";
LPCTSTR szTitle = "LAB2";

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
    while (GetMessage(&msg, nullptr, 0, 0))
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
    wcex.hIcon = LoadIcon(nullptr, IDI_HAND); 		//визначення іконки
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); 	//визначення курсору
    wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW); //установка фону
    wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); 				//визначення меню
    wcex.lpszClassName = szWindowClass; 		//ім’я класу
    wcex.hIconSm = nullptr;

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
        CW_USEDEFAULT, 			// розмір по Х
        CW_USEDEFAULT, 			// розмір по Y
        nullptr, 					// дескриптор батьківського вікна
        nullptr, 					// дескриптор меню вікна
        hInstance, 				// дескриптор програми
        nullptr); 				// параметри створення.

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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    TEXTMETRIC tm;
    HDC hdc;
    HFONT hFont;
    RECT rt;
    RECT rect;
    POINT pt;
    RECT rc;
    static int repeat = 1;

    switch (message)
    {
    case WM_COMMAND: {
        switch (LOWORD(wParam))
        {
        case ID_PROCESS_CREATEPROCESS: {
            // Створи новий процес який відкриває блокнот
            STARTUPINFO si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);
            CreateProcess("C:\\Windows\\System32\\notepad.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

        }
            break;
        }
    }
        break;
    case WM_KEYDOWN: {

        if (wParam != VK_LEFT && wParam != VK_RIGHT && wParam != VK_UP && wParam != VK_DOWN)
        {
            break;
        }

        GetCursorPos(&pt);

        ScreenToClient(hWnd, &pt);

        switch (wParam)
        {

        case VK_LEFT:
            pt.x -= repeat;
            break;

        case VK_RIGHT:
            pt.x += repeat;
            break;

        case VK_UP:
            pt.y -= repeat;
            break;

        case VK_DOWN:
            pt.y += repeat;
            break;

        default:
            break;
        }

        repeat++;

        GetClientRect(hWnd, &rc);

        if (pt.x >= rc.right)
        {
            pt.x = rc.right - 1;
        }
        else
        {
            if (pt.x < rc.left)
            {
                pt.x = rc.left;
            }
        }

        if (pt.y >= rc.bottom)
            pt.y = rc.bottom - 1;
        else if (pt.y < rc.top)
            pt.y = rc.top;

        ClientToScreen(hWnd, &pt);
        SetCursorPos(pt.x, pt.y);
    }
                   break;

    case WM_KEYUP: {
        repeat = 1;
    }
                 break;

    case WM_MOUSEMOVE: {
        // Check if the cursor is inside the rectangle
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (PtInRect(&rectangle, pt))
        {
            cursorInside = true;
            SetCursorPos(0, 0);
        }
        else
        {
            cursorInside = false;
        }
    }
                     break;

    case WM_CREATE: {
        // Initialize the rectangle position and size
        GetClientRect(hWnd, &rectangle);
        rectangle.left += 50;  // Adjust these values as needed
        rectangle.top += 50;
        rectangle.right = rectangle.left + 200;  // Adjust these values as needed
        rectangle.bottom = rectangle.top + 100;

        // Display information about mouse metrics
        int mouseButtons = GetSystemMetrics(SM_CMOUSEBUTTONS);
        int mousePresent = GetSystemMetrics(SM_MOUSEPRESENT);

        // Display information about icon dimensions
        int minIconWidth = GetSystemMetrics(SM_CXSMICON);
        int maxIconWidth = GetSystemMetrics(SM_CXICON);

        // Display information about screen dimensions
        int width = GetSystemMetrics(SM_CXSCREEN);
        int height = GetSystemMetrics(SM_CYSCREEN);

        // Get the font height and the width of the widest character
        hdc = GetDC(hWnd);
        hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
        SelectObject(hdc, hFont);
        GetTextMetrics(hdc, &tm);
        ReleaseDC(hWnd, hdc);

        // Print the information to the console or display it in some way
        std::string infoMessage = "Mouse Metrics:\n";
        infoMessage += "Mouse Present: " + std::to_string(mousePresent) + "\n";
        infoMessage += "Mouse Buttons: " + std::to_string(mouseButtons) + "\n\n";

        infoMessage += "Icon width:\n";
        infoMessage += "Min Icon Width: " + std::to_string(minIconWidth) + "px\n";
        infoMessage += "Max Icon Width: " + std::to_string(maxIconWidth) + "px\n\n";

        infoMessage += "Screen Metrics:\n";
        infoMessage += "Screen Width: " + std::to_string(width) + "px\n";
        infoMessage += "Screen Height: " + std::to_string(height) + "px\n\n";

        infoMessage += "Font Height: " + std::to_string(tm.tmHeight) + "px\n";
        infoMessage += "Max width character: " + std::to_string(tm.tmMaxCharWidth) + " pixels\n";

        MessageBox(hWnd, infoMessage.c_str(), "System Metrics Information", MB_OK | MB_ICONINFORMATION);

    }
                  break;

    case WM_CHAR: {
        // Handle character input
        enteredText += static_cast<wchar_t>(wParam);

        // Measure the size of the text
        SIZE textSize;
        HDC hdc = GetDC(hWnd);
        GetTextExtentPoint32(hdc, enteredText.c_str(), enteredText.length(), &textSize);
        ReleaseDC(hWnd, hdc);

        // Update rectangle size based on text size
        rectangle.right = rectangle.left + textSize.cx + 10;  // Add some padding

        // Trigger a repaint
        InvalidateRect(hWnd, NULL, TRUE);
    }
                break;

    case WM_PAINT: {
        hdc = BeginPaint(hWnd, &ps);

        // Draw the rectangle
        Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);

        // Display text along the perimeter if the cursor is inside the rectangle
        if (!cursorInside)
        {
            DrawText(hdc, enteredText.c_str(), enteredText.length(), &rectangle, DT_WORDBREAK | DT_EDITCONTROL);
        }

        EndPaint(hWnd, &ps);
    }
                 break;

    case WM_DESTROY:{ 				//Завершення роботи
        // При закритті програми закриваємо вікно стовреного блокноту
        HWND notepad = FindWindow(NULL, "Untitled - Notepad");
        PostMessage(notepad, WM_CLOSE, 0, 0);
        PostQuitMessage(0);
    }
        break;
    default:
        //Обробка повідомлень, які не оброблені користувачем
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}