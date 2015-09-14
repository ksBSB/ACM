#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 10005;
const double inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;

struct Point {
	double x, y;
	Point (double x = 0, double y = 0): x(x), y(y) {}
	bool operator < (const Point& u) const {
		if (fabs(x - u.x) > eps)
			return x > u.x;
		return y > u.y;
	}
}p[maxn];

double slope(Point a, Point b) {
	if (fabs(a.x - b.x) < eps)
		return 0;
	return (a.y - b.y) / (a.x - b.y);
}

int N, M;

void init () {
	double x, y, z;
	for (int i = 0; i < N; i++) {
		scanf("%lf%lf%lf", &x, &y, &z);
		p[i].x = sqrt(x * x + y * y);
		p[i].y = z;
	}
	sort(p, p + N);

	/*
	M = 0;
	for (int i = 1; i < N; i++) {
		if (p[i].y - p[M].y < eps)
			continue;
		while (M && slope(p[i], p[M-1]) < slope(p[M], p[M-1]))
			M--;
		p[++M] = p[i];
	}
	*/

	/*
	for (int i = 0; i <= M; i++)
		printf("%lf %lf\n", p[i].x, p[i].y);
		*/
}

double find (double r) {
	double ret = 0;
	for (int i = 0; i < N; i++)
		ret = max(ret, p[i].y * r / (r - p[i].x));
	return ret;
}

void solve () {
	double l = p[0].x, r = 1e10;
	while (fabs(r - l) > eps) {
		double rl = l + (r - l) / 3;
		double rr = r - (r - l) / 3;

		double hl = find(rl);
		double hr = find(rr);

		if (rl * rl * hl > rr * rr * hr)
			l = rl;
		else
			r = rr;
	}
	printf("%lf %lf\n", find(l), l);
}

int main () {
	while (scanf("%d", &N) == 1) {
		init ();
		solve ();
	}
	return 0;
}
