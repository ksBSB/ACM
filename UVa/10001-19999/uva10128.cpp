#include <stdio.h>
#include <string.h>
const int N = 20;

long long dp[N][N][N];

void init() {
	memset(dp, 0, sizeof(dp));
	dp[1][1][1] = 1;

	for (int i = 2; i <= 13; i++) {
		for (int j = 1; j <= i; j++) {
			int top = i - j + 1;
			for (int k = 1; k <= top; k++)
			   dp[i][j][k] = dp[i - 1][j - 1][k] + dp[i - 1][j][k - 1] + (i - 2) * dp[i - 1][j][k];	
		}
	}
}

int main () {
	int cas, n, p, r;
	scanf("%d", &cas);
	init();
	while (cas--) {
		scanf("%d%d%d", &n, &p, &r);
		printf("%lld\n", dp[n][p][r]);
	}
	return 0;
}
