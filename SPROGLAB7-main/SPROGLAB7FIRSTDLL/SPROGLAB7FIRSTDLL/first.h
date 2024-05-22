#include <windows.h>
#pragma once

#ifdef FIRSTDLL_EXPORTS
#define FIRSTDLL_API __declspec(dllexport)
#else
#define FIRSTDLL_API __declspec(dllimport)
#endif

extern "C" FIRSTDLL_API int power(int numberX, int numberY);
extern "C" FIRSTDLL_API int powerOfSums(int numberX, int numberN);