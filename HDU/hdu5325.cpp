#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 500005;

int N, W[maxn], C[maxn], ans;
vector<int> G[maxn];

void init () {
	ans = 0;
	memset(C, 0, sizeof(C));
	for (int i = 1; i <= N; i++) {
		scanf("%d", &W[i]);
		G[i].clear();
	}
	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

void dfs (int u, int f, int d) {

	int& ret = C[u];
	ret = d + 1;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f)
			continue;
		if (W[u] > W[v])
			continue;
		dfs(v, u, 0);
		C[u] += C[v];
	}

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f)
			continue;
		if (W[u] < W[v])
			continue;
		dfs(v, u, C[u]);
	}
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		dfs(1, 0, 0);
		int ans = 0;
		for (int i = 1; i <= N; i++) {
			ans = max(ans, C[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
