#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const double eps = 1e-10;
inline int dcmp(double e) { if (fabs(e) < eps) return 0; return e < 0 ? -1 : 1; }

struct Point {
	double x, y;
	void read() { scanf("%lf%lf", &x, &y); }
	Point(double x = 0, double y = 0): x(x), y(y) {}

	Point operator < (const Point& u) const { return x < u.x || (dcmp(x - u.x) == 0 && y < u.y); }
	Point operator + (const Point& u) const { return Point(x + u.x, y + u.y); }
	Point operator - (const Point& u) const { return Point(x - u.x, y - u.y); }
	Point operator * (const double& k) const { return Point(x * k, y * k); }
	Point operator / (const double& k) const { return Point(x / k, y / k); }
};

typedef Point Vector;

double getDot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double getCross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double getLength(Vector a) { return sqrt(getDot(a, a)); }
Vector rotate(Vector v, double rad) { return Vector(v.x * cos(rad) - v.y * sin(rad), v.x * sin(rad) + v.y * cos(rad)); }
double getArea(Point a, Point b, Point c) { return getCross(b - a, c - a); }

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

struct Segment {
	Point s, e;
	Segment(Point s, Point e): s(s), e(e) {}
	Point point(double k) { return s + (e - s) * k; }
};

/**********************************************/
const int maxn = 55;
const int maxm = 1e5 + 5;
typedef pair<double,int> pdi;

int N, M;
double ans[maxn], len[maxn], event[maxm];
Point P[maxn][4];
pdi T[maxn<<1];

bool checkVertical() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++)
			if (dcmp(P[i][j].x - P[i][j+1].x) == 0) return true;
	}
	return false;
}

void adjust() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 4; j++)
			P[i][j] = rotate(P[i][j], 0.001);
	}
}

void init () {
	int n = N = M = 0;
	scanf("%d", &n);
	while (n--) {
		for (int i = 0; i < 3; i++) P[N][i].read();
		P[N][3] = P[N][0];
		if (dcmp(getArea(P[N][0], P[N][1], P[N][2]))) N++;
	}

	while (checkVertical()) adjust();
}

inline bool onSegment(Point p, Point a, Point b) { return dcmp(getDot(a - p, b - p)) <= 0;}

bool verticalPos(Point l, Point r, int id, double& in, double& ot) {
	int c = 0;
	double y[3];
	Point tmp;

	//printf("%lf %lf %lf %lf\n", l.x, l.y, r.x, r.y);

	for (int i = 0; i < 3; i++) {
		getIntersection(l, r-l, P[id][i], P[id][i+1]-P[id][i], tmp);
		if (onSegment(tmp, P[id][i], P[id][i+1]))
			y[c++] = tmp.y;
	}
	sort(y, y + c);
	if (c <= 1) return false;
	in = y[0], ot = y[c-1];
	return true;
}

void calculate (double x) {
	int c = 0;
	double in, ot;
	Point a = Point(x, 0), b = Point(x, 1);
	for (int i = 0; i < N; i++) {
		if (verticalPos(a, b, i, in, ot)) {
			T[c++] = make_pair(in, 1);
			T[c++] = make_pair(ot, -1);
		}
	}
	sort(T, T + c);
	int mv = 0;
	for (int i = 0; i < c; i++) {
		if (mv > 0) len[mv] += T[i].first - T[i-1].first;
		mv += T[i].second;
	}
}

void getPosition() {
	for (int i = 0; i < N; i++) {
		for (int ki = 0; ki < 3; ki++) {
			Point a = P[i][ki], b = P[i][ki+1];
			event[M++] = a.x;
			for (int j = i + 1; j < N; j++) {
				for (int kj = 0; kj < 3; kj++) {
					Point c = P[j][kj], d = P[j][kj+1], e;
					if (haveIntersection(a, b, c, d)) {
						getIntersection(a, b-a, c, d-c, e);
						event[M++] = e.x;
					}
				}
			}
		}
	}

	sort(event, event + M);
	M = unique(event, event + M) - event;
}

void solve() {
	getPosition();
	memset(ans, 0, sizeof(ans));

	for (int i = 1; i < M; i++) {
		memset(len, 0, sizeof(len));
		calculate(event[i-1] - eps);
		calculate(event[i] + eps);

		double x = event[i] - event[i-1];
		for (int j = 1; j <= N; j++)
			ans[j] += len[j] * x / 2;
	}

	for (int i = 1; i <= N; i++)
		printf("%.4lf\n", ans[i]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
