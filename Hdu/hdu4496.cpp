#include <cstdio>
#include <cstring>

const int N = 10005;
const int M = 100005;

int n, m, ans[M];
int f[N], x[M], y[M];

int getfar(int s) {
	return s == f[s] ? s : f[s] = getfar(f[s]);
}

void init () {
	for (int i = 0; i < n; i++)
		f[i] = i;

	for (int i = 0; i < m; i++)
		scanf("%d%d", &x[i], &y[i]);
}

void solve () {
	int tmp = n;
	for (int i = m - 1; i >= 0; i--) {
		ans[i] = tmp;

		int p = getfar(x[i]);
		int q = getfar(y[i]);

		if (p != q) {
			f[q] = p;
			tmp--;
		}
	}

	for (int i = 0; i < m; i++)
		printf("%d\n", ans[i]);
}

int main () {
	while (scanf("%d%d", &n, &m) == 2) {
		init();
		solve();
	}
	return 0;
}
