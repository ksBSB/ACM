#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;

const double pi = acos(-1.0);
const int N = 1 << 20;

int n;
double r, l, dp[N];

struct point {
	double x, y, d;
	void scan() {
		scanf("%lf%lf%lf", &x, &y, &d);
		d = d * pi / 180; x -= l; y = fabs(y);
	}
}p[N];

void init() {
	memset(dp, 0, sizeof(dp));
	scanf("%d%lf%lf", &n, &l, &r); r -= l;
	for (int i = 0; i < n; i++) p[i].scan();
}

double f(int id, double x0) {
	double tmp = atan((r - p[id].x) / p[id].y);
	double du = min(tmp, atan((x0 - p[id].x) / p[id].y) + p[id].d);
	return p[id].x + p[id].y * tan(du);
}

double solve() {
	for (int i = 0; i < (1<<n); i++) {
		for (int j = 0; j < n; j++) {
			if (i & (1<<j)) continue;
			dp[i | (1<<j)] = max(dp[i | (1<<j)], f(j, dp[i]));
		}
	}
	return dp[(1<<n) - 1];
}

int main() {
	init();
	printf("%.9lf\n", solve());
	return 0;
}
