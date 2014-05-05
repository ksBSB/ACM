#include <stdio.h>
#include <string.h>
const int N = 30;
int n, d[N][N][N];
double g[N][N][N];

void init() {
	memset(g, 0, sizeof(g));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				scanf("%lf", &g[i][j][1]);
				d[i][j][1] = i;
			}
		}
	}
}

void print(int x, int y, int p) {
	if (p == 0)
		printf("%d", x + 1);
	else {
		print(x, d[x][y][p], p - 1);
		printf(" %d", y + 1);
	}
}

void floyd() {
	for (int p = 1; p < n; p++) {
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (g[i][k][p] * g[k][j][1] > g[i][j][p + 1] + 1e-9) {
						g[i][j][p + 1] = g[i][k][p] * g[k][j][1];
						d[i][j][p + 1] = k;
					}
				}
			}
		}

		for (int i = 0; i < n; i++) {
			if (g[i][i][p + 1] > 1.01) {
				print(i, i, p + 1);
				printf("\n");
				return ;
			}
		}
	}	
	printf("no arbitrage sequence exists\n");
}

int main () {
	while (scanf("%d", &n) == 1) {
		init();
		floyd();
	}
	return 0;
}
