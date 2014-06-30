#include <stdio.h>

int main() {
	int n, m, k;
	while (scanf("%d%d%d", &n, &m, &k) == 3 && n + m + k) {
		printf("%s\n", m % 2 ? "Keka" : "Gared");
	}
	return 0;
}
