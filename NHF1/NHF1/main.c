#include <stdio.h>
#include <stdlib.h>
//#include "debugmalloc.h"
#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS
#define MAX_MATRICES 20

void clearConsole();
void showMenu(void);
void addNewMatrix(void);
void listMatrices(void);
void freeProgramMemory();

Matrix* openMatrices[MAX_MATRICES] = { NULL }; // Maximum matrices that the program will store
int		openMatrixCount = 0;				   // Matrices currently open

int main(void)
{

	showMenu();


	//Matrix* matrix1 = readMatrixFromFile("mx.txt", ' ', '\n', "A"); // Initialize matrix, allocate memory based on the file given.
	//printMatrixValues(matrix1, '\t', '\n');
	//freeMatrix(matrix1);
	freeProgramMemory();
	return 0;
}

void clearConsole()
{
#ifdef _WIN32
	system("cls");
#endif
#ifdef __unix__
	system("clear");
#endif
}

void showMenu(void)
{
	int option;
	while (1)
	{
		clearConsole();

		printf("1. Add new matrix\n");
		printf("2. Add two matrices\n");
		printf("3. Multiply two matrices\n");
		printf("4. Currently added matrices\n");
		printf("5. Help\n");
		printf("6. Exit\n");
		printf("Select an option by entering it's number: ");
		scanf("%d%*c", &option);
		switch (option)
		{
		case 1:
			clearConsole();
			addNewMatrix();
			break;
		case 2:
			clearConsole();
			//addMatrices();
			break;
		case 3:
			clearConsole();
			//multiplyMatrices();
			break;
		case 4:
			clearConsole();
			listMatrices();
			break;
		case 5:
			clearConsole();
			//help();
			break;
		case 6:
			return;
		default:
			printf("\nInvalid menu option!\n");
			break;
		}
	}
}

void addNewMatrix(void)
{
	if (openMatrixCount >= MAX_MATRICES)
	{
		printf("Cannot add more matrices. Maximum matrix count reached(%d) Press enter to return to the menu\n", MAX_MATRICES);
		getchar();
		getchar();
		return;
	}

	char name[51];
	char path[101];
	char columnSep;
	char rowSep;
	printf("-------Adding a new Matrix-------\n");
	printf("Please enter the name of the new matrix (max 50 characters): ");
	scanf("%50s%*c", &name);
	printf("\nPlease enter the path to the file containing the matrix (max 100 characters): ");
	scanf("%100s%*c", &path);
	printf("\nCharacter separating the columns: ");
	scanf("%c%*c", &columnSep);
	printf("\nCharacter separating the rows: ");
	scanf("%c%*c", &rowSep);

	openMatrices[openMatrixCount++] = readMatrixFromFile(path, columnSep, rowSep, name);
	printf("Matrix added. Press enter to return to the menu");
	getchar();
}

void listMatrices(void)
{
	int i;
	int option;

	if (openMatrixCount == 0)
	{
		printf("No open matrices found. Add some! Press 'Return' to go back to the menu\n");
		getchar();
		return;
	}
	while (1)
	{
		for (i = 0; i < openMatrixCount; i++)
		{
			printf("%d. %s: Rowcount: %d Columncount: %d\n", i + 1, openMatrices[i]->name, openMatrices[i]->columnCount, openMatrices[i]->rowCount);
		}
		printf("\nSelect a matrix you want to print, by entering it's number, or any other number to go back to the menu: ");
		scanf("%d%*c", &option);
		if (option > 0 && option <= openMatrixCount)
		{
			printMatrixValues(openMatrices[option - 1], '\t', '\n');
			getchar();
			continue;
		}
		break;
	}
}

void freeProgramMemory()
{
	int i;

	if (openMatrixCount == 0)
		return;

	for (i = 0; i < openMatrixCount; i++)
	{
		freeMatrix(openMatrices[i]);
	}
}
