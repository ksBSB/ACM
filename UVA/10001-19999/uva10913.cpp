#include <stdio.h>
#include <string.h>
const int N = 80;
const int MAX = -200000000;
const int dir[3][2] = {{0, -1}, {0, 1}, {1, 0}};

int n, k, vis[N][N], g[N][N];
long long dp[N][N][10][5], ans;

void init() {
	ans = MAX;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int x = 0; x < 6; x++)
				for (int y = 0; y < 3; y++)
					dp[i][j][x][y] = MAX;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &g[i][j]);

}

void dfs(int x, int y, int cnt, long long sum) {
	if (cnt > k) return ;

	if (x == n && y == n) {
		if (sum > ans)
			ans = sum;
		return ;
	}

	for (int i = 0; i < 3; i++) {
		int p = x + dir[i][0];
		int q = y + dir[i][1];
		if (p > 0 && p <= n && q > 0 && q <= n && vis[p][q] == 0) {
			vis[p][q] = 1;
			if (g[p][q] < 0 && dp[p][q][cnt + 1][i] < sum + g[p][q]) {
				dp[p][q][cnt + 1][i] = sum + g[p][q];
				dfs(p, q, cnt + 1, sum + g[p][q]);
			}
			else if (g[p][q] >= 0 && dp[p][q][cnt][i] < sum + g[p][q]) {
				dp[p][q][cnt][i] = sum + g[p][q];
				dfs(p, q, cnt, sum + g[p][q]);
			}
			vis[p][q] = 0;
		}
	}
}

int main() {
	int t = 1;
	while (scanf("%d%d", &n, &k) == 2 &&  (n || k)) {
		init();

		vis[1][1] = 1;
		if (g[1][1] >= 0)
			dfs(1, 1, 0, g[1][1]);
		else
			dfs(1, 1, 1, g[1][1]);

		printf("Case %d: ", t++);
		if (ans != MAX)
			printf("%lld\n", ans);
		else
			printf("impossible\n");
	}
	return 0;
}
