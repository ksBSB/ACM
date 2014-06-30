#include <cstdio>
#include <cstring>

const int N = 305;
int n, m, ans[N][N], dp[N][N];

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

void init () {
	memset(dp, 0, sizeof(dp));
	memset(ans, 0, sizeof(ans));

	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++)
			dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + (gcd(i,j) == 1 ? 1 : 0);

	for (int i = 1; i < N; i++)
		for (int j = 1; j < N; j++)
			ans[i][j] = ans[i-1][j] + ans[i][j-1] - ans[i-1][j-1] + dp[i][j] - dp[i/2][j/2];
}

int main () {
	init ();
	while (scanf("%d%d", &n, &m) == 2 && n && m) {
		printf("%d\n", ans[n-1][m-1] * 2);
	}
	return 0;
}
