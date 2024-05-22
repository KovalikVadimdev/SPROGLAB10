#include <windows.h>
#include <cmath>
#include "first.h"

int power(int numberX, int numberY) {
	int result = pow(numberX, numberY);
	return result;
}

int powerOfSums(int numberX, int numberN) {
	int result = 0;
	for (int i = 1; i <= numberN; i++) {
		result += pow(numberX, i);
	}
	return result;
}