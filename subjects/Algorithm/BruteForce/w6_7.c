#include <stdio.h>
#include <time.h>
#include <string.h>

void calculateMin(int *history, int *min, int *minHistory, int jobCost[][10], int index, int sum) {
	int temp[10];
	memcpy(temp, history, sizeof(int)*10);

	for (int i=0; i<10; i++) {
		memcpy(history, temp, sizeof(int)*10);
		if (history[i] != -1) continue;
		history[i] = index;
		
		if (index == 9) {
			if (sum + jobCost[index][i] < *min) {
				*min = sum + jobCost[index][i];
				memcpy(minHistory, history, sizeof(int)*10);
			}
		} else {
			calculateMin(history, min, minHistory, jobCost, index+1, sum + jobCost[index][i]);
		}
	}
}

int main() {

	int jobCost[10][10] = {
		{13,6,7,12,14,15,10,11,15,4},
		{8,14,11,9,6,14,7,9,16,12},
		{10,8,10,10,8,15,11,5,7,9},
		{13,13,16,9,13,16,15,9,14,16},
		{11,4,9,14,12,11,5,16,8,14},
		{7,10,12,13,4,11,16,12,15,9},
		{6,11,10,11,13,15,7,16,11,12},
		{7,15,5,10,4,16,12,4,10,16},
		{5,14,10,15,8,8,8,14,14,4},
		{8,11,4,16,8,12,4,14,9,6}};

	int assigned[10];
	memset(assigned, -1, sizeof(int)*10);
	
	clock_t start = clock();

	int min = 200;
	int minAssignment[10];
	calculateMin(assigned, &min, minAssignment, jobCost, 0, 0);
	printf("cost sum: %d\nassignment: ", min);
	for (int i=0; i<10; i++) {
		printf("person %d on %d job\n", minAssignment[i], i);
	}

	clock_t end = clock();

	printf("execute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
