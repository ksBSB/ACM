#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

const int N = 30;
const int M = 10000;
const int INF = 0x3f3f3f3f;
const int d[4][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1}};
const char sign[N] = "esnwESNW";

struct point {
	int x, y;
};

struct state {
	int x, y;
	int cnt;
	vector<int> rec;
	void clear() {
		x = y = -1;
		cnt = 0;
		rec.clear();
	}
};

int r, c;
state s, b;
char g[N][N];

void init() {
	int flag = 0;
	s.clear();
	b.clear();

	for (int i = 0; i < r; i++) gets(g[i]);

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (g[i][j] == 'S') {
				s.x = i, s.y = j;
				flag++;
			} else if (g[i][j] == 'B') {
				b.x = i, b.y = j;
				flag++;
			}
			if (flag == 2) break;
		}
	}
}

bool bfs(point p, point q, point e, int* ans) {
	queue<point> que;
	point u, k;
	int G[N][N]; memset(G, -1, sizeof(G));
	int vis[M]; memset(vis, 0, sizeof(vis));
	que.push(p);

	while (!que.empty()) {
		u = que.front(); que.pop();
		if (u.x == e.x && u.y == e.y) {
			int xi = u.x, yi = u.y;
			while (G[xi][yi] != -1) {
				int& dir = G[xi][yi];
				vis[++vis[0]] = dir;
				xi += d[3-dir][0]; yi += d[3-dir][1];
			}

			for (int i = vis[0]; i; i--) ans[++ans[0]] = vis[i];
			return false;
		}

		for (int i = 0; i < 4; i++) {
			k.x = u.x + d[i][0]; k.y = u.y + d[i][1];
			if (k.x < 0 || k.x >= r || k.y < 0 || k.y >= c) continue;
			if ((k.x == q.x && k.y == q.y) || (k.x == p.x && k.y == p.y)) continue;
			if (g[k.x][k.y] == '#' || G[k.x][k.y] != -1) continue;

			G[k.x][k.y] = i;
			que.push(k);
		}
	}
	return true;
}

bool judge(state k) {
	int ans[M];
	memset(ans, 0, sizeof(ans));
	int n = k.rec.size();
	point p, q, aid;
	p.x = s.x; p.y = s.y;
	q.x = b.x; q.y = b.y;

	for (int i = 0; i < n; i++) {
		int dir = k.rec[i];
		aid.x = q.x + d[3-dir][0]; aid.y = q.y + d[3-dir][1];
		if (bfs(p, q, aid, ans)) return false;
		ans[++ans[0]] = dir + 4;
		p = q;
		q.x += d[dir][0]; q.y += d[dir][1];
	}

	for (int i = 1; i <= ans[0]; i++) printf("%c", sign[ans[i]]);
	printf("\n");
	return true;
}

bool solve() {
	queue<state> que;
	state u, k;
	que.push(b);
	int v[N][N]; memset(v, INF, sizeof(v));

	while (!que.empty()) {
		u = que.front(); que.pop();

		for (int i = 0; i < 4; i++) {
			int p = u.x + d[3-i][0], q = u.y + d[3-i][1];
			if (p < 0 || p >= r || q < 0 || q >= c || g[p][q] == '#') continue;

			k = u;
			k.x += d[i][0]; k.y += d[i][1];
			if (k.x < 0 || k.x >= r || k.y < 0 || k.y >= c || g[k.x][k.y] == '#') continue;

			if (g[k.x][k.y] == 'T') {
				k.rec.push_back(i);
				if (judge(k)) return false;
			} else {
				k.cnt++;
				if (k.cnt >= v[k.x][k.y]) continue;
				v[k.x][k.y] = k.cnt;
				k.rec.push_back(i);
				que.push(k);
			}
		}
	}
	return true;
}

int main() {
	int cas = 1;
	while (scanf("%d%d%*c", &r, &c), r + c) {
		init();
		printf("Maze #%d\n", cas++);
		if (solve()) printf("Impossible.\n");
		printf("\n");
	}
	return 0;
}
