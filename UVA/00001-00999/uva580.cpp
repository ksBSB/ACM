#include <cstdio>
#include <cstring>

typedef long long ll;
ll dp[40][3];

ll solve (int n) {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;

	for (int i = 1; i <= n; i++) {

		for (int j = 0; j < 3; j++)
			dp[i][0] += dp[i-1][j];

		for (int j = 1; j <= 2; j++)
			dp[i][j] = dp[i-1][j-1];
	}
	ll ans = 0;
	for (int i = 0; i < 3; i++)
		ans += dp[n][i];
	return (1LL<<n)-ans;
}

int main () {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("%lld\n", solve(n));
	}
	return 0;
}
