#include <stdio.h>

int main () {
	int n, m;
	while (scanf("%d%d", &n, &m) == 2 && n+m) {
		printf("%s\n", (n-1)%(m+1) ? "Tang" : "Jiang");
	}
	return 0;
}
