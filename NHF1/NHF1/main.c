#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "matrix.h"
#define MAX_MATRICES 20

void clearConsole();
void showMenu(void);
void addNewMatrix(void);
void multiplyMatrix(void);
void addMatrix(void);
void printMatrixToFile(void);
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
		printf("5. Save matrix to file\n");
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
			addMatrix();
			break;
		case 3:
			clearConsole();
			multiplyMatrix();
			break;
		case 4:
			clearConsole();
			listMatrices();
			break;
		case 5:
			clearConsole();
			printMatrixToFile();
			break;
		case 6:
			return;
			break;
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
	printf("Please enter the name of the new matrix (max 50 characters):\n");
	scanf("%50s%*c", &name);
	printf("\nPlease enter the path to the file containing the matrix (max 100 characters):\n");
	scanf("%100s%*c", &path);
	printf("\nCharacter separating the columns: ");
	scanf("%c%*c", &columnSep);
	printf("\nCharacter separating the rows: ");
	scanf("%c%*c", &rowSep);

	openMatrices[openMatrixCount++] = readMatrixFromFile(path, columnSep, rowSep, name);
	printf("Matrix added. Press enter to return to the menu");
	scanf("%*c");
}

void listMatrices(void)
{
	int i;
	int option;

	if (openMatrixCount == 0)
	{
		printf("No open matrices found. Add some! Enter 0 to go back to the menu\n");
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
void addMatrix(void)
{
	int i;
	int tag1, tag2;
	char newName[51];
	if (openMatrixCount <= 0)
	{
		printf("No open matrices found. Add some! Enter 0 to go back to the menu\n");
		scanf("%*c");
		return;
	}
	if (openMatrixCount >= MAX_MATRICES)
	{
		printf("Too many open matrices. Please restart the program.\n");
		scanf("%*c");
		return;
	}

	for (i = 0; i < openMatrixCount; i++)
	{
		printf("%d. %s: Rowcount: %d Columncount: %d\n", i + 1, openMatrices[i]->name, openMatrices[i]->columnCount, openMatrices[i]->rowCount);
	}

	printf("Select Two matrices to add together, by entering their number\n");
	printf("First one: ");
	scanf("%d%*c", &tag1);
	printf("Second one: ");
	scanf("%d%*c", &tag2);

	if (tag1 > 0 && tag1 <= openMatrixCount && tag2 > 0 && tag2 <= openMatrixCount)
	{
		snprintf(newName, 51 * (sizeof(char)), "%s + %s", openMatrices[tag1 - 1]->name, openMatrices[tag2 - 1]->name);

		openMatrices[openMatrixCount] = addMatrices(openMatrices[tag1 - 1], openMatrices[tag2 - 1], newName);
		if (openMatrices[openMatrixCount] == NULL)
		{
			printf("\n It would be good if the matrices would be the same sizes...\n");
			scanf("%*c");
			return;
		}
		openMatrixCount++;
		printf("\nIt can be found in the menu!\n");
		scanf("%*c");
	}
}

void multiplyMatrix(void)
{
	int i;
	int tag1, tag2;
	char newName[51];
	if (openMatrixCount <= 0)
	{
		printf("No open matrices found. Add some! Enter 0 to go back to the menu\n");
		scanf("%*c");
		return;
	}
	if (openMatrixCount >= MAX_MATRICES)
	{
		printf("Too many open matrices. Please restart the program.\n");
		scanf("%*c");
		return;
	}

	for (i = 0; i < openMatrixCount; i++)
	{
		printf("%d. %s: Rowcount: %d Columncount: %d\n", i + 1, openMatrices[i]->name, openMatrices[i]->columnCount, openMatrices[i]->rowCount);
	}

	printf("Select Two matrices to multiply, by entering their numbers\n");
	printf("First one: ");
	scanf("%d%*c", &tag1);
	printf("Second one: ");
	scanf("%d%*c", &tag2);

	if (tag1 > 0 && tag1 <= openMatrixCount && tag2 > 0 && tag2 <= openMatrixCount)
	{
		snprintf(newName, 51 * (sizeof(char)), "%s * %s", openMatrices[tag1 - 1]->name, openMatrices[tag2 - 1]->name);

		openMatrices[openMatrixCount] = multiplyMatrices(openMatrices[tag1 - 1], openMatrices[tag2 - 1], newName);
		if (openMatrices[openMatrixCount] == NULL)
		{
			printf("\n Matrix1's columncount must be the same as matrix2's rowcount!");
			scanf("%*c");
			return;
		}
		openMatrixCount++;
		printf("\nIt can be found in the menu!\n");
		scanf("%*c");
	}
}

void printMatrixToFile(void)
{
	int i;
	int option,fileType;
	char columnsep, rowsep;
	char fileName[101];

	if (openMatrixCount == 0)
	{
		printf("No open matrices found. Add some! Enter 0 to go back to the menu\n");
		getchar();
		return;
	}
	while (1)
	{
		for (i = 0; i < openMatrixCount; i++)
		{
			printf("%d. %s: Columncount: %d Rowcount: %d\n", i + 1, openMatrices[i]->name, openMatrices[i]->columnCount, openMatrices[i]->rowCount);
		}
		printf("\nSelect a matrix you want to print, by entering it's number, or any other number to go back to the menu: ");
		scanf("%d%*c", &option);
		if (option > 0 && option <= openMatrixCount)
		{
			printf("\nEnter file name(with extension max 100 characters): ");
			scanf("%s%*c", &fileName);
			printf("\nEnter a row separator character: ");
			scanf("%c%*c", &rowsep);
			printf("\nEnter a column separator character: ");
			scanf("%c%*c", &columnsep);
			fSaveMatrixToFile(openMatrices[option - 1], columnsep, rowsep, fileName);
			scanf("%*c");
			continue;
		}
		break;
	}
}