#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-9;

int main () {
	int N, C = 0;
	double a, b, c;
	scanf("%d", &N);
	while (N) {
		scanf("%lf%lf%lf", &a, &b, &c);
		if (fabs(a) < eps || fabs(b) < eps || fabs(c) < eps) {
			N--;
			printf("These are invalid inputs!\n");
			continue;
		}
		a = 1 / a, b = 1 / b, c = 1 / c;
		double t = a + b + c;
		double S = t * (t - 2 * a) * (t - 2 * b) * (t - 2 * c);
		if (S < 0) {
			N--;
			printf("These are invalid inputs!\n");
			continue;
		}
		printf("%.3lf\n", 1 / sqrt(S));
	}
	return 0;
}
