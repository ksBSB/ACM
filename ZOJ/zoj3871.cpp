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
	ll x, y;
	double ang;
	Point (ll x = 0, ll y = 0): x(x), y(y) {}
	void read () { scanf("%lld%lld", &x, &y); }
	//void write () { printf("%d %d", x, y); }

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
const int mod = 998244353;

int N, pow2[maxn];
Point P[maxn], T[maxn * 2];

ll getCross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
ll getArea (Point a, Point b, Point c) { return (getCross(b - a, c - a) % mod + mod) % mod; }

inline bool cmp(const Point& a, const Point& b) { return a.ang < b.ang; }

int main () {
	pow2[0] = 1;
	for (int i = 1; i < maxn; i++) pow2[i] = pow2[i-1] * 2 % mod;
	for (int i = 0; i < maxn; i++) pow2[i] = (pow2[i] - 1 + mod) % mod;

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) P[i].read();

		ll ans = 0;
		for (int i = 0; i < N; i++) {
			int sz = 0;
			for (int j = 0; j < N; j++) if (i != j) {
				T[sz] = P[j];
				T[sz++].ang = atan2(P[j].y-P[i].y, P[j].x-P[i].x);
			}
			for (int j = 0; j < sz; j++) {
				T[j+sz] = T[j];
				T[j+sz].ang += pi * 2;
			}
			sort(T, T + sz * 2, cmp);
			int r = 0;
			for (int j = 0; j < sz; j++) {
				while (T[r+1].ang - T[j].ang < pi) r++;
				ans = (ans + getArea(Point(0, 0), P[i], T[j]) % mod * pow2[r-j]) % mod;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
