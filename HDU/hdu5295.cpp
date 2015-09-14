#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-9;

inline int sgn(double x) {
	return x < 0 ? -1 : 1;
}

struct Point {
	double x, y;
	Point (double x = 0, double y = 0) {
		set(x, y);
	}
	void set(double x, double y) {
		this->x = x;
		this->y = y;
	}
	void put() {
		printf("%lf %lf\n", x, y);
	}
	Point operator - (const Point& a) {
		Point ret;
		ret.set(x - a.x, y - a.y);
		return ret;
	}
	Point operator + (const Point& a) {
		Point ret;
		ret.set(x + a.x, y + a.y);
		return ret;
	}
	bool operator == (const Point& a) {
		return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
};

struct Circle {
	Point o;
	double r;
	void set(Point o, double r) {
		this->o = o;
		this->r = r;
	}
	bool operator == (const Circle& a) {
		return o == a.o && fabs(r - a.r) < eps;
	}
};

Circle P, Q;
Point A, A2, B, C, D, G, T;
double AB, BC, CD, DA, EF;

void getPoint(Circle p, Circle q, Point& u, Point& v) {
	if (p == q) {
		u = p.o + Point(0, p.r);
		v = p.o - Point(0, p.r);
		return;
	}

	double a = q.o.x - p.o.x, b = q.o.y - p.o.y;
	double c = (pow(p.r, 2) - pow(q.r, 2) + a * a + b * b) / 2;

	if (fabs(a) > eps && fabs(b) > eps) {
		double delta = b * b * c * c - (a * a + b * b) * (c * c - p.r * p.r * a * a);
		if (sgn(delta) <= 0)
			delta = 0;
		u.y = (b * c + sqrt(delta)) / (a * a + b * b);
		v.y = (b * c - sqrt(delta)) / (a * a + b * b);
		u.x = (c - b * u.y) / a;
		v.x = (c - b * u.y) / a;
	} else if (fabs(a) > eps && fabs(b) < eps) {
		u.x = v.x = c / a;
		double tmp = p.r * p.r - u.x * u.x;
		if (sgn(tmp) <= 0)
			tmp = 0;
		u.y = sqrt(tmp);
		v.y = -u.y;
	} else if (fabs(a) < eps && fabs(b) > eps) {
		u.y = v.y = c / b;
		double tmp = p.r * p.r - u.y * u.y;
		if (sgn(tmp) <= 0)
			tmp = 0;
		u.x = sqrt(tmp);
		v.x = -u.x;
	}
	u = u + p.o;
	v = v + p.o;

}

void solve () {
	B.set(0, 0);
	C.set(BC, 0);
	P.set(B, 2 * EF);
	Q.set(C, DA);
	getPoint(P, Q, A2, T);

	G = A2 + (B - C);

	P.set(G, AB);
	Q.set(C, CD);

	getPoint(P, Q, D, T);
	A = D + (C - A2);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%lf%lf%lf%lf%lf", &AB, &BC, &CD, &DA, &EF);
		printf("Case #%d:\n", kcas);
		solve();
		A.put();
		B.put();
		C.put();
		D.put();
	}
	return 0;
}
