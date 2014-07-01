#include <stdio.h>
#include <string.h>

const int N = 30005;

int n, m, f[N], s[N];

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

void init () {
	for (int i = 0; i <= n; i++) {
		f[i] = i;
		s[i] = 1;
	}

	int k, a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d", &k);

		if (k == 0) continue;

		scanf("%d", &a);
		int p = getfar(a);
		
		for (int j = 1; j < k; j++) {
			scanf("%d", &b);
			int q = getfar(b);

			if (p != q) {
				f[q] = p;
				s[p] += s[q];
			}
		}
	}
}

int main () {
	while (scanf("%d%d", &n, &m) == 2 && n + m) {
		init ();
		printf("%d\n", s[getfar(0)]);
	}
	return 0;
}
