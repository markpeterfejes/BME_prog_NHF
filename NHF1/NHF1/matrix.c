#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS


Matrix* readMatrixFromFile(char* fileName, char columnSeparator, char rowSeparator) {

	Matrix* newMatrix = (Matrix*)malloc(sizeof(Matrix));

	FILE *fp;
	fp = fopen(fileName, "rt");
	if (fp == NULL) {
		perror("while opening");
		return;
	}
	newMatrix->columnCount = 0;
	newMatrix->rowCount = 0;

	do
	{
		char c = fgetc(fp);
		if (feof(fp)) {
			break;
		}
		if (c == columnSeparator && newMatrix->rowCount == 0) {
			newMatrix->columnCount++;
		}
		if (c == rowSeparator) {
			newMatrix->rowCount++;
		}

	} while (1);
	newMatrix->columnCount++;
	newMatrix->rowCount++;

	newMatrix->data = allocateNewMatrixData(newMatrix->rowCount, newMatrix->columnCount);
	return newMatrix;
}

double** allocateNewMatrixData(int rowCount, int columnCount) {
	int i;
	double** data = (double**)malloc(columnCount*sizeof(double));
	for (i = 0; i < rowCount; i++) {
		data[i] = (double*)malloc(sizeof(double));
	}

	return data;
}