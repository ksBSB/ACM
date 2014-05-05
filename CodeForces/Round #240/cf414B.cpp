#include <stdio.h>
#include <string.h>
#include <math.h>

const int N = 2005;
const int MOD = 1e9+7;

int n, k, dp[N][N];

int main () {
	memset(dp, 0, sizeof(dp));
	dp[0][1] = 1;
	scanf("%d%d", &n, &k);

	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			int t = sqrt(j);
			for (int k = 1; k <= t; k++) {
				if (j % k) continue;
				dp[i][j] = (dp[i][j] + dp[i-1][k])%MOD;

				if (j/k != k) {
					int x = j/k;
					dp[i][j] = (dp[i][j] + dp[i-1][x])%MOD;
				}
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = (ans + dp[k][i]) % MOD;
	printf("%d\n", ans);

	return 0;
}
