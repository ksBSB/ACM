#include  <stdio.h>
#include <string.h>
const int N = 80;

int dp[N][N];

void init() {
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < N; i++) dp[1][i] = dp[i][0] = 1;

	for (int i = 2; i < N; i++) {
		dp[i][1] = i;
		for (int j = 2; j < N; j++)
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
	}
}

int main() {
	init();
	int cas, n, t, p;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d", &n, &t, &p);
		if (t >= p * n)
			printf("%d\n", dp[n][t - p * n]);
		else
			printf("0\n");
	}
	return 0;
}
