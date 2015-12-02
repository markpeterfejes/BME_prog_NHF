#include <stdio.h>
#include <stdlib.h>
//#include "debugmalloc.h"
#include "matrix.h"
#define _CRT_SECURE_NO_WARNINGS
#define MAX_MATRIXES 20

void clearConsole();
void showMenu(void);
void addNewMatrix(void);
Matrix* openMatrixes[MAX_MATRIXES] = { NULL }; // Maximum matrixes that the program will store
int		openMatrixCount = 0;				   // Matrixes currently open

int main(void) {

	showMenu();


	//Matrix* matrix1 = readMatrixFromFile("mx.txt", ' ', '\n', "A"); // Initialize matrix, allocate memory based on the file given.
	//printMatrixValues(matrix1, '\t', '\n');
	//freeMatrix(matrix1);
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

void showMenu(void) {
	int option;
	while (1) {
		clearConsole();

		printf("1. Add new matrix\n");
		printf("2. Add two matrixes\n");
		printf("3. Multiply two matrixes\n");
		printf("4. Currently added matrixes\n");
		printf("5. Help\n");
		printf("6. Exit\n");
		printf("Select an option by entering it's number: ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			clearConsole();
			addNewMatrix();
			break;
		case 2:
			clearConsole();
			//addMatrixes();
			break;
		case 3:
			clearConsole();
			//multiplyMatrixes();
			break;
		case 4:
			clearConsole();
			//listMatrixes();
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

void addNewMatrix(void) {
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

	openMatrixes[openMatrixCount] = readMatrixFromFile(path, columnSep, rowSep, name);
	printf("Matrix added. Press enter to return to the menu");
	getchar();
}