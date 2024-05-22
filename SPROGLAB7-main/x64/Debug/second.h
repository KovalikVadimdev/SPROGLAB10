#pragma once
#include <windows.h>

#ifdef SECONDDLL_EXPORTS
#define SECONDDLL_API __declspec(dllexport)
#else
#define SECONDDLL_API __declspec(dllimport)
#endif

extern "C" SECONDDLL_API int relativePositionX(HWND hWnd, SIZE text);
extern "C" SECONDDLL_API int relativePositionY(HWND hWnd, SIZE text, int i);