#include <stdio.h>

int main () {
	int a, b, c;
	while (scanf("%d%d%d", &a, &b, &c) == 3) {
		printf("%.5lf\n", (1.0 * a * b + b * (b - 1)) / (a + b - c - 1) / (a + b ));
	}
	return 0;
}
