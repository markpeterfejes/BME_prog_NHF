#include "matrix.h"
#include "debugmalloc.h"


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
			if (matrixToPrint->columnCount - 1 == j)
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

Matrix* addMatrices(const Matrix * matrix1, const Matrix * matrix2, const char* name)
{
	if (matrix1->columnCount != matrix2->columnCount || matrix1->rowCount != matrix2->rowCount)
		return NULL;
	int i, j;
	Matrix* sumMatrix = (Matrix*)malloc(sizeof(Matrix));
	sumMatrix->columnCount = matrix1->columnCount;
	sumMatrix->rowCount = matrix1->rowCount;
	sumMatrix->data = allocateNewMatrixData(sumMatrix->rowCount, sumMatrix->columnCount);
	strcpy(sumMatrix->name, name);
	for (i = 0; i < sumMatrix->rowCount; i++)
	{
		for (j = 0; j < sumMatrix->columnCount; j++)
		{
			sumMatrix->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
		}
	}

	return sumMatrix;
}

Matrix * multiplyMatrices(const Matrix * matrix1, const Matrix * matrix2, const char * name)
{
	if (matrix1->columnCount != matrix2->rowCount)
		return NULL;
	int i, j, k;
	Matrix* productMatrix = (Matrix*)malloc(sizeof(Matrix));
	productMatrix->columnCount = matrix2->columnCount;
	productMatrix->rowCount = matrix1->rowCount;
	productMatrix->data = allocateNewMatrixData(productMatrix->rowCount, productMatrix->columnCount);
	strcpy(productMatrix->name, name);
	nullifyMatrixData(productMatrix);
	for (i = 0; i < matrix1->rowCount; i++)
		for (j = 0; j < matrix2->columnCount; j++)
			for (k = 0; k < matrix1->columnCount; k++)
			{
				productMatrix->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
			}

	return productMatrix;
}

void nullifyMatrixData(Matrix * matrixToNullify)
{
	int i, j;

	for (i = 0; i < matrixToNullify->rowCount; i++)
	{
		for (j = 0; j < matrixToNullify->columnCount; j++)
		{
			matrixToNullify->data[i][j] = 0;
		}
	}
}

void fSaveMatrixToFile(const Matrix * matrixToWrite, const char columnSeparator, const char rowSeparator, char * filename)
{
	FILE* fp;
	int i, j;
	fp = fopen(filename, "w+");
	for (i = 0; i < matrixToWrite->rowCount; i++)
	{
		for (j = 0; j < matrixToWrite->columnCount; j++)
		{
			if (matrixToWrite->columnCount - 1 == j)
			{
				fprintf(fp, "%g", matrixToWrite->data[i][j]);
			}
			else
			{
				fprintf(fp, "%g%c", matrixToWrite->data[i][j], columnSeparator);
			}
		}
		if ((matrixToWrite->rowCount - 1) > i)
		{
			fprintf(fp, "%c", rowSeparator);
		}
	}
	fclose(fp);
}
