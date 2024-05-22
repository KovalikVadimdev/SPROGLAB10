#include <windows.h>
#include <fstream>
#include <string>
#include "resource.h"

HINSTANCE hInst;
LPCTSTR szWindowClass = "Kovalik";
LPCTSTR szTitle = "LAB6";
char* globalBuffer = nullptr;

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

void OpenFile(HWND hWnd, HWND hEdit) {
	OPENFILENAME ofn;
	char szFile[256];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.hwndOwner = hWnd;
	ofn.nFilterIndex = 1;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lStructSize = sizeof(ofn);
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrTitle = "Select a file to open";
	ofn.lpstrFilter = "Text Files\0*.TXT\0All Files\0*.*\0";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;


	if (GetOpenFileName(&ofn) == TRUE) {
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE) {
			DWORD dwFileSize = GetFileSize(hFile, NULL);
			globalBuffer = (char*)GlobalAlloc(GPTR, dwFileSize + 1);
			DWORD dwRead;
			if (ReadFile(hFile, globalBuffer, dwFileSize, &dwRead, NULL)) {
				globalBuffer[dwFileSize] = 0;
				HDC hdc = GetDC(hWnd);
				RECT rcClient;
				GetClientRect(hWnd, &rcClient);
				DrawText(hdc, globalBuffer, -1, &rcClient, DT_WORDBREAK | DT_EDITCONTROL);
				ReleaseDC(hWnd, hdc);
			}
			GlobalFree(globalBuffer);
			CloseHandle(hFile);
		}
		else {
			MessageBox(hWnd, "Failed to open file!", "Error", MB_OK | MB_ICONERROR);
		}
	}
}

void CopyTextToReadme() {
	std::ofstream outFile("Readme.txt");
	if (outFile.is_open()) {
		outFile << globalBuffer;
		outFile.close();
		ShellExecute(NULL, "open", "Readme.txt", NULL, NULL, SW_SHOWNORMAL);
	}
	else {
		MessageBox(NULL, "Failed to open file!", "Error", MB_OK | MB_ICONERROR);
	}
}

void DeleteFilesWithExtension(HWND hWnd, const std::string& extension) {
	std::string searchPattern = "*." + extension;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(searchPattern.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::string filename = FindFileData.cFileName;
			if (filename != "." && filename != "..") {
				std::string filepath = filename;
				if (DeleteFile(filepath.c_str())) {
					MessageBox(hWnd, (filename + " deleted successfully!").c_str(), "Success", MB_OK | MB_ICONINFORMATION);
				}
				else {
					MessageBox(hWnd, (filename + " deletion failed!").c_str(), "Error", MB_OK | MB_ICONERROR);
				}
			}
		} while (FindNextFile(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
	else {
		MessageBox(hWnd, ("No files with extension ." + extension + " found!").c_str(), "Info", MB_OK | MB_ICONINFORMATION);
	}
}

void DeleteHiddenFiles(HWND hWnd) {
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile("*.*", &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			std::string filename = FindFileData.cFileName;
			if (filename != "." && filename != ".." && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
				std::string filepath = filename;
				if (DeleteFile(filepath.c_str())) {
					MessageBox(hWnd, (filename + " deleted successfully!").c_str(), "Success", MB_OK | MB_ICONINFORMATION);
				}
				else {
					MessageBox(hWnd, (filename + " deletion failed!").c_str(), "Error", MB_OK | MB_ICONERROR);
				}
			}
		} while (FindNextFile(hFind, &FindFileData) != 0);
		FindClose(hFind);
	}
	else {
		MessageBox(hWnd, "No hidden files found!", "Info", MB_OK | MB_ICONINFORMATION);
	}
}

void InformationFile(HWND hWnd) {

	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = NULL;
	ofn.lpstrTitle = NULL;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn)) {
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile != INVALID_HANDLE_VALUE) {
			BY_HANDLE_FILE_INFORMATION fileInfo;
			if (GetFileInformationByHandle(hFile, &fileInfo)) {
				std::string info = "File Information:\n";
				info += "File name: " + std::string(ofn.lpstrFile) + "\n";
				if (fileInfo.nFileSizeLow > 1024) {
					info += "File size: " + std::to_string(fileInfo.nFileSizeLow / 1024) + " KB\n";
				}
				else {
					info += "File size: " + std::to_string(fileInfo.nFileSizeLow) + " bytes\n";
				}
				info += "File attributes: " + std::to_string(fileInfo.dwFileAttributes) + "\n";
				MessageBox(hWnd, info.c_str(), "File Information", MB_OK | MB_ICONINFORMATION);
			}
			else {
				MessageBox(hWnd, "Failed to get file information!", "Error", MB_OK | MB_ICONERROR);
			}
			CloseHandle(hFile);
		}
		else {
			MessageBox(hWnd, "Failed to open file!", "Error", MB_OK | MB_ICONERROR);
		}
	}
}

