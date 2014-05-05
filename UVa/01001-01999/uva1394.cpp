#include <stdio.h>

int main () {
	int n, k, m;
	while (scanf("%d%d%d", &n, &k, &m) == 3 && n + k + m) {
		int ans = 0;
		for (int i = 2; i < n; i++)
			ans = (ans + k) % i;
		printf("%d\n", (ans + m) % n + 1);
	}
	return 0;
}
