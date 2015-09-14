#pragma comment(linker, "/STACK:102400000,102400000")  
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 100;
const int inf = 0x3f3f3f3f;

int N, W[maxn], dpDestroy[maxn][maxm + 5], dpSafe[maxn][maxm + 5];
int minDestroy[maxn][maxm + 5], minSafe[maxn][maxm + 5];
vector<int> G[maxn];

void init () {
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

void dfs (int u, int f) {
	//memset(dpDestroy[u], inf, sizeof(dpDestroy[u]));
	//memset(dpSafe[u], inf, sizeof(dpSafe[u]));
	for (int i = 0; i <= maxm; i++)
		dpDestroy[u][i] = dpSafe[u][i] = N;


	int tmp = 0;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f)
			continue;

		dfs(v, u);
		tmp += min(minDestroy[v][W[u]], (W[u] ? minSafe[v][W[u]-1] : inf));
	}
	dpDestroy[u][W[u]] = tmp + 1;

	for (int i = 0; i < maxm; i++) {
		int p = 0, q = 0;
		for (int j = 0; j < G[u].size(); j++) {
			int v = G[u][j];
			if (v == f)
				continue;
			p += min(minDestroy[v][i + 1], (i == 0 ? inf : minSafe[v][i-1]));
			q += min(minDestroy[v][i], (i == 0 ? inf : minSafe[v][i-1]));
		}

		for (int j = 0; j < G[u].size(); j++) {
			int v = G[u][j];
			if (v == f)
				continue;
			//dpDestroy[u][i] = min(dpDestroy[u][i], p+dpDestroy[v][i+1]-min(minDestroy[v][i+1], minSafe[v][i]));
			if (i)  {
				dpDestroy[u][i] = min(dpDestroy[u][i], p+dpDestroy[v][i+1]-min(minDestroy[v][i+1], minSafe[v][i-1]));
				dpSafe[u][i] = min(dpSafe[u][i], q + dpSafe[v][i-1] - min(minDestroy[v][i], minSafe[v][i-1]));
			} else {
				dpDestroy[u][i] = min(dpDestroy[u][i], p+dpDestroy[v][i+1]-min(minDestroy[v][i+1], inf));
				dpSafe[u][i] = min(dpSafe[u][i], q);
			}
		}
	}

	if (G[u].size() == 1)
		dpSafe[u][0] = 0;


	minDestroy[u][0] = dpDestroy[u][0];
	minSafe[u][0] = dpSafe[u][0];
	for (int i = 1; i <= maxm; i++) {
		minDestroy[u][i] = min(minDestroy[u][i-1], dpDestroy[u][i]);
		minSafe[u][i] = min(minSafe[u][i-1], dpSafe[u][i]);
	}
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		dfs(1, 0);
		printf("%d\n", minDestroy[1][maxm]);
	}
	return 0;
}
