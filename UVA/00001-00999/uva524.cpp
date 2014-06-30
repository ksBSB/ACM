#include <stdio.h>
#include <string.h>

const int N = 50;
const int p[N] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0};

int n, v[N], vis[N];

void dfs(int d) {
	if (d == n) {
		if (p[v[n-1] + v[0]] == 1) {
			for (int i = 0; i < n - 1; i++) printf("%d ", v[i]);
			printf("%d\n", v[n - 1]);
		}
		return ;
	}

	for (v[d] = 1; v[d] <= n; v[d]++) {
		if (vis[v[d]]) continue;
		if (p[v[d] + v[d - 1]] == 0) continue;
		vis[v[d]] = 1;
		dfs(d + 1);
		vis[v[d]] = 0;
	}
}

int main () {
	int cas = 0;
	while (scanf("%d", &n) == 1) {
		if (cas) printf("\n");
		printf("Case %d:\n", ++cas);
		memset(vis, 0, sizeof(vis));
		v[0] = vis[1] = 1;
		dfs(1);
	}
	return 0;
}
