#include <windows.h>
#include <stdio.h>
#include "resource.h"

HINSTANCE hInst;
HWND g_hEdit;
HWND g_hButton;
LPCTSTR szWindowClass = "Kovalik";
LPCTSTR szTitle = "LAB8";

// Глобальні змінні для збереження значень флагів
DWORD flags_before;
DWORD flags_after;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_HAND);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	HWND hWnd;
	hInst = hInstance;
	hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd) {
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

char* intToBinaryString(int num, char* binaryString, char* binaryStringleft)
{
	int flags_before = 0;
	int beforeCF = 0;
	int beforePF = 0;
	int beforeAF = 0;
	int beforeZF = 0;
	int beforeSF = 0;
	int beforeOF = 0;

	int flags_after = 0;
	int afterCF = 0;
	int afterPF = 0;
	int afterAF = 0;
	int afterZF = 0;
	int afterSF = 0;
	int afterOF = 0;

	__asm {
		mov eax, num
		mov edi, binaryString 
		mov byte ptr[edi + 32], 0
		mov ecx, 32
		loop_start:
		shr eax, 1
			jnc zero_bit
			mov byte ptr[edi + 31], '1'
			jmp next_bit
			zero_bit :
		mov byte ptr[edi + 31], '0'
			next_bit :
			dec edi 
			loop loop_start

			pushfd
			pop flags_before
			mov eax, flags_before
			and eax, 1
			mov beforeCF, eax
			mov eax, flags_before
			shr eax, 2
			and eax, 1
			mov beforePF, eax
			mov eax, flags_before
			shr eax, 4
			and eax, 1
			mov beforeAF, eax
			mov eax, flags_before
			shr eax, 6
			and eax, 1
			mov beforeZF, eax
			mov eax, flags_before
			shr eax, 7
			and eax, 1 
			mov beforeSF, eax
			mov eax, flags_before
			shr eax, 11
			and eax, 1
			mov beforeOF, eax


			mov eax, num
			add eax, 33
			mov edi, binaryStringleft
			mov byte ptr[edi + 32], 0
			mov ecx, 32
			loop_startleft:
			shr eax, 1
			jnc zero_bitleft
			mov byte ptr[edi + 31], '1'
			jmp next_bitleft
			zero_bitleft :
			mov byte ptr[edi + 31], '0'
			next_bitleft :
			dec edi
			loop loop_startleft

			pushfd
			pop flags_after
			mov eax, flags_after
			and eax, 1
			mov afterCF, eax
			mov eax, flags_after
			shr eax, 2
			and eax, 1
			mov afterPF, eax
			mov eax, flags_after
			shr eax, 4
			and eax, 1
			mov afterAF, eax
			mov eax, flags_after
			shr eax, 6
			and eax, 1
			mov afterZF, eax
			mov eax, flags_after
			shr eax, 7
			and eax, 1
			mov afterSF, eax
			mov eax, flags_after
			shr eax, 11
			and eax, 1
			mov afterOF, eax
	}
	
	char flags[100];
	sprintf_s(flags, "CF=%d PF=%d AF=%d ZF=%d SF=%d OF=%d", beforeCF, beforePF, beforeAF, beforeZF, beforeSF, beforeOF);
	TextOut(GetDC(g_hEdit), 5, 120, flags, strlen(flags));
	TextOut(GetDC(g_hEdit), 5, 140, binaryStringleft, 32);
	sprintf_s(flags, "CF=%d PF=%d AF=%d ZF=%d SF=%d OF=%d", afterCF, afterPF, afterAF, afterZF, afterSF, afterOF);
	TextOut(GetDC(g_hEdit), 5, 160, flags, strlen(flags));
	return binaryString;
}

void ConvertAndDisplayBinary() {
	char inputText[100];
	GetWindowText(g_hEdit, inputText, 100);

	int num = atoi(inputText);
	// Convert the number to binary string
	char binaryString[33];
	char binaryStringleft[33];

	// Display the result in a message box
	TextOut(GetDC(g_hEdit), 5, 100, intToBinaryString(num, binaryString, binaryStringleft), 32);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	switch (message) {
	case WM_CREATE: {
		// Create a text edit control
		g_hEdit = CreateWindow(
			"EDIT",
			"",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			5,
			30,
			200,
			25,
			hWnd,
			NULL,
			hInst,
			NULL
		);

		// Create a button
		g_hButton = CreateWindow(
			"BUTTON",
			"Convert to Binary",
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			5,
			60,
			200,
			25,
			hWnd,
			(HMENU)ID_B_BUTTON,
			hInst,
			NULL
		);

		break;
	}

	case WM_COMMAND: {
		if (LOWORD(wParam) == ID_B_BUTTON) {
			ConvertAndDisplayBinary();
		}
		break;
	}

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		char text[100] = "Enter number";
		int len = strlen(text);
		TextOut(hdc, 55, 5, text, len);
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	default: {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}