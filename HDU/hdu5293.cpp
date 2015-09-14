#pragma comment(linker, "/STACK:1024000000,1024000000") 
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define lowbit(x) ((x)&(-x))
const int maxn = 100005;

struct Edge {
	int u, v, w;
}e[maxn];

vector<int> G[maxn];
int N, Q, fenw[maxn], dp[maxn], sum[maxn];
int E, first[maxn], jump[maxn * 2], link[maxn * 2];
int id, idx[maxn], dep[maxn], top[maxn], far[maxn], son[maxn], cnt[maxn];

inline void fenwAdd(int x, int w) {
	while (x <= N) {
		fenw[x] += w;
		x += lowbit(x);
	}
}

inline int fenwSum(int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

inline void addEdge(int u, int v) {
	jump[E] = first[u];
	link[E] = v;
	first[u] = E++;
}

void dfs (int u, int pre, int d) {
	dep[u] = d;
	far[u] = pre;
	cnt[u] = 1;
	son[u] = 0;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == pre)
			continue;
		dfs(v, u, d + 1);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs (int u, int rot) {
	top[u] = rot;
	idx[u] = ++id;
	if (son[u])
		dfs(son[u], rot);

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == far[u] || v == son[u])
			continue;
		dfs(v, v);
	}
}

int LCA (int u, int v) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		u = far[p];
		p = top[u];
	}
	if (dep[u] > dep[v])
		swap(u, v);
	return u;
}

int query(int u, int v) {
	int p = top[u], q = top[v], ret = 0;
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}
		ret += fenwSum(idx[u]) - fenwSum(idx[p] - 1);
		
		u = far[p];
		p = top[u];
	}

	if (dep[u] > dep[v])
		swap(u, v);
	ret += fenwSum(idx[v]) - fenwSum(idx[u] - 1);
	return ret;
}

void init () {
	int u, v;
	E = 0;
	memset(fenw, 0, sizeof(fenw));
	memset(first, -1, sizeof(first));
	for (int i = 1; i <= N; i++)
		G[i].clear();

	scanf("%d%d", &N, &Q);
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	id = 0;
	dfs(1, 0, 0);
	dfs(1, 1);

	for (int i = 1; i <= Q; i++) {
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		G[LCA(e[i].u, e[i].v)].push_back(i);
	}
}

void solve(int u) {

	sum[u] = 0;
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == far[u])
			continue;
		solve(v);
		sum[u] += dp[v];
	}

	dp[u] = sum[u];
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		dp[u] = max(dp[u], query(e[v].u, e[v].v) + sum[u] + e[v].w);
	}
	fenwAdd(idx[u], sum[u] - dp[u]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve(1);
		printf("%d\n", dp[1]);
	}
	return 0;
}
