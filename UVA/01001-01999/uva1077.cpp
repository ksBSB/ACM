#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 200005;
const double eps = 1e-8;

struct Point {
	double x, y;
	Point(double x = 0, double y = 0): x(x), y(y) {}

	Point operator + (const Point& u) { return Point(x+u.x, y+u.y); }
	Point operator - (const Point& u) { return Point(x-u.x, y-u.y); }
	Point operator * (const double& k) { return Point(x*k, y*k); }
};
typedef Point Vector;

inline double dcmp(double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

double getCross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double getDot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double getLength(Vector a) { return sqrt(getDot(a, a)); }

/* 判断线段是否存在交点 */
bool haveIntersection (Point a1, Point a2, Point b1, Point b2) {
	double c1=getCross(a2-a1, b1-a1), c2=getCross(a2-a1, b2-a1), c3=getCross(b2-b1, a1-b1), c4=getCross(b2-b1,a2-b1);
	return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}

/* 直线pv和直线qw的交点 */
bool getIntersection (Point p, Vector v, Point q, Vector w, Point& o) {
	if (dcmp(getCross(v, w)) == 0) return false;
	Vector u = p - q;
	double k = getCross(w, u) / getCross(v, w);
	o = p + v * k;
	return true;
}

int N, C;
double X[maxn];
Point L[maxn][2], R[maxn][2];

void init () {
	C = 0;

	double x, h, b;
	for (int i = 0; i < N; i++) {
		scanf("%lf%lf%lf", &x, &h, &b);
		X[C++] = x - b * 0.5;
		X[C++] = x;
		X[C++] = x + b * 0.5;

		L[i][0] = Point(x - b * 0.5, 0);
		R[i][0] = L[i][1] = Point(x, h);
		R[i][1] = Point(x + b * 0.5, 0);
	}

	Point tmp;
	for (int i = 0; i < N; i++) {
		for (int ki = 0; ki < 2; ki++) {
			for (int j = i+1; j < N; j++) {
				for (int kj = 0; kj < 2; kj++) {
					if (haveIntersection (L[i][ki], R[i][ki], L[j][kj], R[j][kj])) {
						getIntersection (L[i][ki], R[i][ki]-L[i][ki], L[j][kj], R[j][kj]-L[j][kj], tmp);
						X[C++] = tmp.x;
					}
				}
			}
		}
	}
}

double find (double x) {
	double ret = 0;
	Point tmp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++) {
			if (dcmp(L[i][j].x -  x) <= 0 && dcmp(x - R[i][j].x) <= 0) {
				//double haha = L[i][j].y + (x - L[i][j].x) / (R[i][j].x - L[i][j].x) * (R[i][j].y - L[i][j].y);
				getIntersection(L[i][j], R[i][j]-L[i][j], Point(x, 0), Vector(0, 1), tmp);
				ret = max(ret, tmp.y);
			}
		}
	}
	return ret;
}

double solve () {
	sort(X, X + C);
	C = unique(X, X + C) - X;

	double ans = 0, pre = find(X[0]);
	for (int i = 1; i < C; i++) {
		double cur = find(X[i]);
		if (dcmp(cur) > 0 || dcmp(pre) > 0)
			ans += getLength(Point(X[i], cur) - Point(X[i-1], pre));
		pre = cur;
	}
	return ans;
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		init();
		printf("Case %d: %.0lf\n\n", cas++, solve());
	}
	return 0;
}
