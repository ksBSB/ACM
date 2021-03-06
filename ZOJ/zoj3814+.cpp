#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef char Mat[10][10];

const int maxn = 9;
const int maxm = 4;
const int maxs = 1<<18;
const int dir[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

Mat sb[maxn], se[maxn];
int mesh[maxn][maxm];

inline int hash_state(int* c) {
	int ret = 0;
	for (int i = 0; i < maxn; i++)
		ret = ret * maxm + c[i];
	return ret;
}

inline void reback(int p, int* c) {
	for (int i = maxn-1; i >= 0; i--) {
		c[i] = p % maxm;
		p /= maxm;
	}
}

void rotate (Mat u);

int vis[maxs+5], c[maxn+5];
set<int> stop;

void dfs (int d, int s) {
	if (d >= maxn) {
		stop.insert(s);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (memcmp(sb[d], se[d], sizeof(se[d])) == 0)
			dfs(d+1, s * maxm + i);
		rotate(sb[d]);
	}
}

void init () {

	stop.clear();

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 8; k++) {
			for (int j = 0; j < 3; j++)
				scanf("%s", sb[i*3+j][k]);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 8; k++) {
			for (int j = 0; j < 3; j++)
				scanf("%s", se[i*3+j][k]);
		}
	}

	dfs(0, 0);

	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxm; j++)
			scanf("%d", &mesh[i][j]);
	}
}

int solve (int star, int id) {
	int que[30], f = 0, r = 0;
	que[r++] = id;

	memset(c, 0, sizeof(c));
	c[id] = -1;

	int t[maxn+5];
	reback(star, t);

	while (f < r) {
		int u = que[f++];

		int x = u / 3, y = u % 3;

		for (int i = 0; i < 4; i++) {
			int p = x + dir[i][0], q = y + dir[i][1];
			int v = p * 3 + q;

			if (p < 0 || p >= 3 || q < 0 || q >= 3 || c[v])
				continue;

			if (mesh[u][(t[u] + i) % maxm] && mesh[v][(t[v] + i + 2) % maxm]) {
				que[r++] = v;
				c[v] = -c[u];
			}
		}
	}

	for (int i = 0; i < maxn; i++)
		t[i] = (t[i] + c[i] + maxm) % maxm;
	return hash_state(t);
}

int bfs() {

	if (stop.size() == 0)
		return -1;

	queue<int> que;
	memset(vis, -1, sizeof(vis));

	que.push(0);
	vis[0] = 0;

	if (stop.find(0) != stop.end())
		return 0;

	int cnt = 0;

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		cnt++;

		for (int i = 0; i < maxn; i++) {
			int v = solve(u, i);

			if (vis[v] >= 0)
				continue;
			vis[v] = vis[u] + 1;
			que.push(v);

			if (stop.find(v) != stop.end())
				return vis[v];
		}
	}
	return -1;
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		init();
		printf("%d\n", bfs());
	}
	return 0;
}

void rotate (Mat u) {
	Mat v;
	memset(v, 0, sizeof(v));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			v[7-j][i] = u[i][j];
	}
	memcpy(u, v, sizeof(v));
}
