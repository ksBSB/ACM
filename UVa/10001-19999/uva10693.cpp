#include <cstdio>
#include <cstring>
#include <cmath>

int main () {
	double l, f;
	while (scanf("%lf%lf", &l, &f) == 2 && l + f) {
		printf("%.8lf %.8lf\n", sqrt(2 * l * f), 3600 * sqrt(f / (2 * l)));
	}
	return 0;
}
