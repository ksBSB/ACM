#include <stdio.h>

int main () {
	int n;
	while (scanf("%d", &n) == 1) {
		int ans = 0;
		while (n) {
			n /= 2;
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
