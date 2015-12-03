#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 100005;
const int inf = 0x3f3f3f3f;

int N, W[maxn], L[maxn], R[maxn], D[maxn];
vector<pii> G[maxn];

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) G[i].clear();

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d%d", &u, &v, &W[i]);
		G[u].push_back(make_pair(v, i));
		G[v].push_back(make_pair(u, i));
		L[i] = R[i] = -inf;
	}
}

int solve(int& s, int& e) {
	memset(D, inf, sizeof(D));
	D[1] = 0;

	queue<int> que;
	que.push(1);

	while (!que.empty()) {
		s = que.front();
		que.pop();
		for (int i = 0; i < G[s].size(); i++) {
			int v = G[s][i].first;
			if (D[v] > D[s] + 1) {
				D[v] = D[s] + 1;
				que.push(v);
			}
		}
	}

	memset(D, inf, sizeof(D));
	D[s] = 0;
	que.push(s);

	while (!que.empty()) {
		e = que.front();
		que.pop();

		for (int i = 0; i < G[e].size(); i++) {
			int v = G[e][i].first;
			if (D[v] > D[e] + 1) {
				D[v] = D[e] + 1;
				que.push(v);
			}
		}
	}
	return D[e];
}

int dep[maxn], son[maxn], len[maxn], idx[maxn];

void dfs(int u, int f) {
	dep[u] = dep[f] + 1;
	son[u] = 0;
	len[u] = dep[u];

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i].first;
		if (v == f) continue;
		dfs(v, u);
		if (len[v] > len[u]) {
			son[u] = v;
			idx[u] = G[u][i].second;
			len[u] = len[v];
		}
	}
	//printf("%d %d %d\n", u, son[u], idx[u]);
}

void dfs(int u, int f, int deter, int id, int* a) {
	if (u == 0) return;
	a[id] = max(a[id], deter);

	int k = dep[u];
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i].first;
		if (v == f || v == son[u]) continue;
		k = max(k, dep[v]);
	}

	dfs(son[u], u, max(deter, k), idx[u], a);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		int s, e;
		int deter = solve(s, e);
		dep[0] = -1;
		dfs(s, 0);
		dfs(s, 0, 0, 0, L);

		dep[0] = -1;
		dfs(e, 0);
		dfs(e, 0, 0, 0, R);
		int ans = inf, id = 0, x;
		for (int i = 1; i < N; i++) {
			if (L[i] < 0 || R[i] < 0) x = deter;
			else x = max(L[i], R[i]);
			if (x * W[i] < ans) {
				ans = x * W[i];
				id = i;
			}
		}
		printf("Case #%d: %d\n", kcas, id);

	}
	return 0;
}
