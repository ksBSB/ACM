#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
const int M = 27;
const int N = 10005;

int dp[M][M][N], sum[M][N];

void init() {
	memset(dp, 0, sizeof(dp));
	memset(sum, 0, sizeof(sum));

	dp[0][0][0] = 1;
	for (int i = 1; i <= 26; i++) {
		int top = i * 26;
		for (int k = 1; k <= top; k++) {
			int n = min(k, 26);
			for (int j = 1; j <= n; j++) {
				for (int t = 0; t < j; t++)
					dp[i][j][k] += dp[i - 1][t][k - j];
				sum[i][k] += dp[i][j][k];
			}
		}
	}
}
int main () {
	init();
	int l, s, cas = 1;
	while (scanf("%d%d", &l, &s), l + s) {
		l = min(l, 26);
		printf("Case %d: %d\n", cas++, sum[l][s]);
	}
	return 0;
}
