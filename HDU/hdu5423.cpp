#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1005;

int N, D[maxn], V[maxn];
vector<int> G[maxn];

void dfs (int u, int d) {
	D[d]++;
	V[u] = 1;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (V[v]) continue;
		dfs(v, d + 1);
	}
}

void init () {
	memset(D, 0, sizeof(D));
	memset(V, 0, sizeof(V));
	for (int i = 0; i <= N; i++) G[i].clear();

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
}

bool judge () {
	for (int i = 0; i < N-1 && D[i]; i++) {
		if (D[i] > 1 && D[i+1]) return false;
	}
	return true;;
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
