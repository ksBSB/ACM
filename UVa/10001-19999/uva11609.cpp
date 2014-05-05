#include <stdio.h>
#include <string.h>

typedef long long ll;
const ll MOD = 1000000007;

ll sPow (ll a, ll n) {
	ll x = 1;

	while (n) {
		if (n&1)
			x = (x * a) % MOD;

		n /= 2;
		a = (a * a) % MOD;
	}
	return x;
}

int main () {
	int cas;
	ll n;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%lld", &n);
		printf("Case #%d: %lld\n", i, n * sPow(2, n-1) % MOD);
	}
	return 0;
}
