#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, M, P[3], S[3];
bool vis[maxn][maxn];
vector<int> G[3];

bool solve (int u, int v) {
	for (int i = 1; i <= S[v]; i++) {
		int vv = (P[v] + i) % S[v];
		int a = G[u][P[u]], b = G[v][vv];
		if (vis[a][b]) continue;
		vis[a][b] = true;
		P[v] = vv;
		return true;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &N, &M);
		printf("Case #%d:\n", kcas);
		for (int i = 0; i < 3; i++) G[i].clear();

		for (int i = 1; i <= N; i++) G[(i-1)%3].push_back(i);
		for (int i = 0; i < 3; i++) S[i] = G[i].size();
		P[0] = 0, P[1] = P[2] = -1;

		memset(vis, false, sizeof(vis));
		for (int i = 0; i < M; i++) {
			int u = i % 3, v = (i + 1) % 3;
			while (!solve(u, v)) P[u] = (P[u] + 1) % S[u];
			printf("%d %d %d\n", G[u][P[u]], G[v][P[v]], i + 1);
		}
	}
	return 0;
}
