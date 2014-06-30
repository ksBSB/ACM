#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1005;
const ll MOD = 1000000007;

int n, m, k;
ll dp[N], c[N][N];

void init () {
	memset(c, 0, sizeof(c));
	for (int i = 0; i < N; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
	}

	dp[0] = 1;
	dp[1] = 0;
	for (ll i = 2; i < N; i++)
		dp[i] = ((dp[i-1] + dp[i-2]) % MOD * (i-1)) % MOD;
}

ll solve () {
	ll ans = 0;
	int t = n - m;
	for (int i = 0; i <= t; i++)
		ans = (ans + c[t][i] * dp[n-k-i]) % MOD;
	return (ans * c[m][k]) % MOD;
}

int main () {
	init();
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d%d%d", &n, &m, &k);
		printf("Case %d: %lld\n", i, solve());
	}
	return 0;
}
