#include "matrix.h"
//#include "debugmalloc.h"
#define _CRT_SECURE_NO_WARNINGS


Matrix* readMatrixFromFile(const char* fileName, const char columnSeparator, const char rowSeparator, const char* matrixName)
{

	Matrix* newMatrix = (Matrix*)malloc(sizeof(Matrix));
	unsigned int maxDecimals = 0;
	unsigned int decimalCounter = 0;
	FILE *fp;
	strcpy(newMatrix->name, matrixName);
	fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		perror("\nError opening file");
		return(-1);
	}
	newMatrix->columnCount = 0;
	newMatrix->rowCount = 0;

	do
	{
		char c = fgetc(fp);
		if (feof(fp))
		{
			break;
		}
		decimalCounter++; // conviniently this will stop at the size of the input's maximum decimals + 1 :) 
		if (columnSeparator == c && 0 == newMatrix->rowCount)
		{
			newMatrix->columnCount++;
		}
		if (columnSeparator == c)
		{
			maxDecimals = decimalCounter > maxDecimals ? decimalCounter : maxDecimals;
			decimalCounter = 0;
		}
		if (rowSeparator == c)
		{
			newMatrix->rowCount++;
			maxDecimals = decimalCounter > maxDecimals ? decimalCounter : maxDecimals;
			decimalCounter = 0;
		}
	} while (1);
	rewind(fp);

	newMatrix->columnCount++;
	newMatrix->rowCount++;
	newMatrix->data = allocateNewMatrixData(newMatrix->rowCount, newMatrix->columnCount);

	char* tempDecimalHolder = (char*)malloc(maxDecimals * sizeof(char));
	decimalCounter = 0;
	int i = 0; int j = 0;
	do
	{
		char c = fgetc(fp);
		if (feof(fp))
		{
			break;
		}
		if (columnSeparator == c)
		{
			tempDecimalHolder[decimalCounter] = '\0';
			newMatrix->data[i][j++] = atof(tempDecimalHolder);
			decimalCounter = 0;
			continue;
		}
		if (rowSeparator == c)
		{
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

	//printf("Test:\nValue in (3,4): %g\n", newMatrix->data[2][3]);

	free(tempDecimalHolder);
	fclose(fp);
	return newMatrix;
}

static double** allocateNewMatrixData(int rowCount, int columnCount)
{
	int i;
	double** data = (double**)malloc(rowCount*sizeof(double*));
	for (i = 0; i < rowCount; i++)
	{
		data[i] = (double*)malloc(columnCount*sizeof(double));
	}

	return data;
}

void freeMatrix(Matrix* matrixToDelete)
{
	int i;
	for (i = 0; i < matrixToDelete->rowCount; i++)
	{
		free(matrixToDelete->data[i]);
	}
	free(matrixToDelete->data);
	free(matrixToDelete);
}

void printMatrixValues(const Matrix* matrixToPrint, const char columnSeparator, const char rowSeparator)
{
	int i, j;

	if (matrixToPrint->rowCount > 60 || matrixToPrint->columnCount > 30)
	{
		printf("\nMatrix is too big to be shown here.\n");
		return;
	}

	for (i = 0; i < matrixToPrint->rowCount; i++)
	{
		for (j = 0; j < matrixToPrint->columnCount; j++)
		{
			if (matrixToPrint->columnCount == j)
			{
				printf("%g", matrixToPrint->data[i][j]);
			}
			else
			{
				printf("%g%c", matrixToPrint->data[i][j], columnSeparator);
			}
		}
		if ((matrixToPrint->rowCount - 1) > i)
		{
			printf("%c", rowSeparator);
		}
	}
	printf("\n");
}

Matrix* addMatrices(const Matrix * matrix1, const Matrix * matrix2)
{
	if (matrix1->columnCount != matrix2->columnCount || matrix1->rowCount != matrix2->rowCount)
		return NULL;
	int i, j;
	Matrix* sumMatrix = (Matrix*)malloc(sizeof(Matrix));
	sumMatrix->columnCount = matrix1->columnCount;
	sumMatrix->rowCount = matrix1->rowCount;
	sumMatrix->data = allocateNewMatrixData(sumMatrix->rowCount, sumMatrix->columnCount);

	for (i = 0; i < sumMatrix->rowCount; i++)
	{
		for (j = 0; j < sumMatrix->columnCount; j++)
		{
			sumMatrix->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
		}
	}

	return sumMatrix;
}
