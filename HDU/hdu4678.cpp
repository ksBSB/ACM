#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 1005;
const int dir[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

int N, M, K, G[maxn][maxn], T[maxn][maxn];

void init () {
	scanf("%d%d%d", &N, &M, &K);
	memset(G, 0, sizeof(G));
	memset(T, 0, sizeof(T));

	int u, v;
	for (int i = 0; i < K; i++) {
		scanf("%d%d", &u, &v);
		G[u][v] = -1;
		for (int j = 0; j < 8; j++) {
			int x = u + dir[j][0];
			int y = v + dir[j][1];
			if (x < 0 || x >= N || y < 0 || y >= M || G[x][y] == -1) continue;
			G[x][y] = 1;
		}
	}
}

queue<pii> Q;

int bfs(int x, int y) {
	int ret = 0;
	Q.push(make_pair(x, y));
	T[x][y] = 1;

	while (!Q.empty()) {
		x = Q.front().first;
		y = Q.front().second;
		Q.pop();

		if (G[x][y]) { ret++; continue; }

		for (int i = 0; i < 8; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];
			if (p < 0 || p >= N || q < 0 || q >= M || T[p][q]) continue;
			Q.push(make_pair(p, q));
			T[p][q] = 1;
		}
	}
	return ret&1 ? 2 : 1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		int ans = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (G[i][j] == 0 && T[i][j] == 0)
					ans ^= bfs(i, j);
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++)
				if (G[i][j] == 1 && T[i][j] == 0)
					ans ^= 1;
		}
		printf("Case #%d: %s\n", kcas, ans ? "Xiemao" : "Fanglaoshi");
	}
	return 0;
}
