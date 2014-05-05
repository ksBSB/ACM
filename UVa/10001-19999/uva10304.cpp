#include <stdio.h>
#include <string.h>
const int N = 300;
const int MAX = 1 << 30;
int min(int a, int b) { return a > b ? b : a; }
int n, dp[N][N], sum[N], num[N];

void read() {
	sum[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &num[i]);
		sum[i] = sum[i - 1] + num[i];
	}
}

int solve() {
	memset(dp, 0, sizeof(dp));
	for (int i = 2; i <= n; i++) {
		for (int j = i - 1; j; j--) {
			dp[j][i] = MAX;
			for (int k = j; k <= i; k++) {
				dp[j][i] = min(dp[j][i], dp[j][k - 1] + dp[k + 1][i] + sum[i] - sum[j - 1] - num[k]);
			}
		}
	}
	return dp[1][n];
}

int main() {
	while (scanf("%d", &n) == 1) {
		read();
		printf("%d\n", solve());
	}
	return 0;
}
