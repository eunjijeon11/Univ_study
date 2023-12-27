#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int bubbleSort(int *arr) {
	for (int i=0; i<999; i++) {
		for (int j=0; j<999-i; j++) {
			if (arr[j] > arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main() {

	int numbers[1000];
	for (int i=0; i<1000; i++) {
		numbers[i] = rand()%10000;
	}
	
	clock_t start = clock();
	bubbleSort(numbers);
	clock_t end = clock();

	for (int i=0; i<1000; i++) printf("%d ", numbers[i]);
	printf("\n");

	printf("execute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
