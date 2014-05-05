#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 2050;
const int MOD = 1e9+7;

int	n, k, s[N];
int dp[N][N][2];

int solve () {

	for (int i = 1; i <= n; i++) {
		if (s[i] == 2 || s[i] == 0) {
			for (int j = 0; j < N; j++) {
				int p = min(j + 2, 2049);
				dp[i][p][1] = (dp[i][p][1] + dp[i-1][j][1])%MOD;
				dp[i][p][0] = (dp[i][p][0] + dp[i-1][j][0])%MOD;
			}
		}

		if (s[i] == 4 || s[i] == 0) {
			for (int j = 0; j < N; j++) {
				int p = min(j + 4, 2049);

				if (j%4) {
					if (j >= (1<<k))
						dp[i][4][1] = (dp[i][4][1] + dp[i-1][j][0])%MOD;
					else
						dp[i][4][0] = (dp[i][4][0] + dp[i-1][j][0])%MOD;

					dp[i][4][1] = (dp[i][4][1] + dp[i-1][j][1])%MOD;
				} else {
					dp[i][p][0] = (dp[i][p][0] + dp[i-1][j][0])%MOD;
					dp[i][p][1] = (dp[i][p][1] + dp[i-1][j][1])%MOD;
				}
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < 2050; i++) {
		ans = (ans + dp[n][i][1])%MOD;
		if (i >= (1<<k))
			ans = (ans + dp[n][i][0])%MOD;
	}
	return ans;
}

int main () {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &s[i]);

	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	printf("%d\n", solve());
	return 0;
}
