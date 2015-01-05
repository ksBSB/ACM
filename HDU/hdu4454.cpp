#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-9;
const double pi = 4 * atan(1.0);

struct point {
	double x, y;
	point(double x = 0, double y = 0) {
		this->x = x;
		this->y = y;
	}
}s, o, p[4];

double R;

inline double distant(point u, point v) {
	double x = u.x - v.x;
	double y = u.y - v.y;
	return sqrt(x*x + y*y);
}

inline double handle(point u, point l, point r) {
	if (fabs(l.x - r.x) < eps) {
		double a = min(l.y, r.y), b = max(l.y, r.y);
		if (a <= u.y && u.y <= b)
			return fabs(u.x - l.x);
		else
			return min(distant(u, l), distant(u, r));
	} else {
		double a = min(l.x, r.x), b = max(l.x, r.x);
		if (a <= u.x && u.x <= b)
			return fabs(u.y - l.y);
		else
			return min(distant(u, l), distant(u, r));
	} 
}

inline double f(double k) {
	point u(o.x + R * cos(k), o.y + R * sin(k));
	double ret = handle(u, p[0], p[3]);
	for (int i = 0; i < 3; i++)
		ret = min(ret, handle(u, p[i], p[i+1]));
	return distant(s, u) + ret;
}

double solve (double l, double r) {
	for (int i = 0; i < 100; i++) {
		double x1 = l + (r-l) / 3;
		double x2 = r - (r-l) / 3;
		if (f(x1) < f(x2))
			r = x2;
		else
			l = x1;
	}
	return f(l);
}

void init () {
	double a, b, c, d;
	scanf("%lf%lf%lf", &o.x, &o.y, &R);
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	p[0].x = min(a, c); p[0].y = min(b, d);
	p[1].x = min(a, c); p[1].y = max(b, d);
	p[2].x = max(a, c); p[2].y = max(b, d);
	p[3].x = max(a, c); p[3].y = min(b, d);
	/*
	for (int i = 0; i < 4; i++)
		printf("%lf %lf\n", p[i].x, p[i].y);
		*/
}

int main () {
	while (scanf("%lf%lf", &s.x, &s.y) == 2 && (fabs(s.x) > eps || fabs(s.y) > eps)) {
		init();
		printf("%.2lf\n", solve(0, 2 * pi));
	}
	return 0;
}
