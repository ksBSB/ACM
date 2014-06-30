#include <stdio.h>
#include <string.h>

const int N = 1e3+5;

int n, c[N];

int main () {
	while (scanf("%d", &n) == 1) {
		int a;
		memset(c, 0, sizeof(c));
		for (int i = 0; i <= n; i++) {
			scanf("%d", &a);
			c[a]++;
		}

		int x;
		for (x = 1; x <= n; x++)
			if (c[x] == 2) break;

		printf("%d\n", x);
	}
	return 0;
}
