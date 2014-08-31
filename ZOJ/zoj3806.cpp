#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

double f (double a, double R) {
	double t = sqrt(R * R - a * a / 4) + R;
	return sqrt(t * t + a * a / 4);
}

double judge (double a, double b, double R) {
	return a * b * b / (2 * R  * (a + b + b));
}

double bsearch (double l, double R, double v) {
	double r = sqrt(3.0) * R;

	for (int i = 0; i < 1000; i++) {
		double mid = (l + r) / 2;
		double x = f(mid, R);
		if (judge(mid, x, R) > v)
			r = mid;
		else
			l = mid;
	}
	return (l + r) / 2;
}

int main () {
	int r, R;
	while (scanf("%d%d", &r, &R) == 2) {
		if (r * 2 > R)
			printf("NO Solution!\n");
		else {
			double a = bsearch(0, R, r);
			double b = f(a, R);
			printf("%.10lf %.10lf %.10lf\n", a, b, b);
		}
	}
	return 0;
}
