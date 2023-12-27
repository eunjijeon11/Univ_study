#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

int main() {

	int N = 0;
	printf("Item 수를 입력하세요: ");
	scanf("%d", &N);

	int wLimit = 0;
	printf("Weight limit을 입력하세요: ");
	scanf("%d", &wLimit);

	int cases = pow(2, N);
	int value[N];
	int weight[N];
	
	printf("==============\n");
	for (int i=0; i<N; i++) {
		printf("%d번째 value를 입력하세요: ", i+1);
		scanf("%d", &value[i]);
		
		printf("%d번째 weight를 입력하세요: ", i+1);
		scanf("%d", &weight[i]);
		printf("==============\n");
	}

	int valueComb[cases];
	int weightComb[cases];
	memset(valueComb, 0, sizeof(int) * cases);
	memset(weightComb, 0, sizeof(int) * cases);
	
	clock_t start = clock();

	for (int i=0; i<N; i++) {
		for (int j=0; j<pow(2, i); j++) {
			for (int k=0; k<cases/pow(2,i+1); k++) {
				int index = j * cases / pow(2, i) + k;
				valueComb[index] += value[i];
				weightComb[index] += weight[i];
			}
		}
	}
	
	int maxValue = 0;
	for (int i=0; i<cases; i++) {
		if (weightComb[i] <= wLimit && valueComb[i] > maxValue) maxValue = valueComb[i];
	}
	printf("max value: %d\n", maxValue);

	clock_t end = clock();

	printf("execute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
