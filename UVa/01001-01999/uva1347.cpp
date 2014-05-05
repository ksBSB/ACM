#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>

using namespace std;
const int N = 105;
const double INF = 0x3f3f3f3f3f3f3f3f;

int n;
double x[N], y[N], dp[N][N];

inline double dis (int a, int b) {
	return sqrt((x[a]-x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]));
}

void init () {

	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &x[i], &y[i]);

	memset(dp, 0, sizeof(dp));
	dp[2][1] = dis(1, 2);
}

double solve () {
	for (int i = 3; i <= n; i++) {
		dp[i][i-1] = INF;

		for (int j = 1; j < i-1; j++) {
			dp[i][i-1] = min(dp[i][i-1], dp[i-1][j] + dis(i, j));
			dp[i][j] = dp[i-1][j] + dis(i, i-1);
		}
	}

	double ans = INF;
	for (int i = 1; i < n; i++)
		ans = min(ans, dp[n][i] + dis(n, i));
	return ans;
}

int main () {
	while (scanf("%d", &n) == 1) {
		init ();
		printf("%.2lf\n", solve ());
	}
	return 0;
}
