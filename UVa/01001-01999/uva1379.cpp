#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 105;
const int M = 10;

struct state {
	int val, u;
}g[N][N];

int n, m, d, t[N*3];
int dp[2][M][M][M][M];

inline bool cmp (const state& a, const state& b) {
	return a.val > b.val;
}

inline int cat (int j, int i) {
	if (j == 0 || i == 0)
		return 0;
	return g[i][j].u;
}

void init () {
	scanf("%d%d%d", &n, &m, &d);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &g[i][j].val);
			g[i][j].u = j;
		}
		sort(g[i]+1, g[i] + n + 1, cmp);
	}

	d += 10;

	for (int i = 1; i <= d; i++)
		scanf("%d", &t[i]);
}

double solve () {
	memset(dp[0], 0, sizeof(dp[0]));

	for (int i = 1; i <= d; i++) {
		int now = i%2;
		int pre = 1-now;

		memset(dp[now], 0, sizeof(dp[now]));

		if (t[i]) {

			for (int j = 1; j <= 5; j++) {
				for (int x = 0; x <= 5; x++) {
					if (i > 1 && cat(j, t[i]) == cat(x, t[i-1])) continue;

					for (int y = 0; y <= 5; y++) {
						if (i > 2 && cat(j, t[i]) == cat(y, t[i-2])) continue;

						for (int z = 0; z <= 5; z++) {
							if (i > 3 && cat(j, t[i]) == cat(z, t[i-3])) continue;

							for (int a = 0; a <= 5; a++) {
								if (i > 4 && cat(j, t[i]) == cat(a, t[i-4])) continue;
								dp[now][j][x][y][z] = max(dp[now][j][x][y][z], dp[pre][x][y][z][a] + g[t[i]][j].val);
							}
						}
					}
				}
			}
		} else {

			for (int x = 0; x <= 5; x++) {
				for (int y = 0; y <= 5; y++) {
					for (int z = 0; z <= 5; z++) {
						for (int a = 0; a <= 5; a++) {
							dp[now][0][x][y][z] = max(dp[now][0][x][y][z], dp[pre][x][y][z][a]);
						}
					}
				}
			}
		}
	}

	int ans = 0;
	int u = d%1;

	for (int x = 0; x <= 5; x++)
		for (int y = 0; y <= 5; y++)
			for (int z = 0; z <= 5; z++)
				for (int a = 0; a <= 5; a++)
					ans = max(ans, dp[u][x][y][z][a]);
	return ans / 100.0;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		printf("%.2lf\n", solve());
	}
	return 0;
}
