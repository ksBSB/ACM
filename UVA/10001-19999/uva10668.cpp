#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1.0);

double parabola_length (double w, double x) {
	double r = w / sin(x/2);
	return x * r;
}

double bsearch (double l, double r, double v, double w) {
	for (int i = 0; i < 100; i++) {
		double mid = l + (r - l) / 2;
		if (parabola_length(w, mid) < v)
			l = mid;
		else
			r = mid;
	}
	return r;
}

double solve (double w, double x) {
	return (1 - cos(x/2)) * w / sin(x/2);
}

int main () {
	double L, l, n, c;
	while (scanf("%lf%lf%lf", &L, &n, &c) == 3) {
		if (L < 0 && n < 0 && c < 0)
			break;
		l = (1 + n * c) * L;
		printf("%.3lf\n", solve(L/2, bsearch(0, pi, l, L/2)));
	}
	return 0;
}
