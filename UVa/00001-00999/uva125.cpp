#include <stdio.h>
#include <string.h>
#define max(a,b) (a)>(b)?(a):(b)
const int N = 1005;

int r, n, g[N][N];

void init() {
	r = 0;
	int a, b;
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		g[a][b] = 1;
		r = max(max(a, b), r);
	}
}

void warshall() {
	for (int k = 0; k <= r; k++)
		for (int i = 0; i <= r; i++)
			for (int j = 0; j <= r; j++)
				g[i][j] += g[i][k] * g[k][j];
	for (int k = 0; k <= r; k++) {
		if (g[k][k]) {
			for (int i = 0; i <= r; i++) {
				for (int j = 0; j <= r; j++)
					if (g[i][k] && g[k][j]) g[i][j] = -1;
			}
		}
	}
}

void put() {
	for (int i = 0; i <= r; i++) {
		for (int j = 0; j < r ; j++)
			printf("%d ", g[i][j]);
		printf("%d\n", g[i][r]);
	}
}

int main () {
	int cas = 0;
	while (scanf("%d", &n) == 1) {
		init();
		warshall();
		printf("matrix for city %d\n", cas++);
		put();
	}
	return 0;
}
