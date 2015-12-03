#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1.0);
const double eps = 1e-8;

inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

struct Point {
	double x, y;
	Point (double x = 0, double y = 0): x(x), y(y) {}
	void read () { scanf("%lf%lf", &x, &y); }

	Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
};

typedef Point Vector;

double getDot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double getLength (Vector a) { return sqrt(getDot(a,a)); }
double getAngle (double a, double b, double c) { return acos((a*a+b*b-c*c) / (2*a*b)); }

struct Circle {
	Point o;
	double r;
	Circle () {}
	Circle (Point o, double r = 0): o(o), r(r) {}
	void read () { o.read(), scanf("%lf", &r); }
	Point point(double rad) { return Point(o.x + cos(rad)*r, o.y + sin(rad)*r); }
	double getArea (double rad) { return rad * r * r / 2; }
};

double getPublicAreaCircleToCircle(Circle a, Circle b) {
	double dis = getLength(a.o - b.o);

	if (dcmp(dis-a.r-b.r) >= 0) return 0;

	if (dis <= fabs(a.r - b.r)) { return min(a.getArea(2*pi), b.getArea(2*pi)); }

	double ang1 = getAngle(a.r, dis, b.r);
	double ang2 = getAngle(b.r, dis, a.r);
	double ret = ang1 * a.r * a.r + ang2 * b.r * b.r - dis * a.r * sin(ang1);
	return ret;
}

const double inf = 0x3f3f3f3f;

int N;
Circle C[30];

bool judge(Circle O) {
	for (int i = 1; i <= N; i++) {
		if (getPublicAreaCircleToCircle(O, C[i]) < C[i].getArea(pi))
			return false;
	}
	return true;
}

double solve (Point p) {
	double l = 0, r = inf;
	for (int i = 0; i < 100; i++) {
		double mid = (l + r) / 2;
		if (judge(Circle(p, mid))) r = mid;
		else l = mid;
	}
	return l;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) C[i].read();
		double ans = inf;
		for (int i = 1; i <= N; i++)
			ans = min(ans, solve(C[i].o));
		printf("%.4lf\n", ans);
	}
	return 0;
}
