#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 5005;

int N, M, S, E, C, path[maxn];
vector<int> G[maxn];

void init () {
	for (int i = 1; i <= N; i++) G[i].clear();

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

bool dfs (int u, int fa) {

	if (u == E) {
		path[C++] = u;
		return true;
	}

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == fa) continue;
		if (dfs(v, u)) {
			path[C++] = u;
			return true;
		}
	}
	return false;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();

		scanf("%d\n", &M);
		while (M--) {
			scanf("%d%d", &S, &E);
			C = 0;
			dfs(S, 0);
			if (C&1)
				printf("The fleas meet at %d.\n", path[C/2]);
			else {
				int a = path[C/2], b = path[C/2-1];
				if (a > b) swap(a, b);
				printf("The fleas jump forever between %d and %d.\n", a, b);
			}
		}
	}
	return 0;
}
