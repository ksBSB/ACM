#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const double eps = 1e-9;
double A, B, C, D, L, R;

double function(double x) {
	if (x >= L && x <= R) {
		double y = A * x * x * x + B * x * x + C * x + D;
		return fabs(y);
	}
	return -1;
}

double solve (double a, double b, double c) {
	if (fabs(a) < eps) {
		if (fabs(b) < eps)
			return -1;
		else
			return function(- c / b);
	}

	double dta = b * b - 4 * a * c;
	if (dta > 0) {
		dta = sqrt(dta);
		return max(function( (-b + dta) / 2 / a ), function( (-b - dta) / 2 / a) );
	}
	return -1;
}

int main () {

	while (~scanf("%lf%lf%lf%lf%lf%lf", &A, &B, &C, &D, &L, &R)) {
		double ans = max(function(L), function(R));
		ans = max(ans, solve(3*A, 2*B, C));
		while (ans < 0);
		printf("%.2lf\n", ans);
	}
	return 0;
}
