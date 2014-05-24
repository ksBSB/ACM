#include <cstdio>
#include <cstring>

typedef long long ll;

const int N = 1005;
ll dp[N][N];

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a%b);
}

void init () {
	for (int i = 2; i < N; i++)
		for (int j = 2; j < N; j++)
			dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + gcd(i, j) - 1;

	for (int i = 2; i < N; i++)
		for (int j = 2; j < N; j++)
			dp[i][j] += dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
}

ll C(ll n, ll m) {
	if (n < m)
		return 0;

	ll ans = 1;
	for (ll i = 0; i < m; i++)
		ans = ans * (n-i) / (i+1);
	return ans;
}

ll solve (ll n, ll m) {
	return C((n)*(m), 3) - C(n, 3) * m - C(m, 3) * n;
}

int main () {
	int cas = 1;
	ll n, m;
	init();
	while (scanf("%lld%lld", &n, &m) == 2 && n && m) {
		printf("Case %d: %lld\n", cas++, solve(n+1, m+1)-dp[n][m]*2);
	}
	return 0;
}
