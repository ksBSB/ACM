#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 100;
const double INF = 0x3f3f3f3f3f3f;
const double eps = 1e-9;

struct point {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
}p[N];

int n;
double dp[N][N];

double area (point a, point b, point c) {
	return fabs((b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y))/2;
}

bool judge (int a, int b, int c) {
	double cur = area(p[a], p[b], p[c]);
	for (int i = 0; i < n; i++) {
		if (i == a || i == b || i == c)
			continue;
		double tmp = area(p[a], p[b], p[i]) + area(p[b], p[c], p[i]) + area(p[c], p[a], p[i]);
		if (fabs(tmp - cur) < eps)
			return false;
	}
	return true;
}

double solve () {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++)
			dp[j][(j+i)%n] = 0;
	}

	for (int i = 0; i < n; i++)
		dp[i][(i+2)%n] = area(p[i], p[(i+1)%n], p[(i+2)%n]);

	for (int k = 3; k < n; k++) {

		for (int i = 0; i < n; i++) {
			int t = (i + k) % n;
			dp[i][t] = INF;
			for (int j = (i+1)%n; j != t; j = (j+1)%n) {
				if (judge(i, t, j))
					dp[i][t] = min(dp[i][t], max(max(dp[i][j], dp[j][t]), area(p[i], p[j], p[t])));
			}
		}
	}

	double ans = INF;
	for (int i = 0; i < n; i++)
		ans = min (ans, dp[i][(i+n-1)%n]);
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			p[i].get();

		printf("%.1lf\n", solve());
	}
	return 0;
}
