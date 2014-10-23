#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int INF = 0x3f3f3f3f;
int N, M, g[maxn][maxn], p[maxn], dp[maxn][maxn];

void init () {
	scanf("%d%d", &N, &M);
	memset(g, 0, sizeof(g));
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= M; j++)
			scanf("%d", &g[i][j]);
	}

	for (int i = 1; i <= N; i++)
		scanf("%d", &p[i]);
}

int solve () {
	memset(dp, -INF, sizeof(dp));

	if (p[1] == -1)
		memset(dp[1], 0, sizeof(dp[1]));
	else
		dp[1][p[1]] = 0;

	for (int i = 2; i <= N; i++) {
		if (p[i] == -1) {
			for (int x = 1; x <= M; x++)
				for (int y = 1; y <= M; y++)
					dp[i][x] = max(dp[i][x], dp[i-1][y] + g[y][x]);
		} else {
			int x = p[i];
			for (int y = 1; y <= M; y++)
				dp[i][x] = max(dp[i][x], dp[i-1][y] + g[y][x]);
		}
	}
	int ret = 0;
	for (int i = 1; i <= M; i++)
		ret = max(dp[N][i], ret);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
}
