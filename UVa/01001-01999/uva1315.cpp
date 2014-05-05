#include <stdio.h>
#include <string.h>

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		int t = (n - 1) / 2;
		int s = (1 + t) * t;
		if (n&1) s -= t;
		printf("%d\n", s);
	}
	return 0;
}
