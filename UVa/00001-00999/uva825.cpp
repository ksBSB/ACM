#include <stdio.h>
#include <string.h>
const int N = 1005;

int n, m, dp[N][N], g[N][N];

void handle(int k, char str[]) {
	int len = strlen(str), num = 0;
	for (int i = 0; i <= len; i++) {
		if (str[i] >= '0' && str[i] <= '9')
			num = num * 10 + str[i] - '0';
		else {
			g[k][num] = 1;
			num = 0;
		}
	}
}

void read() {
	int r;
	char str[N];
	memset(dp, 0, sizeof(dp));
	memset(g, 0, sizeof(g));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &r);
		gets(str);
		handle(r, str);
	}
}

int solve () {
	dp[0][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (g[i][j])	continue;
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[n][m];
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		read();
		printf("%d\n", solve());
		if (cas) printf("\n");
	}
	return 0;
}
