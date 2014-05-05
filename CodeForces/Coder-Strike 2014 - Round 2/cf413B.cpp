#include <cstdio>
#include <cstring>

const int N = 2 * 1e4 + 5;

int n, m, k, c[N], r[15];
int g[N][15];

void init () {
	memset(r, 0, sizeof(r));
	memset(c, 0, sizeof(c));
	memset(g, 0, sizeof(g));

	scanf("%d%d%d", &n, &m, &k);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			scanf("%d", &g[i][j]);
	}
}

void solve () {
	int a, b;
	for (int i = 0; i < k; i++) {
		scanf("%d%d", &a, &b);
		c[a]++;
		r[b]++;
	}

	for (int i = 1; i <= n; i++) {
		int t = 0;
		for (int j = 1; j <= m; j++) {
			if (g[i][j])
				t += r[j];
		}
		c[i] = t - c[i];
	}

	for (int i = 1; i < n; i++)
		printf("%d ", c[i]);
	printf("%d\n", c[n]);
}

int main () {
	init ();
	solve ();
	return 0;
}
