#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

const int N = 1005;

int n, s, k, fa[N], vis[N];
vector<int> g[N], node[N];

void init() {
	scanf("%d%d%d", &n, &s, &k);
	for (int i = 0; i <= n; i++)	g[i].clear(),node[i].clear();

	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
}

void change(int u, int f, int d) {
	fa[u] = f;

	int nc = g[u].size();
	if (nc == 1 && d > k) node[d].push_back(u);

	for (int i = 0; i < nc; i++) {
		int v = g[u][i];
		if (v != f)	change(v, u, d + 1);
	}
}

void dfs(int u, int f, int d) {
	vis[u] = 1;
	int nc = g[u].size();

	for (int i = 0; i < nc; i++) {
		int v = g[u][i];
		if (v != f && d < k) dfs(v, u, d + 1);
	}
}

int solve() {
	int ans = 0;
	memset(vis, 0, sizeof(vis));

	for (int d = n - 1; d > k; d--) {
		for (int i = 0; i < node[d].size(); i++) {
			int u = node[d][i];
			if (vis[u]) continue;

			int v = u;
			for (int j = 0; j < k; j++) v = fa[v];
			dfs(v, -1, 0);
			ans++;
		}
	}

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		change(s, -1, 0);
		printf("%d\n", solve());
	}
	return 0;
}
