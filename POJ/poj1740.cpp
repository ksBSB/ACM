#include <stdio.h>
#include <string.h>

const int N = 105;

int main () {
	int a, n, c[N];
	while (scanf("%d", &n) == 1 && n) {
		memset(c, 0, sizeof(c));
		for (int i = 0; i < n; i++) {
			scanf("%d", &a);
			c[a]++;
		}

		int ans = 0;
		for (int i = 0; i < N; i++)
			ans += (c[i]&1);
		printf("%d\n", ans ? 1 : 0);

	}
	return 0;
}