INT_PTR CALLBACK FunctionCreateFile(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG: {
		HMENU hMenu = CreateMenu();
		HMENU hSubMenu = CreatePopupMenu();
		HMENU hSubMenu2 = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "Menu");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_CREATEFILE, "Create file");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_OPENFILE, "Open file");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_COPYTEXT, "Copy text");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu2, "Delete");
		AppendMenu(hSubMenu2, MF_STRING, ID_MENU_DELETE_EXE, "Delete .exe files");
		AppendMenu(hSubMenu2, MF_STRING, ID_MENU_DELETE_TXT, "Delete .txt files");
		AppendMenu(hSubMenu2, MF_STRING, ID_MENU_DELETE_HIDDEN, "Delete hidden files");
		AppendMenu(hSubMenu2, MF_STRING, ID_DELETE_INFORMATIONONFILE, "Information on file");
		SetMenu(hDlg, hMenu);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_CREATE_BUTTON: {
			TCHAR szFileName[MAX_PATH];
			GetDlgItemText(hDlg, IDC_FILE_NAME, szFileName, MAX_PATH);
			if (GetFileAttributes(szFileName) != INVALID_FILE_ATTRIBUTES) {
				MessageBox(hDlg, "File already exists. Please choose a different name.", "File Exists", MB_OK | MB_ICONEXCLAMATION);
				SetDlgItemText(hDlg, IDC_FILE_NAME, "");
			}
			else {
				HANDLE hFile = CreateFile(
					szFileName,
					GENERIC_WRITE,
					0,
					NULL,
					CREATE_NEW,
					FILE_ATTRIBUTE_NORMAL,
					NULL
				);
				if (hFile != INVALID_HANDLE_VALUE) {
					MessageBox(hDlg, "File created successfully!", "Success", MB_OK | MB_ICONINFORMATION);
					CloseHandle(hFile);
				}
				else {
					MessageBox(hDlg, "Failed to create file!", "Error", MB_OK | MB_ICONERROR);
				}
				EndDialog(hDlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		
		case ID_MENU_DELETE_EXE: {
			DeleteFilesWithExtension(hDlg, "exe");
			break;
		}
		case ID_MENU_DELETE_TXT: {
			DeleteFilesWithExtension(hDlg, "txt");
			break;
		}
		case ID_MENU_DELETE_HIDDEN: {
			DeleteHiddenFiles(hDlg);
			break;
		}
		case ID_DELETE_INFORMATIONONFILE: {
			InformationFile(hDlg);
			break;
		}
		case IDC_CLOSE_BUTTON: {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			}
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	static HWND hEdit;
	switch (message) {
	case WM_CREATE: {
		HMENU hMenu = CreateMenu();
		HMENU hSubMenu = CreatePopupMenu();
		HMENU hSubMenu2 = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "Menu");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_CREATEFILE, "Create file");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_OPENFILE, "Open file");
		AppendMenu(hSubMenu, MF_STRING, ID_MENU_COPYTEXT, "Copy text");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu2, "Delete");
		AppendMenu(hSubMenu2, MF_STRING, ID_MENU_DELETE_EXE, "Delete .exe files");
		AppendMenu(hSubMenu2, MF_STRING, ID_MENU_DELETE_TXT, "Delete .txt files");
		AppendMenu(hSubMenu2, MF_STRING, ID_MENU_DELETE_HIDDEN, "Delete hidden files");
		AppendMenu(hSubMenu2, MF_STRING, ID_DELETE_INFORMATIONONFILE, "Information on file");
		SetMenu(hWnd, hMenu);

		break;
	}

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case ID_MENU_CREATEFILE: {
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, FunctionCreateFile);
			break;
		}
		case ID_MENU_OPENFILE: {
			OpenFile(hWnd, hEdit);
			break;
		}
		case ID_MENU_COPYTEXT: {
			CopyTextToReadme();
			break;
		}
		case ID_MENU_DELETE_EXE: {
			DeleteFilesWithExtension(hWnd, "exe");
			break;
		}
		case ID_MENU_DELETE_TXT: {
			DeleteFilesWithExtension(hWnd, "txt");
			break;
		}
		case ID_MENU_DELETE_HIDDEN: {
			DeleteHiddenFiles(hWnd);
			break;
		}
		case ID_DELETE_INFORMATIONONFILE: {
			InformationFile(hWnd);
			break;
		}
		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		}
		break;
	}

	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		if (globalBuffer != nullptr) {
			RECT rcClient;
			GetClientRect(hWnd, &rcClient);
			DrawText(hdc, globalBuffer, -1, &rcClient, DT_WORDBREAK | DT_EDITCONTROL);
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
