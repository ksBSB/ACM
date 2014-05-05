#include <stdio.h>
#include <string.h>
#include <math.h>

int main () {
	int a, b;
	while (scanf("%d%d", &a, &b) == 2 && a + b) {
		int t = floor(sqrt(b)) - floor(sqrt(a-1));
		printf("%d\n", t);
	}
	return 0;
}
