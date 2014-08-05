#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll ite=(1<<20)-1;

ll N;

/*
ll mul_mod (ll x, ll n, ll mod) {
	ll ans = 0;
	x %= mod;
	n %= mod;

	while (n) {
		if (n&1)
			ans = (ans + x) % mod;
		x = 2 * x % mod;
		n >>= 1;
	}
	return ans;
}
*/
ll mul_mod(ll a, ll b, ll mod) {
    return (a * (b>>20) % mod * (1ll<<20) %mod + a*(b&(ite)) % mod) % mod;
}

ll pow_mod (ll x, ll n, ll mod) {
	ll ret = 1;
	while (n) {
		if (n&1)
			ret = mul_mod(ret, x, mod);
		x = mul_mod(x, x, mod);
		n >>= 1;
	}
	return ret;
}

bool dfs (int d, ll u, ll mod) {
	if (d == 12) {
		if (u >= 1e11 && pow_mod(N, u, mod) == u) {
			printf("%lld\n", u);
			return true;
		}
		return false;
	}

	for (int i = 0; i < 10; i++) {
		if (pow_mod(N, i * mod + u, mod) == u) {
			if (dfs(d+1, i * mod + u, mod * 10))
				return true;
		}
	}
	return false;
}

int main () {
	int cas = 1;
	while (scanf("%lld", &N) == 1 && N) {
		printf("Case %d: Public Key = %lld Private Key = ", cas++, N);
		for (int i = 0; i < 10; i++) {
			if (dfs(1, i, 10))
				break;
		}
	}
	return 0;
}
