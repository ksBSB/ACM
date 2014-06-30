#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 105;
const int M = 1005; 
const int INF = 0x3f3f3f3f;
const double eps = 1e-6;
const double pi = atan(1.0)*4;

struct state {
	int l, r, val;	
}s[M];

struct point {
	double x, y;
	point (double x = 0, double y = 0) { this->x = x; this->y = y;}
	point operator - (const point &o) const {return point(x - o.x, y - o.y);}
	double det(const point &o) const {return x * o.y - y * o.x;}
}p[N], o;
int n, m, dp[N];

inline double dis(double x, double y) {
	return sqrt(x*x+y*y);
}

inline int sign(double x) {return x < -eps ? -1 : x > eps;}

inline double getP(double y, double x) {
	if (fabs(x) < eps) {
		return y > 0 ? -pi : pi;
	}
	return atan2(y, x);
}

bool judge (point l, point a, point b) {
	return sign((l - a).det(b - a) * (o - a).det(b - a)) < 0;
}

void cat (state& u, double xi, double yi) {
	bool flag[N];
	memset(flag, false, sizeof(flag));

	for (int i = 0; i < n; i++) {
		if (judge(point(xi, yi), p[i], p[i+1]))
			flag[i] = true;
	}

	if (flag[0] && flag[n-1]) {
		int l = n-1, r = n;
		while (flag[l]) u.l = l, l--;
		while (flag[r-n]) u.r = r, r++;
		
	} else {
		int l = 0, r = n-1;
		while (!flag[l]) l++;
		u.l = l;
		while (!flag[r]) r--;
		u.r = r;
	}

	u.r++;
	if (u.r < u.l)
		u.r += n;
}	

void init () {

	o.x = o.y = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
		o.x += p[i].x;
		o.y += p[i].y;
	}
	o.x /= n;
	o.y /= n;

	p[n] = p[0];
	double x, y;
	int value;

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%lf%lf%d", &x, &y, &value);
		cat(s[i], x, y);
		s[i].val = value;
	}
}

bool solve () {
	int ans = INF;

	for (int i = 0; i < n; i++) {
		memset(dp, INF, sizeof(dp));
		dp[i] = 0;

		for (int j = 0; j < n; j++) {

			int t = i + j;
			for (int x = 0; x < m; x++) {
				if (s[x].l > t)
					continue;

				int ad = min(s[x].r, i+n);
				dp[ad] = min(dp[ad], dp[t]+s[x].val);
			}
		}
		ans = min(ans, dp[i+n]);
	}

	if (ans == INF)
		return false;
	printf("%d\n", ans);
	return true;
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		init ();
		if (!solve())
			printf("Impossible.\n");
	}
	return 0;
}
