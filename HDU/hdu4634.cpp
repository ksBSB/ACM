#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 205;
const int maxm = 40005;
const int inf = 0x3f3f3f3f;
const int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
typedef pair<int,int> pii;

int N, M, K, idx, T[maxn][maxn], X[maxm], Y[maxm];
int E, first[maxm], jump[maxm<<2], linker[maxm<<2], val[maxm<<2];
char G[maxn][maxn];
int iskey[maxn][maxn];

int pre, vis[maxn][maxn];

void addEdge(int u, int v, int s) {
	jump[E] = first[u];
	linker[E] = v;
	val[E] = s;
	first[u] = E++;
}

int direction(char ch) {
	if (ch == 'U') return 0;
	if (ch == 'D') return 1;
	if (ch == 'L') return 2;
	if (ch == 'R') return 3;
	return -1;
}

bool iswall(int x, int y) {
	if (x <= 0 || x > N || y <= 0 || y > M) return false;
	return G[x][y] == '#';
}

void find(int u, int d) {
	pre++;
	int x = X[u], y = Y[u], s = 0;

	while (true) {
		vis[x][y] = pre;

		x += dir[d][0];
		y += dir[d][1];

		if (x <= 0 || x > N || y <= 0 || y > M) return; // disappear;
		if (G[x][y] == '#') return;

		int vd = direction(G[x][y]); // miss sigle;
		if (vd != -1) { 
			if (vis[x][y] == pre) return;
			d = vd;
			continue;
		}

		if (iskey[x][y] != -1) // iskey
			s |= (1<<(iskey[x][y]));

		if (G[x][y] == 'E') addEdge(u, idx, s);
		if (T[x][y] != -1 && iswall(x+dir[d][0], y+dir[d][1])) break;
	}
	addEdge(u, T[x][y], s);
}

void init () {

	K = idx = 0;
	memset(T, -1, sizeof(T));
	memset(iskey, -1, sizeof(iskey));

	for (int i = 1; i <= N; i++)
		scanf("%s", G[i]+1);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (G[i][j] == '#') {
				for (int k = 0; k < 4; k++) {
					int x = i + dir[k][0];
					int y = j + dir[k][1];
					if (x <= 0 || x > N || y <= 0 || y > M) continue;
					if (T[x][y] != -1) continue;
					if (G[x][y] == '.' || G[x][y] == 'K') {
						T[x][y] = ++idx;
						X[idx] = x, Y[idx] = y;
					}
				}
			} else if (G[i][j] == 'S') {
				T[i][j] = 0;
				X[0] = i, Y[0] = j;
			}
			if (G[i][j] == 'K')
				iskey[i][j] = K++;
		}
	}
	idx++;
}

void build() {
	pre = E = 0;
	memset(first, -1, sizeof(first));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < idx; i++) {
		for (int j = 0; j < 4; j++)
			find(i, j);
	}
}

int D[maxm][(1<<7) + 5];

int bfs (int s, int e) {
	queue<pii> que;
	que.push(make_pair(s, 0));

	memset(D, inf, sizeof(D));
	D[s][0] = 0;

	while (!que.empty()) {
		int u = que.front().first;
		int g = que.front().second;
		que.pop();

		for (int i = first[u]; i + 1; i = jump[i]) {
			int v = linker[i];
			int x = g | val[i];

			if (D[v][x] > D[u][g] + 1) {
				D[v][x] = D[u][g] + 1;
				que.push(make_pair(v, x));
			}
		}

	}

	int ans = D[e][(1<<K)-1];
	if (ans == inf) return -1;
	return ans;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		build();
		printf("%d\n", bfs(0, idx));
	}
	return 0;
}
