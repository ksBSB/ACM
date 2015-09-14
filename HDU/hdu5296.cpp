#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 100005;
typedef set<int>::iterator iter;

set<int> S;
int N, Q, dp[maxn], vis[maxn];
int E, first[maxn], jump[maxn * 2], link[maxn * 2], val[maxn * 2];
int id, idx[maxn], ridx[maxn], dep[maxn], top[maxn], far[maxn], son[maxn], cnt[maxn];

inline void addEdge(int u, int v, int w) {
	link[E] = v;
	val[E] = w;
	jump[E] = first[u];
	first[u] = E++;
}

void dfs (int u, int pre, int d, int w) {
	far[u] = pre;
	dep[u] = d;
	cnt[u] = 1;
	son[u] = 0;
	dp[u] = w;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == pre)
			continue;
		dfs(v, u, d + 1, w + val[i]);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs (int u, int rot) {
	top[u] = rot;
	if (son[u])
		dfs(son[u], rot);
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == far[u] || v == son[u])
			continue;
		dfs(v, v);
	}
	idx[u] = ++id;
	ridx[id] = u;
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

void init () {
	S.clear();
	scanf("%d%d", &N, &Q);
	id = E = 0;
	memset(first, -1, sizeof(first));
	memset(vis, 0, sizeof(vis));

	int u, v, w;
	for (int i = 1; i < N; i++) {
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w);
		addEdge(v, u, w);
	}

	dfs(1, 0, 0, 0);
	dfs(1, 1);
}

int solve (int u) {
	if (S.size() == 0)
		return 0;

	int a, b;
	iter mv = S.upper_bound(idx[u]);
	if (mv == S.begin() || mv == S.end()) {
		a = ridx[*S.begin()];
		b = ridx[*S.rbegin()];
	} else {
		a = ridx[*mv];
		mv--;
		b = ridx[*mv];
	}
	return dp[u] - dp[LCA(u, a)] - dp[LCA(u, b)] + dp[LCA(a, b)];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d:\n", kcas);

		int k, u, ans = 0;
		for (int i = 0; i < Q; i++) {
			scanf("%d%d", &k, &u);
			if (k == 1 && vis[idx[u]] == 0) {
				ans += solve(u);
				S.insert(idx[u]);
				vis[idx[u]] = 1;
			}

			if (k == 2 && vis[idx[u]]) {
				S.erase(idx[u]);
				vis[idx[u]] = 0;
				ans -= solve(u);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
