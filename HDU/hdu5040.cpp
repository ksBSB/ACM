#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 505;
const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int INF = 0x3f3f3f3f;

struct state {
	int x, y, t;
	state (int x = 0, int y = 0, int t = 0) {
		this->x = x;
		this->y = y;
		this->t = t;
	}
};

int N, sx, sy, ex, ey, v[maxn][maxn];
int dp[maxn][maxn][4];
char g[maxn][maxn];

inline int cal (char ch) {
	if (ch == 'N') return 0;
	else if (ch == 'E') return 1;
	else if (ch == 'S') return 2;
	else return 3;
}

void look (int x, int y) {
	v[x][y] = 15;
	int b = cal(g[x][y]);
	for (int i = 0; i < 4; i++) {
		int idx = (i + b) % 4;
		int p = x + dir[idx][0];
		int q = y + dir[idx][1];

		if (p < 0 || p >= N || q < 0 || q >= N || g[p][q] == '#')
			continue;
		v[p][q] |= (1<<i);
	}
}

void init () {
	scanf("%d", &N);
	memset(v, 0, sizeof(v));
	for (int i = 0; i < N; i++)
		scanf("%s", g[i]);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (g[i][j] == '#')
				v[i][j] = -1;
			else if (g[i][j] == 'M') {
				sx = i, sy = j;
			} else if (g[i][j] == 'T') {
				ex = i, ey = j;
			} else if (g[i][j] != '.')
				look(i, j);
		}
	}
}

int bfs () {
	queue<state> que;
	que.push(state(sx, sy, 0));

	memset(dp, INF, sizeof(dp));
	dp[sx][sy][0] = 0;

	while (!que.empty()) {
		state u = que.front();
		que.pop();

		int x = u.x, y = u.y, t = u.t;

		for (int i = 0; i < 4; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];

			if (p < 0 || p >= N || q < 0 || q >= N || v[p][q] == -1)
				continue;
			int add = 1;

			if ((v[x][y] & (1<<t)) || (v[p][q] & (1<<t))) {
				int ti = (t + add) % 4;
				if (dp[x][y][ti] > dp[x][y][t] + add) {
					dp[x][y][ti] = dp[x][y][t] + add;
					que.push(state(x, y, ti));
				}
				add = 3;
			}

			int ti = (t + add) % 4;
			if (dp[p][q][ti] > dp[x][y][t] + add) {
				dp[p][q][ti] = dp[x][y][t] + add;
				que.push(state(p, q, ti));
			}
		}
	}

	int ans = INF;
	for (int i = 0; i < 4; i++)
		ans = min(ans, dp[ex][ey][i]);

	if (ans == INF)
		return -1;
	else
		return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d: %d\n", kcas, bfs());
	}
	return 0;
}
