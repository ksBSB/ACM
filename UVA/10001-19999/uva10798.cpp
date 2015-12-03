#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 23;
const int maxm = 11;
const int dir[][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

struct State {
	int x, y, l, u, r, d, w;
	State (int x = 0, int y = 0, int l = 0, int u = 0, int r = 0, int d = 0): x(x), y(y), l(l), u(u), r(r), d(d) {
		w = max(max(l, r), max(u, d));
	}
	bool operator <  (const State& u) const { return w > u.w; }
};

int N, vis[maxn][maxn][maxm][maxm][maxm][maxm];
char G[maxn][maxn];

int bfs (int x, int y) {
	memset(vis, 0, sizeof(vis));
	priority_queue<State> que;

	vis[x][y][0][0][0][0] = 1;
	que.push(State(x, y, 0, 0, 0, 0));

	while (!que.empty()) {
		State u = que.top();
		que.pop();

		for (int i = 0; i < 4; i++) {
			State v = u;
			int x = u.x + dir[i][0];
			int y = u.y + dir[i][1];
			if (x <= 0 || x > N || y <= 0 || y > N) return u.w;
			v.x = x;
			v.y = y;

			if (G[x][y] == 'R') v.l++;
			if (G[y][N-x+1] == 'R') v.u++;
			if (G[N-x+1][N-y+1] == 'R') v.r++;
			if (G[N-y+1][x] == 'R') v.d++;
			if (vis[x][y][v.l][v.u][v.r][v.d]) continue;
			vis[x][y][v.l][v.u][v.r][v.d] = 1;
			que.push(State(v.x, v.y, v.l, v.u, v.r, v.d));
		}
	}
	return -1;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 1; i <= N; i++)
			scanf("%s", G[i]+1);
		printf("At most %d rose(s) trampled.\n", bfs(N/2+1, N/2+1));
	}
	return 0;
}
