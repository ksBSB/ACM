#include <stdio.h>
#include <string.h>
const int N = 105;

long long dp[N][N];
char str[N];

long long solve() {
	memset(dp, 0, sizeof(dp));
	int n = strlen(str);
	for (int i = 0; i < n; i++)
		dp[i][i] = 1;

	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			if (str[i] != str[j])
				dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
			else
				dp[i][j] = dp[i + 1][j] + dp[i][j - 1] + 1;;
		}
	}
	return dp[0][n - 1];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", str);
		printf("%lld\n", solve());
	}
	return 0;
}
