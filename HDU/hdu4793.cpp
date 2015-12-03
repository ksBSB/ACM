#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1);
const double eps = 1e-6;

inline int dcmp(double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
inline double torad(double deg) { return deg / 180 * pi; }

struct Point {
	double x, y;
	Point (double x = 0, double y = 0): x(x), y(y) {}
	void read() { scanf("%lf%lf", &x, &y); }

	Point operator + (const Point& p) { return Point(x+p.x, y+p.y); }
	Point operator - (const Point& p) { return Point(x-p.x, y-p.y); }
};

typedef Point Vector;
double getDot (Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
//double getCross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double getLength (Vector a) { return sqrt(getDot(a, a)); }

struct Circle {
	Point o;
	double r;
	Circle() {}
	Circle(Point o, double r): o(o), r(r) {}
};

int getLineCircleIntersection(Point p, Vector v, Circle O, double& t1, double& t2) {
	double a = v.x, b = p.x - O.o.x, c = v.y, d = p.y - O.o.y;
	double e = a*a+c*c, f = 2*(a*b+c*d), g = b*b+d*d-O.r*O.r;
	double delta = f*f - 4*e*g;
	if (dcmp(delta) < 0) return 0;
	if (dcmp(delta) == 0) {
		t1 = t2 = -f / (2*e);
		return 1;
	}

	t1 = (-f - sqrt(delta)) / (2*e);
	t2 = (-f + sqrt(delta)) / (2*e);
	return 2;
}

double Rm, R, r, X, Y, VX, VY;

int main () {
	while (scanf("%lf%lf%lf%lf%lf%lf%lf", &Rm, &R, &r, &X, &Y, &VX, &VY) == 7) {
		double t1, t2, ans = 0;
		Point P = Point(X, Y);
		Vector V = Vector(VX, VY);
		int tmp = getLineCircleIntersection(P, V, Circle(Point(0, 0), Rm+r), t1, t2);
		if (tmp && dcmp(t1) >= 0) {
			double k = t1;
			getLineCircleIntersection(P, V, Circle(Point(0, 0), R+r), t1, t2);
			ans = (2 * k - t1 - max(t1, 0.0));
		} else if (getLineCircleIntersection(P, V, Circle(Point(0, 0), R+r), t1, t2)) {
			t1 = max(t1, 0.0); t2 = max(t2, 0.0);
			ans = (t2-t1);
		}
		printf("%.3lf\n", ans);
	}
	return 0;
}
