#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int INF = 0x3f3f3f3f;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int N, M, dp[maxn][maxn][15][35];
int vis[maxn][maxn];
char g[maxn][maxn];

struct state {
	int x, y, k, s;
	state (int x = 0, int y = 0, int k = 0, int s = 0) {
		set(x, y, k, s);
	}
	void set (int x, int y, int k, int s) {
		this->x = x;
		this->y = y;
		this->k = k;
		this->s = s;
	}
}S, E;

void init () {
	int tmp = 0;
	memset(vis, 0, sizeof(vis));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (g[i][j] == 'K')
				S.set(i, j, 0, 0);
			if (g[i][j] == 'S')
				vis[i][j] = --tmp;
			if (g[i][j] == 'T')
				E.set(i, j, M, 0);
			if (g[i][j] == '#')
				vis[i][j] = 1;
		}
	}
}

void bfs () {
	queue<state> que;
	que.push(S);
	memset(dp, INF, sizeof(dp));
	dp[S.x][S.y][S.k][S.s] = 0;

	while (!que.empty()) {
		state u = que.front();
		que.pop();

		for (int i = 0; i < 4; i++) {
			int x = u.x + dir[i][0];
			int y = u.y + dir[i][1];
			int k = u.k, s = u.s;

			if (x < 0 || x >= N || y < 0 || y >= N || vis[x][y] == 1)
				continue;

			int add = 1;

			if (vis[x][y] < 0) {
				int tmp = -vis[x][y] - 1;
				if ((s&(1<<tmp)) == 0)
					add++;
				s |= (1<<tmp);
			}

			if (g[x][y] >= '1' && g[x][y] <= '9') {
				int tmp = g[x][y] - '0';
				if (tmp == k + 1)
					k++;
			}

			if (dp[u.x][u.y][u.k][u.s] + add < dp[x][y][k][s]) {
				dp[x][y][k][s] = dp[u.x][u.y][u.k][u.s] + add;
				que.push(state(x, y, k, s));
			}
		}
	}

	int ans = INF;
	for (int i = 0; i < 32; i++)
		ans = min (ans, dp[E.x][E.y][M][i]);

	if (ans == INF)
		printf("impossible\n");
	else
		printf("%d\n", ans);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		for (int i = 0; i < N; i++)
			scanf("%s", g[i]);
		init();
		bfs();
	}
	return 0;
}
