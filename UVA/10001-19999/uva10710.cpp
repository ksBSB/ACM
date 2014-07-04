#include <cstdio>
#include <cstring>

typedef long long ll;

ll pow_mod(ll a, ll n, ll mod) {
	ll ans = 1;
	while (n) {
		if (n&1)
			ans = ans * a % mod;
		a = a * a % mod;
		n /= 2;
	}
	return ans;
}

int main () {
	ll n;
	while (scanf("%lld", &n) == 1 && n != -1) {

		if (pow_mod(2, n-1, n) == 1)
			printf("%lld is a Jimmy-number\n", n);
		else
			printf("%lld is not a Jimmy-number\n", n);
	}
	return 0;
}
