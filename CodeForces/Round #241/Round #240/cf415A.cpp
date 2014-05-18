#include <stdio.h>
#include <string.h>

const int N = 105;

int main () {
	int n, m, a, v[N];
	scanf("%d%d", &n, &m);
	memset(v, 0, sizeof(v));

	for (int i = 0; i < m; i++) {
		scanf("%d", &a);
		for (int j = a; j <= n; j++)
			if (v[j] == 0) v[j] = a;
	}
	for (int i = 1; i < n; i++)
		printf("%d ", v[i]);
	printf("%d\n", v[n]);
	return 0;
}
