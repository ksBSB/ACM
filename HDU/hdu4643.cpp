#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const double eps = 1e-10;

inline int dcmp(double x) { if (fabs(x)<eps) return 0; else return x < 0 ? -1 : 1; }

struct Point {
	double x, y;
	Point (double x = 0, double y = 0): x(x), y(y) {}
	void read() { scanf("%lf%lf", &x, &y); }

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

double getDot (Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double getCross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double getLength (Vector a) { return sqrt(getDot(a, a)); }
Vector getNormal (Vector a) { double l = getLength(a); return Vector(-a.y/l, a.x/l); }

bool getIntersection (Point p, Vector v, Point q, Vector w, Point& o) {
	if (dcmp(getCross(v, w)) == 0) return false;
	Vector u = p - q;
	double k = getCross(w, u) / getCross(v, w);
	o = p + v * k;
	return true;
}

const int maxn = 55;

int N, M;
Point city[maxn], base[maxn];

double getDistance(double x, double y) { return sqrt(x*x+y*y); }

int getClose(Point t) {
	int ret = -1;
	double dis = 1e20;
	for (int i = 0; i < M; i++) {
		double tmp = getDistance(t.x - base[i].x, t.y - base[i].y);
		if (dcmp(tmp - dis) <= 0) {
			dis = tmp;
			ret = i;
		}
	}
	return ret;
}

int solve (Point s, Point e) {
	int la = getClose(s), lb = getClose(e);
	if (la == lb) return 0;
	if (dcmp(getLength(e-s)) == 0) return 1;
	Point mid = (s + e) * 0.5;
	return solve(s, mid) + solve(mid, e);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		for (int i = 0; i < N; i++) city[i].read();
		for (int i = 0; i < M; i++) base[i].read();

		int k, u, v;
		scanf("%d", &k);
		while (k--) {
			scanf("%d%d", &u, &v);
			printf("%d\n", solve(city[u-1], city[v-1]));
		}
	}
	return 0;
}
