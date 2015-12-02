#include <stdio.h>
#include <stdlib.h>
//#include "debugmalloc.h"
#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS

void clearConsole();

int main(void) {


	Matrix* matrix1 = readMatrixFromFile("mx.txt", ' ', '\n'); // Initialize matrix, allocate memory based on the file given.

	printMatrixValues(matrix1, '\t', '\n');

	freeMatrix(matrix1);
	return 0;
}


void clearConsole() {
#ifdef _WIN32
	system("cls");
#endif
#ifdef __unix__
	system("clear");
#endif

}