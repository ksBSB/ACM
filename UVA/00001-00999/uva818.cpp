#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 20;

int n, ans, k, ti, g[N][N];

void init() {
	ans = n;
	int a, b;
	memset(g, 0, sizeof(g));

	while (scanf("%d%d", &a, &b) == 2) {
		if (a == -1 || b == -1) break;
		g[a-1][b-1] = g[b-1][a-1] = 1;
	}
}

int cal(int s) {
	return s ? cal(s/2) + (s&1) : 0;
}

bool judge() {
	for (int i = 0; i < n; i++) {
		if (k & (1<<i)) continue;
		int c = 0;
		for (int j = 0; j < n; j++) {
			if (k & (1<<j)) continue;
			if (g[i][j]) c++;
		}
		if (c > 2) return true;
	}
	return false;
}

bool dfs(int f, int u, int* vis) {
	if (vis[u]) return true;
	vis[u] = 1;

	for (int i = 0; i < n; i++) {
		if (k & (1<<i)) continue;
		if (i == f || !g[u][i]) continue;
		if (dfs(u, i, vis)) return true;
	}	
	return false;
}

bool rol() {
	int vis[N];
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n; i++) {
		if (k & (1<<i)) continue;
		if (vis[i]) continue;
		if (dfs(-1, i, vis)) return true;
		ti++;
	}
	return false;
}

void solve() {
	ti = 0;
	if (judge() || rol()) return;
	if (cal(k) >= ti - 1) {
		ans = min(ans, cal(k));
	}
}

int main() {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init();
		for (k = 0; k < (1<<n); k++)
			solve();
		printf("Set %d: Minimum links to open is %d\n", cas++, ans);
	}
	return 0;
}
