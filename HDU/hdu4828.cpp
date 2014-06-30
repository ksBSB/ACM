#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1000005;
const ll MOD = 1e9+7;

ll dp[N];

ll extendGcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}

	ll d = extendGcd(b, a%b, y, x);
	y -= a / b * x;
	return d;
}

ll solve (ll n) {
	ll x, y;
	ll tmp = extendGcd(n + 1, MOD, x, y);
	x = (x % MOD + MOD) % MOD;
	return x;
}

void init () {
	dp[1] = 1;
	dp[2] = 2;
	for (ll i = 3; i < N; i++)
		dp[i] = (dp[i-1] * (4 * i - 2) % MOD * solve(i)) % MOD;
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	init();
	for (int i = 1; i <= cas; i++) {
		scanf("%d", &n);
		printf("Case #%d:\n%lld\n", i, dp[n]);
	}
	return 0;
}
