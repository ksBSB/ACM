#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-8;

double sx, sy, ex, ey;
double v, t;
double vx, vy, wx, wy;

bool judge (double h) {
	if (h > t) {
		sx = ex - vx * t - (h-t) * wx;
		sy = ey - vy * t - (h-t) * wy;
	} else {
		sx = ex - vx * h;
		sy = ey - vy * h;
	}
	return sx * sx + sy * sy <= v * v * h * h;
}

int main () {
	scanf("%lf%lf%lf%lf", &sx, &sy, &ex, &ey);
	scanf("%lf%lf", &v, &t);
	scanf("%lf%lf%lf%lf", &vx, &vy, &wx, &wy);
	ex -= sx, ey -= sy;

	double l = 0, r = 1e20;
	while (r - l > eps) {
		double mid = (l + r) * 0.5;
		if (judge(mid))
			r = mid;
		else
			l = mid;
	}
	printf("%.10lf\n", l);
	return 0;
}
