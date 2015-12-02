#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix {
	char name[51];
	int rowCount;
	int columnCount;
	double** data;
}Matrix;

Matrix* readMatrixFromFile(const char* fileName, const char columnSeparator, const char rowSeparator, const char* matrixName); // creates a new Matrix from the given file, with the given separators
static double** allocateNewMatrixData(int rowCount, int columnCount);
void freeMatrix(Matrix* matrixToDelete);
void printMatrixValues(const Matrix* matrixToPrint, const char columnSeparator, const char rowSeparator);

#endif