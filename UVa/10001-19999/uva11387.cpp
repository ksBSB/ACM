#include <stdio.h>
#include <string.h>

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		if (n % 2 || n <= 2) printf("Impossible\n");
		else {
			int tmp = n / 2;
			printf("%d\n", tmp * 3);
			for (int i = 1; i <= n; i++) printf("%d %d\n", i, i % n + 1);
			for (int i = 1; i <= tmp; i++) printf("%d %d\n", i, i + tmp);
		}
	}
	return 0;
}
