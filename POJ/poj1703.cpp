#include <stdio.h>
#include <string.h>

const int N = 1e5+5;
int n, m, f[N], v[N];

int getfar(int x) {
	if (x != f[x]) {
		int t = f[x];
		f[x] = getfar(f[x]);
		v[x] = (v[x] + v[t]) % 2;
	}
	return f[x];
}

void init () {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++)
		f[i] = i;
	memset(v, 0, sizeof(v));
}

int main () {
	int cas, a, b;
	char str[10];
	scanf("%d", &cas);
	while (cas--) {
		init ();
		for (int i = 0; i < m; i++) {
			scanf("%s%d%d", str, &a, &b);
			int p = getfar(a), q = getfar(b);

			if (str[0] == 'A') {

				if (p != q)
					printf("Not sure yet.\n");
				else if (v[a] == v[b])
					printf("In the same gang.\n");
				else
					printf("In different gangs.\n");
			} else {

				if (p != q) {
					f[q] = p;
					v[q] = (v[a] + 1 - v[b])%2;
				}
			}
		}
	}
	return 0;
}
