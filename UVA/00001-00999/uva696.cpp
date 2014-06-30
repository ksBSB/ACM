#include <stdio.h>

int f(int n, int m) {
	if (n < m) return f(m, n);
	else if (m == 1) return  n;
	else if (m == 2) {
		return (n / 4) * 4 + ((n % 4 > 1) ? 2 : n % 4) * 2;
	}
	else return (n * m + 1) / 2;
}

int main () {
	int r, c;
	while (scanf("%d%d", &r, &c), r + c) {
		printf("%d knights may be placed on a %d row %d column board.\n", f(r, c), r, c);
	}
	return 0;
}
