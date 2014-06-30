#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
const int N = 35;

int n, m, k, v[N], c[N];
vector<int> g[N];
map<int, double> d[N];

int dfs (int u) {
	v[u] = 1;
	int ans = 1;
	for (int i = 0; i < g[u].size(); i++) {
		if (v[g[u][i]]) continue;
		ans += dfs(g[u][i]);
	}
	return ans;
}

void init () {
	scanf("%d%d", &n, &m);

	int a, b;
	memset(v, 0, sizeof(v));
	for (int i = 1; i <= n; i++) g[i].clear();

	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}

	k = 0;
	for (int i = 1; i <= n; i++) if (!v[i]) {
		d[k].clear();
		c[k] = dfs(i);
		k++;
	}
}

double solve (int u, int s) {
	if (d[u].count(s)) return d[u][s];

	int link = 0;
	for (int i = 0; i < k; i++) if (s&(1<<i)) {
		link += c[i];
	}
	if (link == n) return d[u][s] = 0;
	d[u][s] = (n-1)*1.0/(n-link);

	for (int i = 0; i < k; i++) if ((s&(1<<i)) == 0) {
		d[u][s] += solve (i, s | (1<<i)) * c[i]/(n-link);
	}
	return d[u][s];
}

int main () {
	int cas;
	scanf("%d", &cas);	
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %.6lf\n", i, solve (0, 1));
	}
	return 0;
}
