#include <stdio.h>

int solve (int n, int flag) {
	int tmp = (n + flag) % 2;
	if (n == 1) return 1;
	if (flag) {
		return solve((n + 1) / 2, tmp) * 2 - 1;
	} else {
		return solve(n / 2, tmp) * 2;
	}
}

int main () {
	int n;
	while (scanf("%d", &n), n) {
		printf("%d\n", solve(n, 0));
	}	
	return 0;
}
