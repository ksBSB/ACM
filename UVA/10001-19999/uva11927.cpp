#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, M, g[maxn][maxn], c[maxn], s[maxn];

inline int SG(int u) {
	if (s[u] != -1)
		return s[u];

	int vis[maxn];
	memset(vis, 0, sizeof(vis));

	for (int i = 0; i < c[u]; i++) {
		int tmp = SG(g[u][i]);
		vis[tmp] = 1;
	}

	int ret = -1;
	while (vis[++ret]);
	return s[u] = ret;
}

void init () {
	int u, v;
	memset(s, -1, sizeof(s));
	memset(c, 0, sizeof(c));

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &u, &v);
		g[u][c[u]++] = v;
	}

	for (int i = 0; i < N; i++)
		s[i] = SG(i);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		int ans = 0, u;
		for (int i = 0; i < N; i++) {
			scanf("%d", &u);
			if (u&1)
				ans ^= s[i];
		}
		printf("%s\n", ans ? "First" : "Second");
	}
	return 0;
}
