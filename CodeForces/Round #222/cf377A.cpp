#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 505;
const int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct state {
	int x, y, cnt;
	state() {};
	state(int x, int y) { this->x = x; this->y = y; };
}p[N * 10];

int n, r, l, k, v[N][N];
char g[N][N];

void init() {
	scanf("%d%d%d", &r, &l, &k);
	n = 0;
	memset(v, 0, sizeof(v));
	for (int i = 0; i < r; i++) scanf("%s", g[i]);	
}
 
bool cmp(const state& a, const state& b) {
	return a.cnt < b.cnt;
}

void bfs(int x, int y) {
	p[n].x = x, p[n].y = y;

	int m = 0;
	queue<state> que;
	v[x][y] = 1;
	que.push(state(x, y));

	while (!que.empty()) {
		m++;
		state c = que.front(); que.pop(); 
		for (int i = 0; i < 4; i++) {
			x = c.x + dir[i][0]; y = c.y + dir[i][1];
			if (x < 0 || x >= r || y < 0 || y >= l) continue;
			if (v[x][y] || g[x][y] == '#') continue;
			v[x][y] = 1;
			que.push(state(x, y));
		}
	}
	p[n++].cnt = m;
}

void dfs(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int a = x + dir[i][0], b = y + dir[i][1];
		if (a < 0 || a >= r || b < 0 || b >= l) continue;
		if (v[a][b] || g[a][b] == '#') continue;
		v[a][b] = 1;	
		dfs(a, b);
	}
	if (k) {
		k--; v[x][y] = 2;
	}
}

int main() {
	init();
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < l; j++) if (v[i][j] == 0 && g[i][j] == '.') {
			bfs(i, j);
		}
	}	
	sort(p, p + n, cmp);
	memset(v, 0, sizeof(v));
	for (int i = 0; i < n; i++) {
		if (k) dfs(p[i].x, p[i].y);
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < l; j++) {
			if (v[i][j] == 2) printf("X");
			else printf("%c", g[i][j]);
		}
		printf("\n");
	}
	return 0;
}
