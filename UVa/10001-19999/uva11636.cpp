#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
	int cas = 1, n;
	while (scanf("%d", &n) == 1 && n > 0) {
		printf("Case %d: %d\n", cas++, (int)ceil(log2(n)) );
	}
	return 0;
}
