#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int findMinIndex(int startIndex, int *arr) {
	int minIndex = startIndex;
	for (int i=startIndex; i<1000; i++) {
		if (arr[minIndex] > arr[i]) minIndex = i;
	}
	return minIndex;
}

int main() {

	int numbers[1000];
	for (int i=0; i<1000; i++) {
		numbers[i] = rand()%10000;
	}
	
	clock_t start = clock();

	for (int i=0; i<999; i++) {
		int minIndex = findMinIndex(i, numbers);
		int temp = numbers[i];
		numbers[i] = numbers[minIndex];
		numbers[minIndex] = temp;
	}

	for (int i=0; i<1000; i++) printf("%d ", numbers[i]);
	printf("\n");

	clock_t end = clock();

	printf("execute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
