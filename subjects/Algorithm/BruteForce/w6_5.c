#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
	int graph[5][5] = {
		{0, 2, 3, 2, 3},
		{2, 0, 3, 4, 1},
		{3, 3, 0, 2, 4},
		{2, 4, 2, 0, 5},
		{3, 1, 4, 5, 0}};

	int minTSP[5] = {0,};
	int minCost = 100;
	int cost = 0;
	
	clock_t start = clock();
	
	for (int i=1; i<5; i++) {
		cost += graph[0][i];
		for (int j=1; j<5; j++) {
			if (j==i) continue;
			cost += graph[i][j];
			for (int k=1; k<5; k++) {
				if (k==i || k==j) continue;
				cost += graph[j][k];
				for (int l=1; l<5; l++) {
					if (l==i || l==k || l==j) continue;
					cost += graph[k][l] + graph[l][0];
					if (cost < minCost) {
						minCost = cost;
						int temp[] = {0, i, j, k, l};
						memcpy(minTSP, temp, sizeof(int)*5);
					}
					cost -= graph[k][l] + graph[l][0];
				}
				cost -= graph[j][k];
			}
			cost -= graph[i][j];
		}
		cost -= graph[0][i];
	}
	
	for (int i=0; i<5; i++) printf("%d->", minTSP[i]+1);
	printf("1\ntotal cost: %d\n", minCost);

	clock_t end = clock();

	printf("execute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
