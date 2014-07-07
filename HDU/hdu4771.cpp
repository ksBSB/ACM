#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 100;
const int maxv = 10;
const int INF = 0x3f3f3f3f;
const int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct point {
	int x, y;
	point (int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
} p[maxv];

char g[maxn+5][maxn+5];
int n, N, M, v[maxn+5][maxn+5], d[maxv][maxv];

void init () {

	memset(g, 0, sizeof(g));

	for (int i = 1; i <= N; i++) {
		scanf("%s", g[i] + 1);
		for (int j = 1; j <= M; j++)
			if (g[i][j] == '@') {
				p[0].x = i;
				p[0].y = j;
			}
	}

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].x, &p[i].y);
}

int bfs (point s, point e) {

	queue<point> que;
	memset(v, -1, sizeof(v));

	que.push(s);
	v[s.x][s.y] = 0;

	while (!que.empty()) {
		point u = que.front();
		que.pop();

		if (u.x == e.x && u.y == e.y)
			return v[u.x][u.y];

		for (int i = 0; i < 4; i++) {
			int xi = u.x + dir[i][0];
			int yi = u.y + dir[i][1];

			if (xi > N || xi <= 0)
				continue;

			if (yi > M || yi <= 0)
				continue;

			if (v[xi][yi] != -1 || g[xi][yi] == '#')
				continue;

			que.push(point(xi, yi));
			v[xi][yi] = v[u.x][u.y] + 1;
		}
	}
	return -1;
}

bool judge () {
	memset(d, 0, sizeof(d));

	for (int i = 0; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			int dis = bfs(p[i], p[j]);

			if (dis == -1)
				return false;
			d[i][j] = d[j][i] = dis;
		}
	}
	return true;
}

int solve () {
	int pos[maxv];
	for (int i = 0; i <= n; i++)
		pos[i] = i;

	int ans = INF;
	do {
		int sum = 0;
		for (int i = 0; i < n; i++)
			sum += d[pos[i]][pos[i+1]];
		ans = min (ans, sum);
	} while(next_permutation(pos + 1, pos + n + 1));

	return ans;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		if (judge()) {
			printf("%d\n", solve());
		} else
			printf("-1\n");
	}
	return 0;
}
