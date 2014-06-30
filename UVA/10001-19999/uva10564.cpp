#include <stdio.h>
#include <string.h>
const int N = 505;
const int M = 50;

long long dp[M][M][N], ans;
int n, l, num[M][M];

void read() {
	memset(num, 0, sizeof(num));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - i; j++)
			scanf("%d", &num[i][j]);
	for (int i = 1; i < n; i++) 
		for (int j = 0; j <= i; j++)
			scanf("%d", &num[n + i - 1][j]);
}

void solve() {
	memset(dp, 0, sizeof(dp));
	int k = 2 * (n - 1);
	for (int i = 0; i <= n; i++)
	   dp[k][i][num[k][i]] = 1;	

	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			int t = num[i + n - 1][j];
			for (int k = num[i + n - 1][j]; k <= 500; k++)
				dp[i + n - 1][j][k] = dp[i + n][j][k - t] + dp[i + n][j + 1][k - t];
		}
	}
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j < n - i; j++) {
			int t = num[i][j];
			for (int k = t; k <= 500; k++) {
				dp[i][j][k] = dp[i + 1][j][k - t];
				if (j > 0)
					dp[i][j][k] += dp[i + 1][j - 1][k - t];
			}
		}
	}
	ans = 0;
	for (int i = 0; i < n; i++)
		ans += dp[0][i][l];
	printf("%lld\n", ans);
}

void dfs(int x, int y, int sum) {
	if (x >= 2 * (n - 1))
		return ;

	if (x < n - 1) {
		if (y && dp[x + 1][y - 1][sum - num[x][y]]) {
			printf("L");
			dfs(x + 1, y - 1, sum - num[x][y]);
		}
		else if (dp[x + 1][y][sum - num[x][y]]) {
			printf("R");
			dfs(x + 1, y, sum - num[x][y]);
		}
	}
	else {
		if (dp[x + 1][y][sum - num[x][y]]) {
			printf("L");
			dfs(x + 1, y, sum - num[x][y]);
		}
		else if (dp[x + 1][y + 1][sum - num[x][y]]) {
			printf("R");
			dfs(x + 1, y + 1, sum - num[x][y]);
		}
	}
}

void print() {
	for (int i = 0; i < n; i++)
		if (dp[0][i][l]) {
			printf("%d ", i);
			dfs(0, i, l);
			return;
		}
}

int main() {
	while (scanf("%d%d", &n, &l), n || l) {
		read();
		solve();
		print();
		printf("\n");
	}
	return 0;
}
