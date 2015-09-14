#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 305;

int N, C[maxn];
vector<int> G[maxn];

bool bipartite(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (C[u] == C[v]) return false;
		if (!C[v]) {
			C[v] = 3 - C[u];
			if (!bipartite(v)) return false;
		}
	}
	return true;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 1; i <= N; i++) G[i].clear();
		int u, v;
		while (scanf("%d%d", &u, &v) == 2 && u + v) {
			G[u].push_back(v);
			G[v].push_back(u);
		}

		memset(C, 0, sizeof(C));
		C[1] = 1;
		printf("%s\n", bipartite(1) ? "YES" : "NO");
	}
	return 0;
}
