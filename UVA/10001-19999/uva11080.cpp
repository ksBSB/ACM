#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 205;

int N, M, B, W, C[maxn];
vector<int> G[maxn];

void init () {
	scanf("%d%d", &N, &M);
	memset(C, 0, sizeof(C));
	for (int i = 0; i < N; i++) G[i].clear();

	int u, v;
	while (M--) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

bool bipartite(int u) {
	if (C[u] == 1) B++;
	else W++;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (C[v] == C[u]) return false;
		if (!C[v]) {
			C[v] = 3 - C[u];
			if (!bipartite(v)) return false;
		}
	}
	return true;
}

int solve () {
	int ans = 0;
	for (int i = 0; i < N; i++) {
		if (C[i] == 0) {
			B = W = 0;
			C[i] = 1;
			if (!bipartite(i)) return -1;
			ans += max(1, min(B, W));
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
