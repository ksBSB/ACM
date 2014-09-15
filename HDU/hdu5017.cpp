#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double INF = 10000;
const double eps = 1e-9;
double a, b, c, d, e, f;

double get(double A, double B, double C) {
	if (B * B - 4 * A * C < eps)
		return INF;
	return (sqrt(B * B - 4 * A * C) - B) / (2 * A);
}

double func (double x, double y) {
	double z = get(c, e * x + d * y, a * x * x + b * y * y + f * x * y - 1);
	return x * x + y * y + z * z;
}

double search (double x) {
	double l = -INF, r = INF;
	for (int i = 0; i < 200; i++) {
		double ll = l + (r - l) / 3;
		double rr = r - (r - l) / 3;
		if (func(x, ll) > func(x, rr))
			l = ll;
		else
			r = rr;
	}
	return func(x, l);
}

double solve (double l, double r) {
	for (int i = 0; i < 200; i++) {
		double ll = l + (r - l) / 3;
		double rr = r - (r - l) / 3;
		if (search(ll) > search(rr))
			l = ll;
		else
			r = rr;
	}
	return sqrt(search(l));
}

int main () {
	while (scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f) == 6) {
		printf("%.5lf\n", solve(-INF, INF));
	}
	return 0;
}
