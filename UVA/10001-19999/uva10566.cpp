#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-9;

double X, Y, C;

double solve (double a) {
	double hx = sqrt(X * X - a * a);
	double hy = sqrt(Y * Y - a * a);
	return hx * hy / (hx + hy);
}

double search(double l, double r) {
	while (r - l > eps) {
		double mid = (r + l) / 2;
		if (solve(mid) > C)
			l = mid;
		else
			r = mid;
	}
	return l;
}

int main () {
	while (scanf("%lf%lf%lf", &X, &Y, &C) == 3) {
		printf("%.3lf\n", search(0, min(X, Y)));
	}
	return 0;
}
