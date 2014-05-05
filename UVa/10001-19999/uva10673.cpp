#include <stdio.h>
#include <math.h>

void gcd(long long a, long long b, long long& d, long long& x, long long& y) {
	if (!b) { d = a, x = 1, y = 0; }
	else { gcd(b, a % b, d, y, x); y -= x * (a / b); }
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		long long c, k, a, b, d, x, y;
		scanf("%lld%lld", &c, &k);
		a = floor(1.0 * c / k);
		b = ceil(1.0 * c / k);
		gcd(a, b, d, x, y);
		x *= c / d;
		y *= c / d;
		printf("%lld %lld\n", x, y);

	}
	return 0;
}
