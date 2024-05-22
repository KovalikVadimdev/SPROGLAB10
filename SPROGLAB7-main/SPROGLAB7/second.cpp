#include <windows.h>
#include "second.h"

int relativePositionX(HWND hWnd, SIZE text) {
	RECT rt;
	GetClientRect(hWnd, &rt);
	int numberX = rt.right / 200;
	int distance = rt.right / numberX;
	int postionX = rt.right - text.cx;
	return postionX;
}

int relativePositionY(HWND hWnd, SIZE text, int i) {
	RECT rt;
	GetClientRect(hWnd, &rt);
	int numberN = rt.bottom / 200;
	int distance = rt.bottom / numberN;
	if (i == 1) {
		int postionY = 0;
		return postionY;
	}
	else if (i == numberN) {
		int postionY = rt.bottom - text.cy;
		return postionY;
	}
	else {
		int postionY = (i - 1) * distance;
		return postionY;
	}
}