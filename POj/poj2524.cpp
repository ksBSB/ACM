#include <stdio.h>
#include <string.h>

const int N = 50005;
int n, m, f[N];

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &n, &m) == 2 && n + m) {
		for (int i = 0; i <= n; i++)
			f[i] = i;

		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			int p = getfar(a), q = getfar(b);
			if (p != q) {
				n--;
				f[q] = p;
			}
		}
		printf("Case %d: %d\n", cas++, n);
	}
	return 0;
}
