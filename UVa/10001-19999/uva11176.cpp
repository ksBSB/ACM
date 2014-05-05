#include <stdio.h>
#include <string.h>
const int N = 505;

int n;
double p, pi[N], dp[N][N];

void solve() {
	pi[0] = 1;
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i <= n; i++) {
		pi[i + 1] = pi[i] * p;
		dp[0][i] = 1;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = dp[i - 1][j];
			if (i == j + 1)
				dp[i][j] -= pi[j + 1];
			else if (i > j + 1)
				dp[i][j] -= dp[i - j - 2][j] * (1 - p) * pi[j + 1];
		}
	}

	double ans = 0;
	for (int i = 1; i <= n; i++)
		ans += (dp[n][i] - dp[n][i - 1]) * i;
	printf("%.6lf\n", ans);
}

int main () {
	while (scanf("%d%lf", &n, &p), n) {
		solve();
	}
	return 0;
}
