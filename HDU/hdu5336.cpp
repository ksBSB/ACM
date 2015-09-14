#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 105;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int R, C, N, T, sz[maxn][maxn], vs[maxn][maxn], xi[maxn], yi[maxn], tx[maxn], ty[maxn];

struct node {
	int x, y, d;
	node (int x = 0, int y = 0, int d = 0): x(x), y(y), d(d) {}
};

void BFS (int x, int y) {
	queue<node> Q;
	for (int i = 0; i < 4; i++)
		Q.push(node(x, y, i));

	for (int i = 1; i <= T; i++) {

		int n = Q.size(), cnt = 0;
		while (n--) {
			node tmp = Q.front();
			Q.pop();

			int x = tmp.x + dir[tmp.d][0];
			int y = tmp.y + dir[tmp.d][1];

			if (x <= 0 || x > R || y <= 0 || y > C)
				continue;
			if (sz[x][y] == -1)
				Q.push(node(x, y, tmp.d));
			else if (vs[x][y] == -1) {
				sz[x][y]++;
				if (sz[x][y] > 4) {
					vs[x][y] = i;
					tx[cnt] = x;
					ty[cnt] = y;
					cnt++;
				}
			}
		}

		for (int j = 0; j < cnt; j++) {
			for (int k = 0; k < 4; k++)
				Q.push(node(tx[j], ty[j], k));
			sz[tx[j]][ty[j]] = -1;
		}
	}
}

int main () {
	while (scanf("%d%d%d%d", &R, &C, &N, &T) == 4) {
		int x, y, s;
		memset(vs, -1, sizeof(vs));
		memset(sz, -1, sizeof(sz));
		for (int i = 1; i <= N; i++) {
			scanf("%d%d%d", &xi[i], &yi[i], &s);
			sz[xi[i]][yi[i]] = s;
		}

		scanf("%d%d", &x, &y);
		BFS(x, y);
		for (int i = 1; i <= N; i++) {
			if (sz[xi[i]][yi[i]] == -1)
				printf("0 %d\n", vs[xi[i]][yi[i]]);
			else
				printf("1 %d\n", sz[xi[i]][yi[i]]);
		}
	}
	return 0;
}
