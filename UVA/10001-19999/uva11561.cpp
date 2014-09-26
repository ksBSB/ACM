#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 55;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
typedef pair<int, int> pii;

int W, H, v[maxn][maxn];
char g[maxn][maxn];

void tiger (int x, int y) {
	for (int i = 0; i < 4; i++) {
		int p = x + dir[i][0];
		int q = y + dir[i][1];
		if (p < 0 || p >= H || q < 0 || q >= W)
			continue;

		if (v[p][q] == 0)
			v[p][q] = -1;
	}
}

int bfs (pii s) {
	int ret = 0;

	if (v[s.first][s.second] == -1)
		return 0;

	queue<pii> que;
	que.push(s);

	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];

			if (p < 0 || p >= H || q < 0 || q >= W || v[p][q] == 1 || g[p][q] == '#')
				continue;

			if (v[p][q] != -1)
				que.push(make_pair(p, q));

			v[p][q] = 1;
			if (g[p][q] == 'G')
				ret++;
		}
	}
	return ret;
}

int main () {
	while (scanf("%d%d", &W, &H) == 2) {
		memset(v, 0, sizeof(v));
		for (int i = 0; i < H; i++)
			scanf("%s", g[i]);

		pii s;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				if (g[i][j] == 'P')
					s = make_pair(i, j);
				else if (g[i][j] == 'T')
					tiger(i, j);
			}
		}
		printf("%d\n", bfs(s));
	}
	return 0;
}
