#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 1005;
const int maxm = 1e6;

int N, M, E, first[maxn], jump[maxm], link[maxm], vis[maxm];
int cntlock, pre[maxn], low[maxn], iscut[maxm];

void dfs (int u, int fa) {
	pre[u] = low[u] = ++cntlock;

	for (int i = first[u]; i != -1; i = jump[i]) {
		int v = link[i];
		if (!pre[v]) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > pre[u])
				iscut[i] = 1;
		} else if (pre[v] < pre[u] && v != fa)
			low[u] = min(low[u], pre[v]);
	}
}

void findEdge () {
	cntlock = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	for (int i = 1; i <= N; i++)
		if (!pre[i]) dfs(i, -1);
}

inline void addEdge (int u, int v) {
	jump[E] = first[u];
	link[E] = v;
	first[u] = E++;
}

void init () {
	E = 0;
	memset(first, -1, sizeof(first));

	int u, v;
	while (M--) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	findEdge();
}

void put (int u) {
	if (pre[u]) return;

	pre[u] = ++cntlock;

	for (int i = first[u]; i != -1; i = jump[i]) {
		int v = link[i];
		if (iscut[i]) {
			printf("%d %d\n", u, v);
			continue;
		}
		if (vis[i]) continue;
		vis[i] = vis[i^1] = 1;
		printf("%d %d\n", u, v);
		put(v);
	}
}

void solve () {
	cntlock = 0;
	memset(pre, 0, sizeof(pre));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= N; i++)
		put(i);
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		printf("%d\n\n", cas++);
		solve();
		printf("#\n");
	}
	return 0;
}
