#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
const int mod = 1000000007;

int nc, vis[maxn], fac[maxn], F[maxn];

void preserve () {
	nc = 0;
	for (int i = 2; i < maxn; i++) {
		if (vis[i]) continue;
		fac[nc++] = i;
		for (int j = i + i; j < maxn; j += i)
			vis[j] = 1;
	}

	for (int i = 0; i < nc; i++) {
		ll k = fac[i];
		while (k < maxn) {
			vis[k] = fac[i];
			k *= fac[i];
		}
	}

	F[1] = 1;
	for (int i = 2; i < maxn; i++)
		F[i] = 1LL * F[i-1] * vis[i] % mod;
}

int pow_mod(ll x, int n) {
	ll ret = 1;
	while (n) {
		if (n&1)
			ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

int inv(ll x) {
	return pow_mod(x, mod-2);
}

int main () {
	preserve ();
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
	//	printf("%d! %lld\n", F[n+1], inv(n+1));
		printf("%lld\n", 1LL * F[n+1] * inv(n+1) % mod);
	}
	return 0;
}
