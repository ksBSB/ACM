#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;

const int maxn = 55;
const int maxs = 3000;
const int inf = 0x3f3f3f3f;
const int dir[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

int N, M, P, v[maxn][maxn];
int g[maxn * maxn][4], dp[maxn][maxn][maxs];

inline int idx(int x, int y) {
	return (x-1) * M + y - 1;
}

void init () {
	memset(v, 0, sizeof(v));
	memset(g, -1, sizeof(g));
	memset(dp, inf, sizeof(dp));

	int n, x1, y1, x2, y2, k, d;
	scanf("%d", &n);
	while (n--) {
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
		if (x1 == x2)
			d = (y1 > y2 ? 2 : 1);
		else
			d = (x1 > x2 ? 0 : 3);
		g[idx(x1, y1)][d] = g[idx(x2, y2)][3-d] = k;
	}

	scanf("%d", &n);
	while (n--) {
		scanf("%d%d%d", &x1, &y1, &k);
		v[x1][y1] |= (1<<(k-1));
	}
}

int bfs () {
	queue<pii> Q;
	Q.push(make_pair(idx(1, 1), 0));
	dp[1][1][0] = 0;

	while (!Q.empty()) {
		pii u = Q.front(); Q.pop();
		int x = u.first / M + 1;
		int y = u.first % M + 1;

		if (x == N && y == M)
			return dp[x][y][u.second];

		for (int i = 0; i < 4; i++) {
			if (g[u.first][i] == 0)
				continue;
			int xx = x + dir[i][0];
			int yy = y + dir[i][1];

			if (xx <= 0 || xx > N || yy <= 0 || y > M)
				continue;

			int s = u.second | v[xx][yy];
			int tmp = g[u.first][i];
			if (tmp == -1 || (u.second & (1<<(tmp-1)))) {
				if (dp[xx][yy][s] > dp[x][y][u.second] + 1) {
					dp[xx][yy][s] = dp[x][y][u.second] + 1;
					Q.push(make_pair(idx(xx, yy), s));
				}
			}
		}
	}
	return -1;
}

int main () {
	while (scanf("%d%d%d", &N, &M, &P) == 3) {
		init();
		printf("%d\n", bfs());
	}
	return 0;
}
