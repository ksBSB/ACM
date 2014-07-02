#include <cstdio>
#include <cstring>
#include <cmath>

typedef long long ll;

ll n, c1, t1, c2, t2;

void gcd (ll a, ll b, ll& d, ll& x, ll& y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, d, y, x);
		y -= (a/b)*x;
	}
}

int main () {
	while (scanf("%lld", &n) == 1 && n) {
		scanf("%lld%lld%lld%lld", &c1, &t1, &c2, &t2);
		ll d, xi, yi, x, y;
		gcd(t1, t2, d, xi, yi);
		ll lower = ceil(-1.0 * n * xi / t2);
		ll up = floor(1.0 * n * yi / t1);

		if (lower > up || n % d) {
			printf("failed\n");
			continue;
		}

		if (c1 * t2 > c2 * t1) {
			x = xi * n / d + t2 / d * lower;
			y = yi * n / d - t1 / d * lower;
		} else {
			x = xi * n / d + t2 / d * up;
			y = yi * n / d - t1 / d * up;
		}
		printf("%lld %lld\n", x, y);
	}
	return 0;
}
