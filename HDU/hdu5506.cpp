#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 35;
const int maxm = 305;

int N, L, C[maxn], A[maxn][maxn], vis[maxm];

void init () {
	scanf("%d%d", &N, &L);
	for (int i = 0; i < N; i++) {
		scanf("%d", &C[i]);
		for (int j = 0; j < C[i]; j++)
			scanf("%d", &A[i][j]);
	}
}

bool have(int u) {
	for (int i = 0; i < C[u]; i++)
		if (vis[A[u][i]]) return true;
	return false;
}

bool dfs (int u, int d) {
	if (u >= N) return true;
	if (have(u)) return dfs(u+1, d);
	if (d >= L) return false;

	for (int i = 0; i < C[u]; i++) {
		vis[A[u][i]] = 1;
		if (dfs(u+1, d+1)) return true;
		vis[A[u][i]] = 0;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		memset(vis, 0, sizeof(vis));
		printf("%s\n", dfs(0, 0) ? "YES" : "NO");
	}
	return 0;
}
