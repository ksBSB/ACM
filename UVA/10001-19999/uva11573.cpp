#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int inf = 0x3f3f3f3f;
const int dir[8][2] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

int N, M, T, D[maxn][maxn], V[maxn][maxn];
char G[maxn][maxn];

struct State {
	int x, y, d;
	State(int x = 0, int y = 0, int d = 0): x(x), y(y), d(d) {}
	bool operator < (const State& u) const { return d > u.d; }
};
priority_queue<State> Q;

int bfs () {
	int sx, sy, ex, ey;
	scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
	memset(D, inf, sizeof(D));
	memset(V, 0, sizeof(V));

	//while (!Q.empty()) Q.pop();

	D[sx][sy] = 0;
	V[sx][sy] = 1;
	Q.push(State(sx, sy, 0));

	while (!Q.empty()) {
		State u = Q.top();
		Q.pop();
		int x = u.x, y = u.y, d = u.d;
		V[x][y] = 0;

		for (int i = 0; i < 8; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];
			if (p <= 0 || p > N || q <= 0 || q > M) continue;
			int bw = (i == G[x][y] - '0') ? 0 : 1;
			if (D[p][q] > D[x][y] + bw) {
				D[p][q] = D[x][y] + bw;
				if (V[p][q] == 0) {
					V[p][q] = 1;
					Q.push(State(p, q, D[p][q]));
				}
			}
		}
	}
	return D[ex][ey];
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		for (int i = 1; i <= N; i++) scanf("%s", G[i]+1);
		scanf("%d", &T);
		while (T--) printf("%d\n", bfs()); 
	}
	return 0;
}
