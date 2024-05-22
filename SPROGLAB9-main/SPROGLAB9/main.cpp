#include <windows.h> // підключення бібліотеки з функціями API
#include <sstream>

// Глобальні змінні:
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = "Kovalik";
LPCTSTR szTitle = "LAB9";

HWND g_hEdit;
HWND g_hButton;

// Попередній опис функцій

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int countSymbolsInRow(char* row);
int countWordsInRow(char* row);
int countVowels(char* row);
int countConsonants(char* row);

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

	g_hEdit = CreateWindow(
        "EDIT", 
        "", 
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		20, 
        20, 
        500, // ширина
        200, // висота
        hWnd, 
        NULL, 
        hInst, 
        NULL
    );

	g_hButton = CreateWindow(
        "BUTTON", 
        "Get Text", 
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		20, 
        230, 
        100, 
        30, 
        hWnd, 
        (HMENU)1, 
        hInst, 
        NULL
    );

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

int countSymbolsInRow(char* row) {
    int count = 0;
    __asm {
        mov ecx, 0
        mov eax, 0
        mov ebx, row
        mov edx, 0
        start_loop:
        mov al, [ebx + ecx]
            cmp al, 0
            je end_loop
            cmp al, ' '
            je skip_space
            cmp al, '\r'
            je skip_space
            cmp al, '\n'
            je skip_space
            inc count
            skip_space :
        inc ecx
            jmp start_loop
            end_loop :
    }
    return count;
}

int countWordsInRow(char* row) {
    int count = 0;
    bool inWord = false;
    __asm {
        mov ecx, 0
        mov eax, 0
        mov ebx, row
        mov edx, 0
        mov inWord, 0
        start_loop:
        mov al, [ebx + ecx]
            cmp al, 0
            je end_loop
            cmp al, ' '
            je skip_space
            cmp al, 'A'
            jl skip_space
            cmp al, 'Z'
            jg check_lowercase
            jmp in_word_check
            check_lowercase :
        cmp al, 'a'
            jl skip_space
            cmp al, 'z'
            jg skip_space
            in_word_check :
        cmp inWord, 1
            je next_char
            mov inWord, 1
            inc count
            jmp next_char
            skip_space :
        cmp inWord, 1
            je end_word
            jmp next_char
            end_word :
        mov inWord, 0
            next_char :
            inc ecx
            jmp start_loop
            end_loop :
    }
    return count;
}

int countVowels(char* row) {
    int count = 0;
    __asm {
        mov ecx, 0
        mov eax, 0
        mov ebx, row
        mov edx, 0
        start_loop:
        mov al, [ebx + ecx]
            cmp al, 0
            je end_loop
            cmp al, 'A'
            je inc_vowel
            cmp al, 'E'
            je inc_vowel
            cmp al, 'I'
            je inc_vowel
            cmp al, 'O'
            je inc_vowel
            cmp al, 'U'
            je inc_vowel
            cmp al, 'Y'
            je inc_vowel
            cmp al, 'a'
            je inc_vowel
            cmp al, 'e'
            je inc_vowel
            cmp al, 'i'
            je inc_vowel
            cmp al, 'o'
            je inc_vowel
            cmp al, 'u'
            je inc_vowel
            cmp al, 'y'
            je inc_vowel
            jmp next_char
            inc_vowel :
        inc count
            next_char :
        inc ecx
            jmp start_loop
            end_loop :
    }
    return count;
}

int countConsonants(char* row) {
    int count = 0;
    __asm {
        mov ecx, 0
        mov eax, 0
        mov ebx, row
        mov edx, 0
        start_loop:
        mov al, [ebx + ecx]
            cmp al, 0
            je end_loop
            cmp al, 'B'
            je inc_vowel
            cmp al, 'C'
            je inc_vowel
            cmp al, 'D'
            je inc_vowel
            cmp al, 'F'
            je inc_vowel
            cmp al, 'G'
            je inc_vowel
            cmp al, 'H'
            je inc_vowel
            cmp al, 'J'
            je inc_vowel
            cmp al, 'K'
            je inc_vowel
            cmp al, 'L'
            je inc_vowel
            cmp al, 'M'
            je inc_vowel
            cmp al, 'N'
            je inc_vowel
            cmp al, 'P'
            je inc_vowel
            cmp al, 'Q'
            je inc_vowel
            cmp al, 'R'
            je inc_vowel
            cmp al, 'S'
            je inc_vowel
            cmp al, 'T'
            je inc_vowel
            cmp al, 'V'
            je inc_vowel
            cmp al, 'W'
            je inc_vowel
            cmp al, 'X'
            je inc_vowel
            cmp al, 'Z'
            je inc_vowel
            cmp al, 'b'
            je inc_vowel
            cmp al, 'c'
            je inc_vowel
            cmp al, 'd'
            je inc_vowel
            cmp al, 'f'
            je inc_vowel
            cmp al, 'g'
            je inc_vowel
            cmp al, 'h'
            je inc_vowel
            cmp al, 'j'
            je inc_vowel
            cmp al, 'k'
            je inc_vowel
            cmp al, 'l'
            je inc_vowel
            cmp al, 'm'
            je inc_vowel
            cmp al, 'n'
            je inc_vowel
            cmp al, 'p'
            je inc_vowel
            cmp al, 'q'
            je inc_vowel
            cmp al, 'r'
            je inc_vowel
            cmp al, 's'
            je inc_vowel
            cmp al, 't'
            je inc_vowel
            cmp al, 'v'
            je inc_vowel
            cmp al, 'w'
            je inc_vowel
            cmp al, 'x'
            je inc_vowel
            cmp al, 'z'
            je inc_vowel
            jmp next_char
            inc_vowel :
        inc count
            next_char :
        inc ecx
            jmp start_loop
            end_loop :
    }
    return count;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;

	switch (message)
	{
	case WM_CREATE: 				//Повідомлення приходить при створенні вікна
		break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // ID of the button
            char text[1000];
            GetWindowText(g_hEdit, text, 1000);
            std::istringstream iss(text);
            std::string row;
            std::string result;
            while (std::getline(iss, row, '\n')) {
                result += "Symbols in row: " + std::to_string(countSymbolsInRow(&row[0])) + "\n";
				result += "Words in row: " + std::to_string(countWordsInRow(&row[0])) + "\n";
            }
            result += "Count vowels in text: " + std::to_string(countVowels(text)) + "\n";
            result += "Count consonants in text: " + std::to_string(countConsonants(text)) + "\n";
            MessageBox(hWnd, result.c_str(), "Result", MB_OK);
        }
        break;

	case WM_PAINT: 				//Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання
		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
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