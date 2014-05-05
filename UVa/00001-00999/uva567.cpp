#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
const int N = 30;
const int INF = 1 << 20;
int n, d[N][N], g[N][N];

void init() {
	for (int i = 1; i <= 20; i++)
		for (int j = 1; j <= 20; j++)
			d[i][j] = (i == j ? 0 : INF);
	memset(g, 0, sizeof(g));

	int a, cnt = 1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		d[a][cnt] = 1;
		d[cnt][a] = 1;
	}
	for (cnt = 2; cnt <= 19; cnt++) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &a);
			d[a][cnt] = 1;
			d[cnt][a] = 1;
		}
	}
}

void floyd() {
	n = 20;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void solve() {
	scanf("%d", &n);
	int a, b;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		printf("%2d to %2d: %d\n", a, b, d[a][b]);
	}
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1) {
		init();
		floyd();
		printf("Test Set #%d\n", cas++);
		solve();
		printf("\n");
	}
	return 0;
}
