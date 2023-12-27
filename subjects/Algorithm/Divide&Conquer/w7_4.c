#include <stdio.h>
#include <time.h>
#include <math.h>

int karatsuba(int x, int y, int m) {
	if (m == 0) return x * y;
	int bm = pow(10, m);
	int x1 = x / bm;
	int x0 = x % bm;
	int y1 = y / bm;
	int y0 = y % bm;
	
	return x1 * y1 * pow(10, 2*m) + (x1*y0+x0*y1)*pow(10, m) + karatsuba(x0, y0, m-1);
}

int main() {

	int x = 2462;
	int y = 8014;
	
	clock_t start = clock();

	int result = karatsuba(x, y, 3);
	printf("result: %d\n", result);

	clock_t end = clock();

	printf("execute time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);

	return 0;
}
