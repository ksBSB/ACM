#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, W[maxn][maxn];
vector<int> g[maxn];

int dfs (int u, int p) {
	int ret = 0;

	for (int i = 0; i < g[u].size(); i++) {
		int& v = g[u][i];
		if (v != p) {
			int sg = dfs(v, u);
			if (W[u][v] == 1)
				ret ^= (sg+1);
			else if (W[u][v]&1)
				ret ^= (sg + (sg&1 ? -1 : 1));
			else
				ret ^= sg;
		}
	}

	return ret;
}

int main () {
	int cas, u, v, w;
	scanf("%d", &cas);
	for (int k = 1; k <= cas; k++) {
		scanf("%d", &N);

		for (int i = 0; i < N; i++)
			g[i].clear();

		for (int i = 1; i < N; i++) {
			scanf("%d%d%d", &u, &v, &w);
			g[u].push_back(v);
			g[v].push_back(u);
			W[u][v] = W[v][u] = w;
		}

		printf("Case %d: %s\n", k, dfs(0, -1) ? "Emily" : "Jolly");
	}
	return 0;
}
