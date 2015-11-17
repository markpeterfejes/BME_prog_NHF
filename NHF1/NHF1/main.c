#include <stdio.h>
#include <stdlib.h>
//#include "debugmalloc.h"
#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS

int main(void) {


	Matrix* matrix1 = readMatrixFromFile("mx.txt", ' ', '\n'); // Initialize matrix, allocate memory based on the file given.

	printMatrixValues(matrix1, '\t', '\n');

	freeMatrix(matrix1);
	return 0;
}