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
	//double ang1 = acos((a.r * a.r + dis * dis - b.r * b.r) / 2. / a.r / dis);
	//double ang2 = acos((b.r * b.r + dis * dis - a.r * a.r) / 2. / b.r / dis);
	double ret = ang1 * a.r * a.r + ang2 * b.r * b.r - dis * a.r * sin(ang1);
	return ret;
}

int main () {
	double x1, y1, r1, x2, y2, r2;
	while (scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &r1, &x2, &y2, &r2) == 6) {
		Circle a = Circle(Point(x1, y1), r1);
		Circle b = Circle(Point(x2, y2), r2);
		printf("%.3lf\n", getPublicAreaCircleToCircle(a, b));
	}
	return 0;
}
