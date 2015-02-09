#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 6005;
const int inf = 0x3f3f3f3f;

int N, R[maxn], D[maxn], ans = 0;
vector<int> g[maxn];

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &R[i]);
	for (int i = 0; i < N; i++)
		D[i] = inf;

	int a, b;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
}

void dfs(int u, int f) {
	int idx = lower_bound(D, D + N, R[u]) - D;
	ans = max(ans, idx + 1);

	int tmp = D[idx];
	D[idx] = R[u];
	for (int i = 0; i < g[u].size(); i++) {
		if (g[u][i] == f) continue;
		dfs(g[u][i], u);
	}
	D[idx] = tmp;
}

int main () {
	init();
	for (int i = 1; i <= N; i++)
		dfs(i, 0);
	printf("%d\n", ans);
	return 0;
}
