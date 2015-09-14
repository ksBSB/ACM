#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double pi = 4 * atan(1);
const double eps = 1e-9;

inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
inline double getDistance (double x, double y) { return sqrt(x * x + y * y); }

struct Point {
	double x, y;
	Point (double x = 0, double y = 0): x(x), y(y) {}
	void read () { scanf("%lf%lf", &x, &y); }
	void write () { printf("%lf %lf", x, y); }

	bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
	bool operator != (const Point& u) const { return !(*this == u); }
	bool operator < (const Point& u) const { return x < u.x || (x == u.x && y < u.y); }
	bool operator > (const Point& u) const { return u < *this; }
	bool operator <= (const Point& u) const { return *this < u || *this == u; }
	bool operator >= (const Point& u) const { return *this > u || *this == u; }
	Point operator + (const Point& u) { return Point(x + u.x, y + u.y); }
	Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
	Point operator * (const double u) { return Point(x * u, y * u); }
	Point operator / (const double u) { return Point(x / u, y / u); }
};

typedef Point Vector;

struct Line {
	double a, b, c;
	Line (double a = 0, double b = 0, double c = 0): a(a), b(b), c(c) {}
};


namespace Punctual {
	double getDistance (Point a, Point b) { double x=a.x-b.x, y=a.y-b.y; return sqrt(x*x + y*y); }
};

namespace Vectorial {
	/* 点积: 两向量长度的乘积再乘上它们夹角的余弦, 夹角大于90度时点积为负 */
	double getDot (Vector a, Vector b) { return a.x * b.x + a.y * b.y; }

	/* 叉积: 叉积等于两向量组成的三角形有向面积的两倍, cross(v, w) = -cross(w, v) */
	double getCross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

	double getLength (Vector a) { return sqrt(getDot(a, a)); }
	double getAngle (Vector u) { return atan2(u.y, u.x); }
	double getAngle (Vector a, Vector b) { return acos(getDot(a, b) / getLength(a) / getLength(b)); }
	Vector rotate (Vector a, double rad) { return Vector(a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad)); }
	/* 单位法线 */
	Vector getNormal (Vector a) { double l = getLength(a); return Vector(-a.y/l, a.x/l); }
};

namespace Linear {
	using namespace Vectorial;

	Line getLine (double x1, double y1, double x2, double y2) { return Line(y2-y1, x1-x2, y1*(x2-x1)-x1*(y2-y1)); }
	Line getLine (double a, double b, Point u) { return Line(a, -b, u.y * b - u.x * a); }

	bool getIntersection (Line p, Line q, Point& o) {
		if (fabs(p.a * q.b - q.a * p.b) < eps)
			return false;
		o.x = (q.c * p.b - p.c * q.b) / (p.a * q.b - q.a * p.b);
		o.y = (q.c * p.a - p.c * q.a) / (p.b * q.a - q.b * p.a);
		return true;
	}

	/* 直线pv和直线qw的交点 */
	bool getIntersection (Point p, Vector v, Point q, Vector w, Point& o) {
		if (dcmp(getCross(v, w)) == 0) return false;
		Vector u = p - q;
		double k = getCross(w, u) / getCross(v, w);
		o = p + v * k;
		return true;
	}

	/* 点p到直线ab的距离 */
	double getDistanceToLine (Point p, Point a, Point b) { return fabs(getCross(b-a, p-a) / getLength(b-a)); }
	double getDistanceToSegment (Point p, Point a, Point b) {
		if (a == b) return getLength(p-a);
		Vector v1 = b - a, v2 = p - a, v3 = p - b;
		if (dcmp(getDot(v1, v2)) < 0) return getLength(v2);
		else if (dcmp(getDot(v1, v3)) > 0) return getLength(v3);
		else return fabs(getCross(v1, v2) / getLength(v1));
	}

	/* 点p在直线ab上的投影 */
	Point getPointToLine (Point p, Point a, Point b) { Vector v = b-a; return a+v*(getDot(v, p-a) / getDot(v,v)); }

	/* 判断线段是否存在交点 */
	bool haveIntersection (Point a1, Point a2, Point b1, Point b2) {
		double c1=getCross(a2-a1, b1-a1), c2=getCross(a2-a1, b2-a1), c3=getCross(b2-b1, a1-b1), c4=getCross(b2-b1,a2-b1);
		return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
	}

	/* 判断点是否在线段上 */
	bool onSegment (Point p, Point a, Point b) { return dcmp(getCross(a-p, b-p)) == 0 && dcmp(getDot(a-p, b-p)) < 0; }
}

namespace Triangular {
	using namespace Vectorial;

	double getAngle (double a, double b, double c) { return acos((a*a+b*b-c*c) / (2*a*b)); }
	double getArea (double a, double b, double c) { double s =(a+b+c)/2; return sqrt(s*(s-a)*(s-b)*(s-c)); }
	double getArea (double a, double h) { return a * h / 2; }
	double getArea (Point a, Point b, Point c) { return fabs(getCross(b - a, c - a)) / 2; }
};

namespace Polygonal {
	using namespace Vectorial;
	double getArea (Point* p, int n) {
		double ret = 0;
		for (int i = 1; i < n-1; i++)
			ret += getCross(p[i]-p[0], p[i+1]-p[0]);
		return fabs(ret)/2;
	}
};

using namespace Linear;
const int maxn = 55;
const double inf = 0x3f3f3f3f3f3f3f;

int N, M;
double VP, VQ, SP, SQ;
Point P[maxn], Q[maxn];

void init ()  {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) P[i].read();
	for (int i = 1; i <= M; i++) Q[i].read();

	SP = SQ = 0;
	for (int i = 2; i <= N; i++) SP += getLength(P[i] - P[i-1]);
	for (int i = 2; i <= M; i++) SQ += getLength(Q[i] - Q[i-1]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init ();

		int i = 2, j = 2;
		double ansMax = 0, ansMin = inf;
		Point a = P[1], b = Q[1];

		while (i <= N && j <= M) {
			double tp = getLength(P[i] - a) / SP;
			double tq = getLength(Q[j] - b) / SQ;
			double t = min(tp, tq);


			//Vector va = (P[i] - a) * t / tp;
			Point v = b + (Q[j] - b) * t / tq + (a - P[i]) * t / tp;
			ansMax = max(ansMax, getLength(a - b));
			ansMax = max(ansMax, getLength(a - v));
			ansMin = min(ansMin, getDistanceToSegment(a, b, v));

			a = a + (P[i] - a) * t / tp;
			b = b + (Q[j] - b) * t / tq;
			//a.write(), printf(" "), P[i].write(), printf("!\n");
			//b.write(), printf(" "), Q[j].write(), printf("!!\n");
			if (fabs(tp - t) < eps) i++;
			if (fabs(tq - t) < eps) j++;
			//printf("%d %d!\n", i, j);
			//printf("%lf %lf\n", ansMax, ansMin);
			
		}
		printf("Case %d: %lld\n", kcas, (long long)(ansMax - ansMin + 0.5));
	}
	return 0;
}
