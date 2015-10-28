#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const double pi = 4 * atan(1);
const double eps = 1e-8;

inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
inline double getDistance (double x, double y) { return sqrt(x * x + y * y); }
inline double torad(double deg) { return deg / 180 * pi; }

struct Point {
	double x, y;
	Point (double x = 0, double y = 0): x(x), y(y) {}
	void read () { scanf("%lf%lf", &x, &y); }
	void write () { printf("%lf %lf", x, y); }

	bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
	bool operator != (const Point& u) const { return !(*this == u); }
	bool operator < (const Point& u) const { return dcmp(x - u.x) < 0 || (dcmp(x-u.x)==0 && dcmp(y-u.y) < 0); }
	bool operator > (const Point& u) const { return u < *this; }
	bool operator <= (const Point& u) const { return *this < u || *this == u; }
	bool operator >= (const Point& u) const { return *this > u || *this == u; }
	Point operator + (const Point& u) { return Point(x + u.x, y + u.y); }
	Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
	Point operator * (const double u) { return Point(x * u, y * u); }
	Point operator / (const double u) { return Point(x / u, y / u); }
	double operator ^ (const Point& u) { return x*u.y - y*u.x; }
};
typedef Point Vector;

struct Circle {
	Point o;
	double r;
	Circle () {}
	Circle (Point o, double r = 0): o(o), r(r) {}
	void read () { o.read(), scanf("%lf", &r); }
	Point point(double rad) { return Point(o.x + cos(rad)*r, o.y + sin(rad)*r); }
	double getArea (double rad) { return rad * r * r / 2; }
};

/* 点积: 两向量长度的乘积再乘上它们夹角的余弦, 夹角大于90度时点积为负 */
double getDot (Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
/* 叉积: 叉积等于两向量组成的三角形有向面积的两倍, cross(v, w) = -cross(w, v) */
double getCross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

double getLength (Vector a) { return sqrt(getDot(a, a)); }
double getAngle (Vector u) { return atan2(u.y, u.x); }
double getAngle (Vector a, Vector b) { return acos(getDot(a, b) / getLength(a) / getLength(b)); }

/* 直线pv和直线qw的交点 */
bool getIntersection (Point p, Vector v, Point q, Vector w, Point& o) {
	if (dcmp(getCross(v, w)) == 0) return false;
	Vector u = p - q;
	double k = getCross(w, u) / getCross(v, w);
	o = p + v * k;
	return true;
}

/* 判断线段是否存在交点 */
bool haveIntersection (Point a1, Point a2, Point b1, Point b2) {
	double c1=getCross(a2-a1, b1-a1), c2=getCross(a2-a1, b2-a1), c3=getCross(b2-b1, a1-b1), c4=getCross(b2-b1,a2-b1);
	return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}

/* 判断点是否在线段上 */
bool onSegment (Point p, Point a, Point b) { return dcmp(getCross(a-p, b-p)) == 0 && dcmp(getDot(a-p, b-p)) < 0; }

/* 直线和原的交点 */
int getLineCircleIntersection (Point p, Point q, Circle O, vector<Point>& sol) {
	double t1, t2;
	Vector v = q - p;
	sol.clear();

	double a = v.x, b = p.x - O.o.x, c = v.y, d = p.y - O.o.y;
	double e = a*a+c*c, f = 2*(a*b+c*d), g = b*b+d*d-O.r*O.r;
	double delta = f*f - 4*e*g;
	if (dcmp(delta) < 0) return 0;
	if (dcmp(delta) == 0) {
		t1 = t2 = -f / (2 * e);
		sol.push_back(p + v * t1);
		return 1;
	}

	t1 = (-f - sqrt(delta)) / (2 * e); sol.push_back(p + v * t1);
	t2 = (-f + sqrt(delta)) / (2 * e); sol.push_back(p + v * t2);
	return 2;
}

void getTriangleIntersection(Point s, Point e, Point a, Point b, Point c, vector<Point>& sol) {
	Point t;
	sol.clear();
	if (haveIntersection(s, e, a, b)) {
		getIntersection (s, e-s, a, b-a, t);
		sol.push_back(t);
	}

	if (haveIntersection(s, e, b, c)) {
		getIntersection (s, e-s, b, c-b, t);
		sol.push_back(t);
	}

	if (haveIntersection(s, e, c, a)) {
		getIntersection (s, e-s, c, a-c, t);
		sol.push_back(t);
	}
}

//bool getIntersection (Point p, Vector v, Point q, Vector w, Point& o);
//int getLineCircleIntersection (Point p, Point q, Circle O, double& t1, double& t2, vector<Point>& sol) {

struct State {
	double t;
	int k;
	State(double t = 0, int k = 0): t(t), k(k) {}
	bool operator < (const State& u) const {
		if (dcmp(t - u.t)) return t < u.t;
		return k > u.k;
	}
};

double V1, V2, V, T, X;
vector<State> pos;

double getTime(Point a, Vector v, Point b) { return (b.x - a.x) / v.x; }

void init () {
	pos.clear();
	scanf("%lf%lf%lf%lf%lf", &V1, &V2, &V, &T, &X);

	double L = 0, R = V1 * T / (V2 - V1)  + T;

	int n;
	double x, y, r, h;
	vector<Point> sol;
	vector<double> tim;

	Point B = Point(X, 0);
	Vector dir = Vector(-V1, V);
	Point E = B + dir * R;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf%lf%lf", &x, &y, &r, &h);

		tim.clear();
		getLineCircleIntersection(B, E, Circle(Point(x, y), r), sol);

		for (int i = 0; i < sol.size(); i++) {
			if (dcmp(sol[i].y - y) > 0) continue;
			tim.push_back(getTime(B, dir, sol[i]));
		}

		getTriangleIntersection(B, E, Point(x-r, y), Point(x+r, y), Point(x, y+h), sol);
		for (int i = 0; i < sol.size(); i++) {
			tim.push_back(getTime(B, dir, sol[i]));
		}
		sort(tim.begin(), tim.end());
		if (tim.size() <= 1) continue;

		double l = max(L, tim[0]), r = min(R, tim[tim.size()-1]);
		if (dcmp(l - r) > 0) continue;
		pos.push_back(State(l, 1));
		pos.push_back(State(r, -1));
	}
}

double solve () {
	double ret = 0;
	sort(pos.begin(), pos.end());
	int n = pos.size(), k = 1;
	for (int i = 1; i < n; i++) {
		if (k > 0) ret += pos[i].t - pos[i-1].t;
		k += pos[i].k;
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d: %.4lf\n", kcas, solve());
	}
	return 0;
}
