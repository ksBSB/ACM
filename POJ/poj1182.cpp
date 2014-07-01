#include <stdio.h>
#include <string.h>

const int N = 1e5+5;
int n, k, f[N], v[N];

int getfar(int x) {
	if (x != f[x]) {
		int tmp = f[x];
		f[x] = getfar(f[x]);
		v[x] = (v[x] + v[tmp])%3;
	}
	return f[x];
}

int main () {
//	while (scanf("%d%d", &n, &k) == 2) {
	scanf("%d%d", &n, &k);

	{
		memset(v, 0, sizeof(v));
		for (int i = 0; i <= n; i++) f[i] = i;

		int ans = 0, d, a, b;
		for (int i = 0; i < k; i++) {
			scanf("%d%d%d", &d, &a, &b);
			if (a > n || b > n)
				ans++;
			else {
				int p = getfar(a), q = getfar(b);
				if (p == q) {
					if (d == 1 && v[a] != v[b])
						ans++;
					else if (d == 2 && v[b] != (v[a] + 1)%3)
						ans++;
				} else {
					f[q] = p;
					v[q] = (v[a] - v[b] + 3 + d - 1)%3;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
