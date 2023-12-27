#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void quickSort(int *arr, int size) {
	if (size < 2) return;

	int pivot = arr[0];
	int low = 1;
	int high = size - 1;
	while(low <= high) {
		if (arr[low] > arr[high]) {
			int temp = arr[low];
			arr[low] = arr[high];
			arr[high] = temp;
		}

		while(arr[low] <= pivot) low++;
		while(arr[high] > pivot) high--;
	}
	arr[0] = arr[high];
	arr[high] = pivot;

	quickSort(&arr[0], high);
	quickSort(&arr[low], size - low);
}

int main() {
	
	int arr[100] = {0, };
	printf("정렬 전: ");
	for (int i=0; i<100; i++) {
		arr[i] = rand() % 1000;
		printf("%d ", arr[i]);
	}
	printf("\n");

	clock_t start = clock();

	quickSort(arr, 100);

	clock_t end = clock();

	printf("정렬 후: ");
	for (int i=0; i<100; i++) printf("%d ", arr[i]);

	printf("\nexecute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
