#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 55;
const double eps = 1e-9;

struct point {
	double x, y;
}p[N];

int n, dp[N][N];

bool cmp (const point& a, const point& b) {
	return a.x < b.x;
}

bool judge (int a, int b, double d, int key) {

	for (int i = a + 1; i <= b; i++) {
		double tmp = p[a].y + d * (p[i].x - p[a].x);

		if (key == 0 && tmp - p[i].y > -eps)
			return false;

		if (key == 1 && tmp - p[i].y < eps)
			return false;
	}
	return true;
}

int solve () {
	memset(dp, 0, sizeof(dp));

	dp[1][0] = dp[0][1] = 1;

	for (int i = 2; i < n-1; i++) {

		int u = i-1;
		for (int j = 0; j < u; j++) {
			dp[i][j] += dp[u][j];
			dp[j][i] += dp[j][u];
			
			double xi = p[i].x - p[j].x;
			double yi = p[i].y - p[j].y;

			double d = yi / xi;

			if (judge(j, u, d, 0))
				dp[u][i] += dp[u][j];

			if (judge(j, u, d, 1))
				dp[i][u] += dp[j][u];
		}
	}

	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			if (dp[i][j] && (i == n-2 || j == n-2)) {
				printf("%d %d: %d\n", i, j, dp[i][j]);
			}
		}
	}
	*/

	int ans = 0, u = n-1;
	for (int i = 0; i < u-1; i++) {

		double xi = p[u].x - p[i].x;
		double yi = p[u].y - p[i].y;

		double d = yi / xi;

		if (judge(i, u-1, d, 0))
			ans += dp[u-1][i];

		if (judge(i, u-1, d, 1))
			ans += dp[i][u-1];
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {

		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		sort(p, p + n, cmp);

		printf("%d\n", solve());
	}
	return 0;
}
