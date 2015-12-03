#pragma comment(linker, "/STACK:16777216") 
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int maxn = 1e5 + 5;

ll ans;
int N, sz[maxn];
vector<int> G[maxn];

void init () {
	for (int i = 1; i <= N; i++) G[i].clear();

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	ans = 0;
}

void dfs (int u, int f) {
	sz[u] = 0;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}

	int nd = sz[u], fz = N-1-sz[u];
	ll sum = 1LL * fz * nd;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f) continue;
		nd -= sz[v];
		sum += 1LL * sz[v] * nd;
	}

	ans += 1LL * fz * (sum - 1LL * fz * (N-1-fz));
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f) continue;
		ans += 1LL * sz[v] * (sum - 1LL * sz[v] * (N-1-sz[v]));
	}

	sz[u]++;
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		dfs(1, 0);
		printf("%I64u\n", ans / 3);
	}
	return 0;
}
