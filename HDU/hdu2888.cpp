#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 305;

int N, M, Q, g[maxn][maxn], dp[maxn][maxn][9][9];

void rmq_init(int n, int m) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			dp[i][j][0][0] = g[i][j];
	}

	for (int x = 0; (1<<x) <= n; x++)
		for (int y = 0; (1<<y) <= m; y++)
			if (x + y)
				for (int i = 1; i + (1<<x) - 1 <= n; i++)
					for (int j = 1; j + (1<<y) - 1 <= m; j++) {
						if (x)
							dp[i][j][x][y] = max(dp[i][j][x-1][y], dp[i+(1<<(x-1))][j][x-1][y]);
						else
							dp[i][j][x][y] = max(dp[i][j][x][y-1], dp[i][j+(1<<(y-1))][x][y-1]);
					}
}

int rmq_query(int x1, int y1, int x2, int y2) {
	int x = 0, y = 0;
	while ((1<<(x+1)) <= x2 - x1 + 1) x++;
	while ((1<<(y+1)) <= y2 - y1 + 1) y++;
	x2 = x2 - (1<<x) + 1;
	y2 = y2 - (1<<y) + 1;

	return max( max(dp[x1][y1][x][y], dp[x2][y1][x][y]), max(dp[x1][y2][x][y], dp[x2][y2][x][y]));
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++)
				scanf("%d", &g[i][j]);
		}
		rmq_init(N, M);

		scanf("%d", &Q);
		int x1, y1, x2, y2;
		while (Q--) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			int ans = rmq_query(x1, y1, x2, y2);
			bool flag = false;
			if (ans == g[x1][y1] || ans == g[x1][y2] || ans == g[x2][y1] || ans == g[x2][y2])
				flag = true;
			printf("%d %s\n", ans, flag ? "yes" : "no");
		}
	}
	return 0;
}
