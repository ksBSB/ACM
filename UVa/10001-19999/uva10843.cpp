#include <cstdio>
#include <cstring>

typedef long long ll;
const ll MOD = 2000000011;

ll Pow (ll x, ll n) {

	if (n < 0)
		return 1;

	ll ans = 1;

	while (n) {

		if (n&1)
			ans = (ans * x) % MOD;

		x = (x * x) % MOD;
		n /= 2;
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		ll n;
		scanf("%lld", &n);
		printf("Case #%d: %lld\n", i, Pow(n, n-2));
	}
	return 0;
}
