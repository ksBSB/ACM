#include <stdio.h>
#include <math.h>

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%d\n", n + (int)ceil(log2((double)n)) - 2);
	}
	return 0;
}
