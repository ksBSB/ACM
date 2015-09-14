#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const double pi = 4 * atan(1);
const double eps = 1e-10;

inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }
inline double getDistance (double x, double y) { return sqrt(x * x + y * y); }
inline double torad(double deg) { return deg / 180 * pi; }

struct Point {
	int id;
	double x, y, ang;
	Point (double x = 0, double y = 0, double ang = 0, int id = 0): x(x), y(y), ang(ang), id(id) {}
	void read () { scanf("%lf%lf", &x, &y); }

	bool operator < (const Point& u) const { return dcmp(x - u.x) < 0 || (dcmp(x-u.x)==0 && dcmp(y-u.y) < 0); }
	bool operator > (const Point& u) const { return u < *this; }
	bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
	bool operator != (const Point& u) const { return !(*this == u); }
	bool operator <= (const Point& u) const { return *this < u || *this == u; }
	bool operator >= (const Point& u) const { return *this > u || *this == u; }
	Point operator + (const Point& u) { return Point(x + u.x, y + u.y); }
	Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
	Point operator * (const double u) { return Point(x * u, y * u); }
	Point operator / (const double u) { return Point(x / u, y / u); }
	double operator * (const Point& u) { return x*u.y - y*u.x; }
};
typedef Point Vector;

const int maxn = 1005;

int N, V[maxn], C1, C2;
Point A[maxn], B[maxn], T[maxn * 4];

double getCross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double getArea (Point a, Point b, Point c) { return getCross(b - a, c - a) / 2; }
inline int cmp(const Point& a, const Point& b) { return a.ang < b.ang; }

void add (int x) {
	V[x]++;
	if (V[x] == 1)
		C1++;
	else
		C1--, C2++;
}

void del (int x) {
	V[x]--;
	if (V[x] == 0)
		C1--;
	else
		C2--, C1++;
}

double solve(Point* P) {
	double ans = 0;
	for (int i = 0; i < N; i++) {
		int sz = 0;
		for (int j = 0; j < N; j++) if (i != j) {
			T[sz++] = Point(A[j].x, A[j].y, atan2(A[j].y-P[i].y, A[j].x-P[i].x), j);
			T[sz++] = Point(B[j].x, B[j].y, atan2(B[j].y-P[i].y, B[j].x-P[i].x), j);
		}
		for (int j = 0; j < sz; j++) {
			T[sz + j] = T[j];
			T[sz + j].ang += 2 * pi;
		}
		sort(T, T + 2 * sz, cmp);

		int r = 0;
		C1 = C2 = 0;
		memset(V, 0, sizeof(V));

		add(T[r].id);
		for (int j = 0; j < sz; j++) {
			del(T[j].id);
			while (T[r+1].ang - T[j].ang < pi) add(T[++r].id);
			//while (C1 + 2 * C2 != r - j);
			int c = C1 - V[T[j].id];
			if (c + C2 !=  N - 2) continue;
			ans += getArea(Point(0, 0), P[i], T[j]) * pow(0.5, c);
		}
	}
	return ans;
}

int main () {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++) A[i].read(), B[i].read();

		double ans = solve(A) + solve(B);
		printf("%lf\n", ans / 4);
	}
	return 0;
}
