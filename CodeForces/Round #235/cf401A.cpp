#include <stdio.h>
#include <stdlib.h>

int main () {
	int n, x, a, s = 0;
	scanf("%d%d", &n, &x);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		s += a;
	}
	s = abs(s);
	printf("%d\n", s/x + (s%x ? 1 : 0));
	return 0;
}
