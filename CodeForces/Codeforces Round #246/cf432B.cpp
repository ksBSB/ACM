#include <cstdio>
#include <cstring>

const int N = 1e5;
int n, a, k, c[N], p[N];

int main () {
	scanf("%d", &n);

	memset(c, 0, sizeof(c));

	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a, &p[i]);
		c[a]++;
	}

	for (int i = 0; i < n; i++)
		printf("%d %d\n", n - 1 + c[p[i]], n - 1 - c[p[i]]);
	return 0;
}
