#include <stdio.h>
#include <string.h>
const int N = 30;

int n;
double p[N], ans[N];

double dfs(int c, int k, double pi) {
	if (c > n) return k ? 0 : pi;

	double sum = 0;
	if (k) {
		sum += dfs(c + 1, k - 1, pi * p[c]);
		ans[c] += sum;
	}

	sum += dfs(c + 1, k, pi * (1 - p[c]));
	return sum;
}

int main () {
	int r, cas = 1;
	while (scanf("%d%d", &n, &r), n + r) {
		for (int i = 1; i <= n; i++)
			scanf("%lf", &p[i]);
		memset(ans, 0, sizeof(ans));

		printf("Case %d:\n", cas++);
		double P = dfs(1, r, 1);

		for (int i = 1; i <= n; i++)
			printf("%.6lf\n", ans[i] / P);
	}
	return 0;
}
