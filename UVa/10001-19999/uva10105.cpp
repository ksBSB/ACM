#include <stdio.h>
#include <string.h>

const int N = 15;
int c[N][N];

void init() {
	for (int i = 0; i < N; i++) c[i][0] = c[i][i] = 1;

	for (int i = 1; i < N; i++)
		for (int j = 1; j < i; j++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
}

int main () {
	init();
	int n, m, x;
	while (scanf("%d%d", &n, &m) == 2) {
		int ans = 1;
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			ans *= c[n][x];
			n -= x;
		}
		printf("%d\n", ans);
	}
	return 0;
}
