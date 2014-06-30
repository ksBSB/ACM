#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;
const int N = 15005;
const double pi = 4.0 * atan(1.0);
const double INF = 0x3f3f3f3f3f3f3f3f;

struct point {
	double x, y;
}p[N];
int n;
double e, th, k;

inline void init () {
	double xi, yi;
	th = th * pi / 180;
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &xi, &yi);
		p[i].x = xi * cos(th) + yi * sin(th);
		p[i].y = -xi * sin(th) + yi * cos(th);
	}
}

inline bool cmpX (const point& a, const point& b) {
	return a.x < b.x;
}

inline bool cmpY (const point& a, const point& b) {
	return a.y < b.y;
}

inline double cat (point a, point b) {
	double xi = fabs(a.x - b.x) / 2;
	double yi = fabs(a.y - b.y) / 2;

	return (k * xi * xi + yi * yi) / k;
}

double solve () {
	double ans = INF;

	sort (p, p + n, cmpX);

	for (int t = 0; t < 2; t++) {
		for (int i = 1; i < n; i++) {
			double tmp = cat(p[i-1], p[i]);
			ans = min (ans, tmp);
		}

		sort (p, p + n, cmpY);
	}
	return ans;
}

int main () {
	int cas = 1;
	while (scanf("%d%lf%lf", &n, &e, &th) == 3 && n && e && th) {
		init ();

		k = 1 - e * e;
		double d = solve ();

		printf("Case %d:\n", cas++);
		if (e == 1)
			printf("%.6lf\n", 0.0);
		else
			printf("%.6lf\n", pi * d * sqrt(k));
	}
	return 0;
}
