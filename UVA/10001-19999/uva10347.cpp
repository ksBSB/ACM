#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

/* 斯特沃特定理：D为BC上任一点，则有AD*AD*BC+BD*CD*BC = AC*AC*BD + AB*AB*CD */

double getArea(double a, double b, double c) {
	double s =(a + b + c) / 2;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main () {
	double a, b, c;
	while (scanf("%lf%lf%lf", &a, &b, &c) == 3) {

		if (a <= 0 || b <= 0 || c <= 0)
			printf("-1.000\n");
		else if (a + b <= c || a + c <= b || b + c <= a)
			printf("-1.000\n");
		else {
			a = a * a, b = b * b, c = c * c;
			double x = sqrt(2 * b + 2 * c - a) / 3;
			double y = sqrt(2 * c + 2 * a - b) / 3;
			double z = sqrt(2 * a + 2 * b - c) / 3;
			printf("%.3lf\n", getArea(x * 2, y * 2, z * 2));
		}
	}
	return 0;
}
