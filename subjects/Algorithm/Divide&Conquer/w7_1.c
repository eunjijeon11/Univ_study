#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void mergeSort(int *arr, int size, int *sortedArr) {
	if (size == 1) {
		memcpy(sortedArr, arr, sizeof(int));
	}
	else {
		int nextSize = (int)size/2;
		int arr1[nextSize];
		mergeSort(&arr[0], nextSize, arr1);
		int arr2[size-nextSize];
		mergeSort(&arr[nextSize], size - nextSize, arr2);

		int j=0;
		int k=0;
		printf("정렬된 배열: ");
		for (int i=0; i<size; i++) {
			if (j < nextSize && arr1[j] < arr2[k]) {
				sortedArr[i] = arr1[j];
				j++;
			}
			else if (k < size-nextSize) {
				sortedArr[i] = arr2[k];
				k++;
			}
			printf("%d ", sortedArr[i]);
		}
		printf("\n");
	}
}

int main() {

	int arr[50] = {0, };
	printf("정렬 전: \n");
	for (int i=0; i<50; i++) {
		arr[i] = rand()%200;
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	clock_t start = clock();

	int sortedArr[50];
	mergeSort(arr, 50, sortedArr);

	clock_t end = clock();

	printf("정렬 후: \n");
	for (int i=0; i<50; i++) printf("%d ", sortedArr[i]);

	printf("\nexecute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
