#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS

int main(void) {


	Matrix* matrix1 = readMatrixFromFile("mx.txt", ' ', '\n');

	free(matrix1);
	return 0;
}