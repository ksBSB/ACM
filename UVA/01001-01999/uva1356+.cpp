#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
double A;

double f (double x) {
	return sqrt (1 + 4 * A * A * x * x);
}

double simpson (double a, double b) {
	double c = (a + b) / 2;
	return (f(a) + 4*f(c) + f(b)) * (b-a) / 6;
}

double asr (double a, double b, double eps, double S) {
	double c = (a + b) / 2;
	double L = simpson(a, c), R = simpson(c, b);
	if (fabs(L+R-S) <= eps * 15)
		return L + R + (L + R - S) / 15;
	return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}

double asr (double a, double b, double eps) {
	return asr(a, b, eps, simpson(a, b));
}

double parabola_length (double w, double h) {
	A = 4 * h / (w * w);
	return asr(0, w / 2, 1e-5) * 2;
}

double bsearch (double l, double r, double d, double v) {
	while (r - l > 1e-5) {
		double mid = (r + l) / 2;
		if (parabola_length(d, mid) < v)
			l = mid;
		else
			r = mid;
	}
	return l;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int D, H, B, L;
		scanf("%d%d%d%d", &D, &H, &B, &L);

		int n = (B + D - 1) / D;
		double d = B * 1.0 / n;
		double l = L * 1.0 / n;

		if (kcas > 1)
			printf("\n");
		printf("Case %d:\n%.2lf\n", kcas, (double)H - bsearch(0, H, d, l));
	}
	return 0;
}
