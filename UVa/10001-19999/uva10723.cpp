#include <stdio.h>
#include <string.h>
const int N  = 105;
int min(int a, int b) { return a < b ? a : b; }

int n, m, l[N][N], dp[N][N];
char s1[N], s2[N];

void init() {
	gets(s1);
	gets(s2);
	memset(l, 0, sizeof(l));
	memset(dp, 0, sizeof(dp));
	n = strlen(s1), m = strlen(s2);
	for (int i = 1; i < N; i++)
		l[i][0] = l[0][i] = i, dp[i][0] = dp[0][i] = 1;
	dp[0][0] = 1;
}

void solve() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s1[i - 1] == s2[j - 1]) {
				l[i][j] = l[i - 1][j - 1] + 1;
				dp[i][j] = dp[i - 1][j - 1];
			}
			else {
				l[i][j] = min(l[i - 1][j], l[i][j - 1]) + 1;
				if (l[i - 1][j] < l[i][j - 1])
					dp[i][j] = dp[i - 1][j];
				else if (l[i - 1][j] > l[i][j - 1])
					dp[i][j] = dp[i][j - 1];
				else
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
	}
}

int main() {
	int cas, t = 1;
	scanf("%d%*c", &cas);
	while (cas--) {
		init();
		solve();
		printf("Case #%d: %d %d\n", t++, l[n][m], dp[n][m]);
	}
	return 0;
}
