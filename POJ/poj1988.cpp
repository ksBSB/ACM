#include <stdio.h>
#include <string.h>

const int N = 30005;

int n, f[N], s[N], v[N];

int getfar(int x) {
	if (x != f[x]) {
		int t = f[x];
		f[x] = getfar(f[x]);
		v[x] += v[t];
	}
	return f[x];
}

void init () {
	scanf ("%d", &n);
	for (int i = 0; i < N; i++) {
		f[i] = i;
		s[i] = 1;
	}
	memset(v, 0, sizeof(v));
}

int main () {
	init ();

	int a, b;
	char str[10];

	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		if (str[0] == 'M') {
			scanf("%d%d", &a, &b);
			int p = getfar(a), q = getfar(b);
			if (p != q) {
				f[p] = q;
				v[p] = s[q];
				s[q] += s[p];
			}
		} else {
			scanf("%d", &a);
			int p = getfar(a);
			printf("%d\n", v[a]);
		}
	}
	return 0;
}
