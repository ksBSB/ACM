#include <cstdio>
#include <cstring>

const int N = 1005;

int n, c[N], v[N];

void init () {
	memset(c, 0, sizeof(c));
	memset(v, -1, sizeof(v));

	for (int i = 1; i < N; i++) {
		for (int j = i; j < N; j += i)
			c[j] += i;

		if (c[i] < N)
			v[c[i]] = i;
	}
}

int main () {
	init();
	int cas  = 1;
	while (scanf("%d", &n) == 1 && n) {
		printf("Case %d: %d\n", cas++, v[n]);
	}
	return 0;
}
