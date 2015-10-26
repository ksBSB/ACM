#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
typedef long long ll;

int N, W[maxn], fac[maxn], L[maxn], R[maxn], ans[maxn];
int E, first[maxn], jump[maxn<<2], linker[maxn<<2];
vector<int> G[maxn];

void addEdge(int u, int v) {
	jump[E] = first[u];
	linker[E] = v;
	first[u] = E++;
}

void init () {
	E = 0;
	memset(first, -1, sizeof(first));

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	for (int i = 1; i <= N; i++) scanf("%d", &W[i]);
}

int bitcount(int x) { return x ? bitcount(x>>1) + (x&1) : 0; }

int solve (int x, int a) {
	int n = G[x].size(), ret = 0;
	for (int i = 1; i < (1<<n); i++) {
		int t = 1;
		for (int j = 0; j < n; j++) if (i&(1<<j))
			t *= G[x][j];

		if (bitcount(i)&1) ret += fac[t];
		else ret -= fac[t];
		fac[t] += a;
	}
	return ret;
}

int dfs (int u, int f) {
	int cnt = 0;
	L[u] = solve(W[u], 0);

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = linker[i];
		if (v == f) continue;
		cnt += dfs(v, u);
	}

	R[u] = solve(W[u], 1);
	ans[u] = cnt - (R[u]-L[u]);
	if (W[u] == 1) ans[u]++;
	return cnt + 1;
}

int main () {
	//for (int i = 1; i < maxn; i++) G[i].clear();
	for (int i = 2; i < maxn; i++) {
		if (G[i].size()) continue;
		for (int j = i; j < maxn; j += i)
			G[j].push_back(i);
	}

	int cas = 1;
	while (scanf("%d", &N) == 1) {
		init();

		memset(fac, 0, sizeof(fac));
		dfs(1, 0);
		printf("Case #%d:", cas++);
		for (int i = 1; i <= N; i++)
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}
