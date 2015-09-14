#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int inf = 0x3f3f3f3f;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
typedef pair<int,int> pii;

int N, M, T[maxn][maxn], K[maxn][maxn];
char G[maxn][maxn];

bool bfs () {
	int sx, sy;
	queue<pii> Q;

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			K[i][j] = T[i][j] = inf;
			if (G[i][j] == 'F') {
				Q.push(make_pair(i, j));
				T[i][j] = 0;
			} else if (G[i][j] == '#')
				T[i][j] = 0;
			else if (G[i][j] == 'J')
				sx = i, sy = j;
		}

	while (!Q.empty()) {
		int x = Q.front().first;
		int y = Q.front().second;
		Q.pop();

		for (int i = 0; i < 4; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];
			if (p <= 0 || p > N || q <= 0 || q > M) continue;
			if (T[p][q] > T[x][y] + 1) {
				T[p][q] = T[x][y] + 1;
				Q.push(make_pair(p, q));
			}
		}
	}
	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++)
			printf("%d", T[i][j]);
		printf("\n");
	}
	*/

	K[sx][sy] = 0;
	Q.push(make_pair(sx, sy));
	while (!Q.empty()) {
		int x = Q.front().first;
		int y = Q.front().second;
		Q.pop();
		if (x == 1 || x == N || y == 1 || y == M) {
			printf("%d\n", K[x][y] + 1);
			return true;
		}

		for (int i = 0; i < 4; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];
			if (p <= 0 || p > N || q <= 0 || q > M) continue;
			if (min(T[p][q], K[p][q]) > K[x][y] + 1) {
				K[p][q] = K[x][y] + 1;
				Q.push(make_pair(p, q));
			}
		}
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++) scanf("%s", G[i]+1);
		if (!bfs()) printf("IMPOSSIBLE\n");
	}
	return 0;
}
