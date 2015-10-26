#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int mod = 1e9+7;

ll pow_mod(ll x, int n) {
	ll ret = 1;
	while (n) {
		if (n&1) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

ll n, inv2 = pow_mod(2, mod-2), inv6 = pow_mod(6, mod-2);

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld", &n);
		n %= mod;
		ll s = n * (n + 1) % mod * inv2 % mod;
		ll p = n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
		ll ans = (n * n % mod * s % mod + p * (n + 1) % mod + s * s % mod + p) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
