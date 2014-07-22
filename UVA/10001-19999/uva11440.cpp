#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e7;
const ll MOD = 100000007;

int np, pri[maxn+5], vis[maxn+5];
ll fact[maxn+5], phi[maxn+5];


void prime_table (ll n) {
	np = 0;
	for (ll i = 2; i <= n; i++) {
		if (vis[i])
			continue;

		pri[np++] = i;
		for (ll j = i * i; j <= n; j += i)
			vis[j] = 1;
	}
}

void gcd (ll a, ll b, ll& d, ll& x, ll& y) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, d, y, x);
		y -= (a/b) * x;
	}
}

inline ll inv_number (ll a, ll n) {
	ll d, x, y;
	gcd(a, n, d, x, y);
	return (x + n) % n;
}

void init (ll n) {
	fact[1] = phi[1] = 1;
	for (ll i = 2; i <= n; i++) {
		fact[i] = (fact[i-1] * i) % MOD;
		phi[i] = phi[i-1];

		if (vis[i] == 0) {
			phi[i] *= ((i-1) * inv_number(i, MOD)) % MOD;
			phi[i] %= MOD;
		}
	}
}

ll solve (int n, int m) {
	ll ans = fact[n] * phi[m] % MOD;
	return (ans - 1 + MOD) % MOD;
}

int main () {
	prime_table(maxn);
	init (maxn);

	int n, m;
	while (scanf("%d%d", &n, &m) == 2 && n + m) {
		printf("%lld\n", solve(n, m));
	}
	return 0;
}
