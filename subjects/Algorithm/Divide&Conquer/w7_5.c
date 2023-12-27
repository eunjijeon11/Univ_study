#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int** divideMatrix(int *matrix[], int size, int x, int y) {
	int newSize = size / 2;
	int newMatrix[newSize][newSize] = malloc(sizeof(int)*newSize*newSize);
	for (int i=0; i<newSize; i++) {
		for (int j=0; j<newSize; j++) {
			newMatrix[i][j] = matrix[x*newSize+i][y*newSize+j];
		}
	}
	return newMatrix;
}

int* strassen(int *A[], int *B[], int size) {
	int newSize = size / 2;

	int A00[newSize][newSize] = divideMatrix(A, size, 0, 0);
	int A01[newSize][newSize] = divideMatrix(A, size, 0, 1);
	int A10[newSize][newSize] = divideMatrix(A, size, 1, 0);
	int A11[newSize][newSize] = divideMatrix(A, size, 1, 1);

	int B00[newSize][newSize] = divideMatrix(B, size, 0, 0);
	int B01[newSize][newSize] = divideMatrix(B, size, 0, 1);
	int B10[newSize][newSize] = divideMatrix(B, size, 1, 0);
	int B11[newSize][newSize] = divideMatrix(B, size, 1, 1);
	
		
}

int main() {

	int a[2][2] = {
		{10, 8},
		{12, 11}};
	int b[2][2] = {
		{4, 9},
		{8, 13}};
	
	clock_t start = clock();

	

	clock_t end = clock();

	printf("execute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
