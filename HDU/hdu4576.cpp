#include <stdio.h>
#include <string.h>

const int N = 205;

double dp[2][N];
int n, m, l, r, t, w;

int main () {
	while (scanf("%d%d%d%d", &n, &m, &l, &r) == 4 && n + m + l + r) {

		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;

		for (int i = 1; i <= m; i++) {
			scanf("%d", &w);
			
			int now = i&1;
			int pre = !now;

			for (int j = 0; j < n; j++) {

				if (dp[pre][j] > 0) {
					double val = dp[pre][j]*0.5;

					dp[now][(j+w+n)%n] += val;
					dp[now][(j-w+n)%n] += val;
				}
				dp[pre][j] = 0;
			}
		}

		double ans = 0;
		for (int i = l - 1; i < r; i++)
			ans += dp[m&1][i];
		printf("%.4lf\n", ans);
	}
	return 0;
}
