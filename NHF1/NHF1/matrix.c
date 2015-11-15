#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS


Matrix* readMatrixFromFile(char* fileName, char const columnSeparator, char const rowSeparator) {

	Matrix* newMatrix = (Matrix*)malloc (sizeof(Matrix));
	unsigned int maxDecimals = 0;
	unsigned int decimalCounter = 0;
	FILE *fp;
	fp = fopen(fileName, "rt");
	if (fp == NULL) {
		perror("Error opening file");
		return(-1);
	}
	newMatrix->columnCount = 0;
	newMatrix->rowCount = 0;
	
	do
	{
		char c = fgetc(fp);
		if (feof(fp)) {
			break;
		}
		decimalCounter++; // conviniently this will stop at the size of the input's maximum decimals + 1 :) https://www.youtube.com/watch?v=yG0oBPtyNb0
		if (columnSeparator == c && 0 == newMatrix->rowCount) {
			newMatrix->columnCount++;
		}
		if (columnSeparator == c) {
			maxDecimals = decimalCounter > maxDecimals ? decimalCounter : maxDecimals;
			decimalCounter = 0;
		}
		if (rowSeparator == c) {
			newMatrix->rowCount++;
			maxDecimals = decimalCounter > maxDecimals ? decimalCounter : maxDecimals;
			decimalCounter = 0;
		}
	} while (1);
	rewind(fp);

	newMatrix->columnCount++;
	newMatrix->rowCount++;
	newMatrix->data = allocateNewMatrixData (newMatrix->rowCount, newMatrix->columnCount);

	char* tempDecimalHolder = (char*)malloc (maxDecimals * sizeof(char));
	decimalCounter = 0;
	int i = 0; int j = 0;
	do
	{
		char c = fgetc(fp);
		if (feof(fp)) {
			break;
		}
		if (columnSeparator == c) {
			tempDecimalHolder[decimalCounter] = '\0';
			newMatrix->data[i][j++] = atof(tempDecimalHolder);
			decimalCounter = 0;
			continue;
		}
		if (rowSeparator == c) {
			tempDecimalHolder[decimalCounter] = '\0';
			newMatrix->data[i++][j] = atof(tempDecimalHolder);
			j = 0;
			decimalCounter = 0;
			continue;
		}
		tempDecimalHolder[decimalCounter++] = c;
	} while (1);
	tempDecimalHolder[decimalCounter] = '\0';
	newMatrix->data[i][j] = atof(tempDecimalHolder);

	//printf("%g\n", newMatrix->data[2][3]);

	free(tempDecimalHolder);
	fclose(fp);
	return newMatrix;
}

double** allocateNewMatrixData(int rowCount, int columnCount) {
	int i;
	double** data = (double**)malloc(columnCount*sizeof(double*));
	for (i = 0; i < rowCount; i++) {
		data[i] = (double*)malloc(sizeof(double));
	}

	return data;
}

