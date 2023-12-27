#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 150000

int main() {

	FILE *fp = fopen("./little_prince.txt", "rt+,ccs=UTF-8");
	char buffer[MAX_LENGTH] = {0, };
	fread(buffer, sizeof(char), MAX_LENGTH, fp);
	
	int count = 0;
	char littlePrince[] = "어린 왕자";

	clock_t start = clock();

	for (int i=0; i<sizeof(buffer); i++) {
		if (strncmp(buffer+i, littlePrince, sizeof(littlePrince)-1)==0) {
			printf("%d에 \"%s\" 발견\n", i, littlePrince);
			count++;
		}
	}

	printf("총 발견 횟수: %d\n", count);

	clock_t end = clock();

	printf("execute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
