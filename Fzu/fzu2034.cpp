#include <stdio.h>
#include <string.h>

const int N = 20;

int n, m, q;
char g[N][N][100];

void init() {
	memset(g, 0, sizeof(g));

	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			scanf("%s", g[i][j]);
	}
}

void solve() {
	char str[N];
	scanf("%s", str);
	for (int i = 0; i < 3; i++) {
		int x = str[i * 2] - 'A' + 1;
		int y = str[i * 2 + 1] - '0';
		printf("%s", g[y][x]);	
	}
	printf("\n");
}

int main() {
	int cas;
	scanf("%d", &cas);
	for (int k = 1; k <= cas; k++) {
		init();
		printf("Case %d:\n", k);
		for (int i = 0; i < q; i++)
			solve();
	}
	return 0;
}
