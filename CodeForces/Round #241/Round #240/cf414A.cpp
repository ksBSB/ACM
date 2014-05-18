#include <stdio.h>
#include <string.h>

int main () {
	int n, k;

	scanf("%d%d", &n, &k);
	if (n == 1) {
		if (k == 0)
			printf("1\n");
		else
			printf("-1\n");
	} else if (n/2 > k) {
		printf("-1\n");
	} else {
		int x = k - (n - 2) / 2;
		printf("%d %d", x, x * 2);
		x = x * 2 + 1;
		for (int i = 2;i < n; i++)
			printf(" %d", x++);
		printf("\n");
	}
	return 0;
}
