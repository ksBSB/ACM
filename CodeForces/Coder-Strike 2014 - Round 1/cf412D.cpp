#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int N = 3 * 1e4 + 5;

int n, m, v[N], r[N];
vector<int> g[N];

void init () {
	scanf("%d%d", &n, &m);
	int a, b;
	while (m--) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
	}
	m = 0;
}

void dfs(int u) {
	v[u] = 1;

	int t = g[u].size();
	for (int i = 0; i < t; i++) {
		if (v[g[u][i]]) continue;
		dfs(g[u][i]);
	}

	r[m++] = u;
}

int main () {
	init ();
	for (int i = 1; i <= n; i++) {
		if (v[i]) continue;
		dfs(i);
	}

	printf("%d", r[0]);
	for (int i = 1; i < m; i++)
		printf(" %d", r[i]);
	printf("\n");
	return 0;
}
