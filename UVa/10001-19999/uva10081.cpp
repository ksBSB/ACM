#include <stdio.h>
#include <string.h>

int n, k;
double p[105][15];

void solve() {
	memset(p, 0, sizeof(p));
	for (int i = 0; i <= k; i++)
		p[1][i] = 1.0 / (k + 1);
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			p[i][j] = p[i - 1][j];
			if (j) p[i][j] += p[i - 1][j - 1];
			if (j != k) p[i][j] += p[i - 1][j + 1];
			p[i][j] /= (k + 1);
		}
	}
}

int main () {
	while (scanf("%d%d", &k, &n) == 2) {
		solve();
		double ans = 0;
		for (int i = 0; i <= k; i++)
			ans += p[n][i];
		printf("%.5lf\n", ans * 100);
	}
	return 0;
}
