#include <stdio.h>
#include <math.h>

const double INF = 0x3f3f3f;

bool cmp(double a, double b) {
	return a - b < 0;
}

int main() {
	int a, b, cas = 0;
	while (scanf("%d%d", &a, &b) == 2) {
		if (cas++) printf("\n");

		double p = 1.0 * a / b, tmp = INF;
		for (int i = 1; i <= b; i++) {
			int u = (int) i * p + 0.5;
			if(cmp(fabs(1.0*u/i - p), tmp)) {
				tmp = fabs(1.0*u/i - p);
				printf("%d/%d\n", u, i);
			}
		}
	}
	return 0;
}
