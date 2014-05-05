#include <cstdio>
#include <cstring>

int main () {
	int n, k;
	scanf("%d%d", &n, &k);
	if (k > (n-1)/2) {
		printf("-1\n");
	} else {
		printf("%d\n", k * n);
		for (int i = 0; i < n; i++) {
			for (int j = 1; j <= k; j++)
				printf("%d %d\n", i + 1, (i + j) % n + 1);
		}
	}
	return 0;
}
