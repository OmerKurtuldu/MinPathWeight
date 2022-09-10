#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_SIZE 100
#define MAX_VALUE 100

void initializeCellWeight(int cellWeights[MAX_SIZE][MAX_SIZE], int rowSize, int colSize);
int minSummation(int patWeights[MAX_SIZE][MAX_SIZE], int rowIndex, int colIndex);
int minValue(int firstValue, int secondValue, int thirdValue);
void print(int pathWeights[MAX_SIZE][MAX_SIZE], int rowSize, int colSize);
void printWithPath(int cellWeights[MAX_SIZE][MAX_SIZE], int minPathWeights[MAX_SIZE], int rowSize, int colSize);
void copyWeight(int pathWeights[MAX_SIZE][MAX_SIZE], int cellWeights[MAX_SIZE][MAX_SIZE], int rowSize, int colSize);
void calculatePathWeights(int pathWeights[MAX_SIZE][MAX_SIZE], int rowSize, int colSize);
void minPathWeightSummation(int pathWeights[MAX_SIZE][MAX_SIZE], int cellWeights[MAX_SIZE][MAX_SIZE], int minPathWeights[MAX_SIZE], int rowSize, int colSize);
int calculatePathweights(int pathWeights[MAX_SIZE][MAX_SIZE], int minPathWeights[MAX_SIZE], int rowSize);

int main(void) {
	int cellWeights[MAX_SIZE][MAX_SIZE];
	int pathWeights[MAX_SIZE][MAX_SIZE];
	int minPathWeights[MAX_SIZE];
	int colSize, rowSize;
	//int i, j;
	//int min;

	while (1) {

		printf("Enter row numbers or (0 to exit) : ");
		scanf_s("%d", &rowSize);
		if (rowSize == 0)
			break;
		printf("Enter col numbers : ");
		scanf_s("%d", &colSize);

		initializeCellWeight(cellWeights, rowSize, colSize);

		printf("\n\n");

		copyWeight(pathWeights, cellWeights, rowSize, colSize);

		calculatePathWeights(pathWeights, rowSize, colSize);

		minPathWeightSummation(pathWeights, cellWeights, minPathWeights, rowSize, colSize);

		printWithPath(cellWeights, minPathWeights, rowSize, colSize);

		printf("Sum of weights : %d", calculatePathweights(pathWeights, minPathWeights, rowSize));
		printf("\n\n");
	}
	printf("\n\n");
	system("pause");
}

void initializeCellWeight(int cellWeights[MAX_SIZE][MAX_SIZE], int rowSize, int colSize) {
	int i, j;
	int upper = 10, lower = 0;
	srand(time_t(NULL));

	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			cellWeights[i][j] = (rand() % (upper - lower + 1)) + lower;
		}
	}
}

void copyWeight(int pathWeights[MAX_SIZE][MAX_SIZE], int cellWeights[MAX_SIZE][MAX_SIZE], int rowSize, int colSize) {
	int i, j;

	for (i = 0; i < rowSize; i++) {
		for (j = 0; j < colSize; j++) {
			pathWeights[i][j] = cellWeights[i][j];
		}
	}
}

void calculatePathWeights(int pathWeights[MAX_SIZE][MAX_SIZE], int rowSize, int colSize) {
	int i, j;

	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			pathWeights[i][j] = minSummation(pathWeights, i, j, colSize);
		}
	}
}


void minPathWeightSummation(int pathWeights[MAX_SIZE][MAX_SIZE], int cellWeights[MAX_SIZE][MAX_SIZE], int minPathWeights[MAX_SIZE], int rowSize, int colSize) {

	int colIndex = 0;
	int i = 0;
	int rowIndex = rowSize - 1;

	while (i < colSize - 1) {
		if (pathWeights[rowIndex][i + 1] < pathWeights[rowIndex][colIndex]) {
			colIndex = i + 1;
		}
		i++;
	}

	while (rowIndex > 0) {
		minPathWeights[rowIndex] = colIndex;
		if (colIndex > 0 && pathWeights[rowIndex - 1][colIndex - 1] + cellWeights[rowIndex][colIndex] == pathWeights[rowIndex][colIndex]) {
			colIndex = colIndex - 1;
		}
		else if (colIndex < colSize - 1 && pathWeights[rowIndex - 1][colIndex + 1] + cellWeights[rowIndex][colIndex] == pathWeights[rowIndex][colIndex]) {
			colIndex = colIndex + 1;
		}
		rowIndex--;
	}
	minPathWeights[0] = colIndex;
}


void printWithPath(int cellWeights[MAX_SIZE][MAX_SIZE], int minPathWeights[MAX_SIZE], int rowSize, int colSize) {
	int i, j;

	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			if (minPathWeights[i] == j) {
				printf("[%d]\t", cellWeights[i][j]);
			}
			else {
				printf("%d\t", cellWeights[i][j]);
			}

		}
		printf("\n\n");
	}

	printf("\n\n");
}

int minSummation(int patWeights[MAX_SIZE][MAX_SIZE], int rowIndex, int colIndex, int colSize) {
	int currentValue = patWeights[rowIndex][colIndex];
	int leftUpSummationValue = MAX_VALUE, upSummationValue = MAX_VALUE, rightUpSummationValue = MAX_VALUE;

	if (rowIndex != 0 && colIndex != 0 && colIndex != colSize - 1) {
		leftUpSummationValue = currentValue + patWeights[rowIndex - 1][colIndex - 1];
		upSummationValue = currentValue + patWeights[rowIndex - 1][colIndex];
		rightUpSummationValue = currentValue + patWeights[rowIndex - 1][colIndex + 1];
	}
	else if (rowIndex != 0 && colIndex != 0) {
		leftUpSummationValue = currentValue + patWeights[rowIndex - 1][colIndex - 1];
		upSummationValue = currentValue + patWeights[rowIndex - 1][colIndex];
	}
	else if (rowIndex != 0 && colIndex != colSize - 1) {
		upSummationValue = currentValue + patWeights[rowIndex - 1][colIndex];
		rightUpSummationValue = currentValue + patWeights[rowIndex - 1][colIndex + 1];
	}
	else {
		return currentValue;
	}

	return minValue(leftUpSummationValue, upSummationValue, rightUpSummationValue);
}

int minValue(int firstValue, int secondValue, int thirdValue) {
	if (firstValue < secondValue) {
		if (firstValue < thirdValue) {
			return firstValue;
		}
		else {
			return thirdValue;
		}
	}
	else {
		if (secondValue < thirdValue) {
			return secondValue;
		}
		else {
			return thirdValue;
		}
	}
}

void print(int pathWeights[MAX_SIZE][MAX_SIZE], int rowSize, int colSize) {
	int i, j;

	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			printf("%d\t", pathWeights[i][j]);
		}
		printf("\n\n");
	}

	printf("\n\n");
}



int calculatePathweights(int pathWeights[MAX_SIZE][MAX_SIZE], int minPathWeights[MAX_SIZE], int rowSize) {
	return pathWeights[rowSize - 1][minPathWeights[rowSize - 1]];
}