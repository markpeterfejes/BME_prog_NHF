#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix {
	int rowCount;
	int columnCount;
	double** data;
}Matrix;

Matrix* readMatrixFromFile(char* fileName, char columnSeparator, char rowSeparator);
double** allocateNewMatrixData(int rowCount, int columnCount);

#endif