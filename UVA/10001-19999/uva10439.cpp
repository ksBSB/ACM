#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1);
const double eps = 1e-5;

struct Point {
	double x, y;
	Point (double x = 0, double y = 0): x(x), y(y) {}
};

struct Line {
	double a, b, c;
	Line (double a = 0, double b = 0, double c = 0): a(a), b(b), c(c) {}
};

Line getLine(double x1, double y1, double x2, double y2) {
	return Line(y2 - y1, x1 - x2, y1 * (x2 - x1) - x1 * (y2 - y1));
}

Line getLine(double ka, double kb, Point u) {
	return Line(ka, -kb, u.y * kb - u.x * ka);
}

double getAngle(double a, double b, double c) {
	return acos( (a * a + b * b - c * c) / (2 * a * b) );
}

bool getCross(Line p, Line q, Point& u) {
	if (fabs(p.a * q.b - q.a * p.b) < eps)
		return false;
	u.x = (q.c * p.b - p.c * q.b) / (p.a * q.b - q.a * p.b);
	u.y = (q.c * p.a - p.c * q.a) / (p.b * q.a - q.b * p.a);
	return true;
}

double distance (Point a, Point b) {
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt(x * x + y * y);
}

bool judge (double a, int n) {
	double t = 2 * pi / n;
	int k = a / t + 0.5;
	//printf("%d\n", k);
	//printf("%lf %lf %lf\n", a / t, k * t, a);

	return fabs(t * k - a) < eps;
}

int main () {
	int cas;
	scanf("%d", &cas);
	double x1, y1, x2, y2, x3, y3;
	while (cas--) {
		scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
		Line ab = getLine(x1 - x2, y2 - y1, Point((x1+x2)/2, (y1+y2)/2));
		Line bc = getLine(x2 - x3, y3 - y2, Point((x2+x3)/2, (y2+y3)/2));

		Point o;
		getCross(ab, bc, o);
		double r = distance(o, Point(x1, y1));

		double a = getAngle(r, r, distance(Point(x1, y1), Point(x2, y2)));
		double b = getAngle(r, r, distance(Point(x2, y2), Point(x3, y3)));
		double c = getAngle(r, r, distance(Point(x1, y1), Point(x3, y3)));

		for (int i = 3; i <= 200; i++) {
			if (judge(a, i) && judge(b, i) && judge(c, i)) {
				printf("%d\n", i);
				break;
			}
		}
		/*
		*/

		//judge(a, 6), judge(b, 6), judge(c, 6);
	}
	return 0;
}
