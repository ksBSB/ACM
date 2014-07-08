#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 20;
const int INF = 0x3f3f3f3f;
const int dir[4][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

struct point {
	int x, y;
	point (int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
};

struct pipe {
	point s, e;
} pi[maxn];

int N, M, d[maxn][maxn];
int dp[(1<<15)+5][maxn];
char g[maxn][maxn];

int bfs (point s, point e) {
	int vis[maxn][maxn];
	memset(vis, -1, sizeof(vis));

	queue<point> que;

	vis[s.x][s.y] = 0;
	que.push(s);

	while (!que.empty()) {
		point u = que.front();
		que.pop();

		if (u.x == e.x && u.y == e.y)
			return vis[u.x][u.y];

		for (int i = 0; i < 4; i++) {
			int x = u.x + dir[i][0];
			int y = u.y + dir[i][1];

			if (x <= 0 || x > N || y <= 0 || y > N)
				continue;

			if (vis[x][y] != -1 || g[x][y] == '#')
				continue;

			vis[x][y] = vis[u.x][u.y] + 1;
			que.push(point(x, y));
		}
	}
	return -1;
}

void init () {
	for (int i = 1; i <= N; i++)
		scanf("%s", g[i] + 1);

	memset(d, 0, sizeof(d));

	for (int i = 0; i < M; i++) {
		scanf("%d%d%d%d", &pi[i].s.x, &pi[i].s.y, &pi[i].e.x, &pi[i].e.y);
		
		for (int j = 0; j < i; j++) {
			d[i][j] = bfs(pi[i].e, pi[j].s);
			d[j][i] = bfs(pi[j].e, pi[i].s);
		}
	}
}

int solve () {
	memset(dp, INF, sizeof(dp));

	for (int i = 0; i < M; i++)
		dp[1<<i][i] = 0;

	for (int s = 0; s < (1<<M); s++) {

		for (int j = 0; j < M; j++) {
			if (dp[s][j] == INF)
				continue;

			for (int k = 0; k < M; k++) {
				if (s&(1<<k))
					continue;

				if (d[j][k] == -1)
					continue;

				dp[s|(1<<k)][k] = min(dp[s|(1<<k)][k], dp[s][j] + d[j][k]);
			}
		}
	}

	int ans = INF;
	for (int i = 0; i < M; i++)
		ans = min(ans, dp[(1<<M)-1][i]);
	return ans == INF ? -1 : ans;
}


int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();

		printf("%d\n", solve());;
	}
	return 0;
}
