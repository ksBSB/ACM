#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, K, C[maxn];
vector<int> G[maxn];

void init () {
	int u, v;
	memset(C, 0, sizeof(C));
	for (int i = 1; i <= N; i++)
		G[i].clear();
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}
}

void dfs(int u) {
	int& ret = C[u];
	ret = 1;
	for (int i = 0; i < G[u].size(); i++) {
		dfs(G[u][i]);
		ret += C[G[u][i]];
	}
}

int main () {
	while (scanf("%d%d", &N, &K) == 2) {
		init();
		for (int i = 1; i <= N; i++) {
			if (C[i])
				continue;
			dfs(i);
		}

		int ans = 0;
		for (int i = 1; i <= N; i++)
			if (C[i] - 1 == K)
				ans++;
		printf("%d\n", ans);
	}
	return 0;
}
