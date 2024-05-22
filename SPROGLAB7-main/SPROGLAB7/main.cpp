#include <windows.h>
#include <second.h>
#include <stdio.h>

HINSTANCE hInst;
LPCTSTR szWindowClass = "Kovalik";
LPCTSTR szTitle = "LAB7";

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	switch (message) {
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		HMODULE firstDLL = LoadLibrary("SPROGLAB7FIRSTDLL.dll");
		if (firstDLL == nullptr) {
			MessageBox(hWnd, "Error loading firstDLL", "Error", MB_OK | MB_ICONERROR);
		}
		else {
			using power = int(*)(int, int);
			power powerFunc = (power)GetProcAddress(firstDLL, "power");
			if (powerFunc == nullptr) {
				MessageBox(hWnd, "Error loading powerFunc", "Error", MB_OK | MB_ICONERROR);
			}
			else {
				SIZE powerResultSize;
				TCHAR powerResult[256];
				int numberX = rt.right / 200;
				int numberY = rt.bottom / 200;

				TextOut(hdc, 0, 0, "Number X: ", strlen("Number X: "));
				TextOut(hdc, 100, 0, "Number Y: ", strlen("Number Y: "));
				TCHAR numberXStr[256];
				sprintf_s(numberXStr, "%d", numberX);
				TCHAR numberYStr[256];
				sprintf_s(numberYStr, "%d", numberY);
				TextOut(hdc, 70, 0, numberXStr, strlen(numberXStr));
				TextOut(hdc, 170, 0, numberYStr, strlen(numberYStr));

				int powerResultInt = powerFunc(numberX, numberY);
				sprintf_s(powerResult, "%d", powerResultInt);
				GetTextExtentPoint32(hdc, powerResult, strlen(powerResult), &powerResultSize);
				TextOut(hdc, rt.left, rt.bottom - powerResultSize.cy, powerResult, strlen(powerResult));
			}
			using powerOfSums = int(*)(int, int);
			powerOfSums powerOfSumsFunc = (powerOfSums)GetProcAddress(firstDLL, "powerOfSums");
			if (powerOfSumsFunc == nullptr) {
				MessageBox(hWnd, "Error loading powerOfSumsFunc", "Error", MB_OK | MB_ICONERROR);
			}
			else {
				int numberX = rt.right / 200;
				int numberN = rt.bottom / 200;
				for (int i = 1; i <= numberN; i++) {
					if (i == 1) {
						SIZE powerOfSumsResultSize;
						TCHAR powerOfSumsResult[256];
						int powerOfSumsResultInt = powerOfSumsFunc(numberX, i);
						sprintf_s(powerOfSumsResult, "%d", powerOfSumsResultInt);
						GetTextExtentPoint32(hdc, powerOfSumsResult, strlen(powerOfSumsResult), &powerOfSumsResultSize);
						TextOut(hdc, relativePositionX(hWnd, powerOfSumsResultSize), relativePositionY(hWnd, powerOfSumsResultSize, i), powerOfSumsResult, strlen(powerOfSumsResult));
					}
					else if (i == numberN) {
						SIZE powerOfSumsResultSize;
						TCHAR powerOfSumsResult[256];
						int powerOfSumsResultInt = powerOfSumsFunc(numberX, i);
						sprintf_s(powerOfSumsResult, "%d", powerOfSumsResultInt);
						GetTextExtentPoint32(hdc, powerOfSumsResult, strlen(powerOfSumsResult), &powerOfSumsResultSize);
						TextOut(hdc, relativePositionX(hWnd, powerOfSumsResultSize), relativePositionY(hWnd, powerOfSumsResultSize, i), powerOfSumsResult, strlen(powerOfSumsResult));
					}
					else {
						SIZE powerOfSumsResultSize;
						TCHAR powerOfSumsResult[256];
						int powerOfSumsResultInt = powerOfSumsFunc(numberX, i);
						sprintf_s(powerOfSumsResult, "%d", powerOfSumsResultInt);
						GetTextExtentPoint32(hdc, powerOfSumsResult, strlen(powerOfSumsResult), &powerOfSumsResultSize);
						TextOut(hdc, relativePositionX(hWnd, powerOfSumsResultSize), relativePositionY(hWnd, powerOfSumsResultSize, i), powerOfSumsResult, strlen(powerOfSumsResult));
					}
				}
			}
		}
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
