#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <climits>
const int N = 15;
int min(int a, int b) { return a > b ? b : a; }

int n, k;
int day[N][N], val[N][N][N + 20], dp[N][1005];

void read() {
	memset(day, 0, sizeof(day));
	memset(val, 0, sizeof(val));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i != j) {
				scanf("%d", &day[i][j]);
				for (int t = 1; t <= day[i][j]; t++)
					scanf("%d", &val[i][j][t]);
			}
		}
	}

	for (int i = 0; i <= n; i++)
		for (int t = 0; t <= k; t++)
			dp[i][t] = INT_MAX;
}

void solve() {
	dp[1][0] = 0;
	for (int d = 1; d <= k; d++) {
		for (int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if (i != j) {
					int t = (d - 1) % day[j][i] + 1;
					if (val[j][i][t] && dp[j][d - 1] != INT_MAX)
						dp[i][d] = min(dp[i][d], dp[j][d - 1] + val[j][i][t]);
				}
			}
		}
	}
}

int main() {
	int cas = 1;
	while (scanf("%d%d", &n, &k) && n && k) {
		read();
		printf("Scenario #%d\n", cas++);
		solve();
		if (dp[n][k] == INT_MAX)
			printf("No flight possible.\n\n");
		else
			printf("The best flight costs %d.\n\n", dp[n][k]);
	}
	return 0;
}
