#include <stdio.h>
#include <string.h>
const int N = 1005;
const int M = 105;
const int MAX = 1 << 30;
int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int n, m, ans, dp[N], val[M];

int solve() {
	memset(dp, 0, sizeof(dp));
	dp[0] = 1 << 30;
	for (int i = 0; i < n; i++) {
		for (int j = m; j >= 0; j--) {
			for (int k = 1; k <= j && k <= val[i]; k++)
				dp[j] = max(dp[j], min(dp[j - k], val[i] / k));
		}
	}
	return dp[m];
}

int find() {
	if(ans == 0) return 0;
	for (int i = 1; i <= m; i++)
		dp[i] = MAX;
	dp[0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = m; j >= 0; j--) {
			for (int k = min(j, val[i] / ans); k > 0; k--)
				dp[j] = min(dp[j], dp[j - k] + val[i]);
		}
	}
	return dp[m];
}

int main() {
	while (scanf("%d%d", &m, &n), n || m) {
		for (int i = 0; i < n; i++)
			scanf("%d", &val[i]);
		ans = solve();
		printf("%d %d\n", ans, find());
	}
	return 0;
}
