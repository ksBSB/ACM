#include <stdio.h>
#include <string.h>
#include <math.h>
const int N = 35;

int n;
double v[N], t;

double solve() {
	if (fabs(1 - t) < 1e-9) return v[n];

	double ans = v[n];
	for (int i = n - 1; i >= 0; i--) {
		double f = v[i] / ans;

		if (f <= t)
			ans  = (1 + t) / 2 * ans;
		else
			ans = (f - t) / (1 - t) * v[i] + (1 - f) / (1 - t) * (1 + f) / 2 * ans;
	}
	return ans;
}

int main () {
	v[0] = 1;
	for (int i = 1; i <= 30; i++)
		v[i] = v[i - 1] * 2;

	while (scanf("%d%lf", &n, &t), n && t) {
		printf("%.3lf\n", solve());
	}
	return 0;
}
