#include <stdio.h>
#include <string.h>

int main () {
	double a, b, c;
	while (scanf("%lf%lf%lf", &a, &b, &c) == 3) {
		double x = (b + c) / (a + b + 2 * c);
		printf("%.6lf\n", b - (b + c) * x);
	}
	return 0;
}
