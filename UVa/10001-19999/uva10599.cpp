#include <stdio.h>
#include <string.h>
const int N = 105;
const int MAX = 10005;

int row, col, n, dp[MAX], cnt[MAX], rec[MAX], flag, map[N][N];
int g[MAX];


void init() {
	int a, b;
	memset(map, 0, sizeof(map));
	while (scanf("%d%d", &a, &b), a && b) {
		map[a][b] = 1;
	}

	n = 0;
	memset(g, 0, sizeof(g));
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++)
			if (map[i][j])
				g[n++] = (i - 1) * col + j - 1;
	}
	if (g[n - 1] != row * col - 1)
		g[n++] = row * col - 1;
}

void solve() {

	for (int i = 0; i < n; i++) {
		dp[i] = 1, cnt[i] = 1, rec[i] = -1;
		for (int j = 0; j < i; j++) {
			if ((g[j] % col) <= (g[i] % col)) {
				if (dp[i] == dp[j] + 1)
					cnt[i] += cnt[j];
				else if (dp[i] < dp[j] + 1)
					dp[i] = dp[j] + 1, cnt[i] = cnt[j], rec[i] = j;
			}
		}
	}
	if (!map[row][col])
		dp[n - 1]--;
}

void put(int cur) {
	if (rec[cur] != -1)
		put(rec[cur]);
	if (cur != n - 1 || map[row][col])
		printf(" %d", g[cur] + 1);
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &row, &col) == 2) {
		if (row == -1 && col == -1) break;
		init();
		solve();
		printf("CASE#%d: %d %d", cas++, dp[n - 1], cnt[n - 1]);
		put(n - 1);
		printf("\n");
	}
	return 0;
}

