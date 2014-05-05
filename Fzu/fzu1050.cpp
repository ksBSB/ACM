#include <stdio.h>
#include <math.h>

const int N = 1000005;
int n, d[N];

void init() {
	double sum = 0;
	for (int i = 1; i < N; i++) {
		sum += log10((double)i);
		d[i] = (int)sum;
	}
}

int main () {
	init();
	while (scanf("%d", &n) == 1) {
		printf("%d\n", d[n] + 1);
	}
	return 0;
}
