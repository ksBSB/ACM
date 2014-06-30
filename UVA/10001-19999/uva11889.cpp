#include <stdio.h>
#include <math.h>

int l, a;

int gcd (int x, int y) {
	return y == 0 ? x : gcd(y, x%y);
}

int solve () {
	int t = l / a;
	for (int i = t; i <= l; i += t) {
		if (i / gcd (i, a) == t)
			return i;
	}
	return 0;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &a, &l);
		if (l%a)
			printf("NO SOLUTION\n");
		else
			printf("%d\n", solve());
	}
	return 0;
}
