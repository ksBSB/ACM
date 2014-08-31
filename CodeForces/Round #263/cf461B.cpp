#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int MOD = 1e9+7;
const int maxn = 1e5+5;

int N, v[maxn];
ll dp[maxn][2];
vector<int> g[maxn];

void init () {
	memset(dp, 0, sizeof(dp));

	int x;
	scanf("%d", &N);
	for (int i = 1; i < N; i++) {
		scanf("%d", &x);
		g[x].push_back(i);
	}

	for (int i = 0; i < N; i++)
		scanf("%d", &v[i]);
}

ll pow_mod (ll x, int n, ll mod) {
	ll ret = 1;
	while (n) {
		if (n&1)
			ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

ll inv (ll x) {
	if (x == 0)
		return 1;
	return pow_mod(x, MOD-2, MOD);
}

void solve (int u) {
	if (g[u].size() == 0) {
		dp[u][v[u]] = 1;
		return;
	}

	for (int i = 0; i < g[u].size(); i++)
		solve(g[u][i]);

	if (v[u]) {
		dp[u][0] = 0;
		ll& ans = dp[u][1];
		ans = 1;

		for (int i = 0; i < g[u].size(); i++) {
			int k = g[u][i];
			ans = ans * (dp[k][1] + dp[k][0]) % MOD;
		}
	} else {
		dp[u][1] = 0;
		ll& ans = dp[u][0];
		ans = 1;

		for (int i = 0; i < g[u].size(); i++) {
			int k = g[u][i];
			ans = ans * (dp[k][0] + dp[k][1]) % MOD;
		}

		for (int i = 0; i < g[u].size(); i++) {
			int k = g[u][i];
			dp[u][1] += ans * inv(dp[k][0] + dp[k][1]) % MOD * dp[k][1] % MOD;
			dp[u][1] %= MOD;
		}
	}
	//printf("%d %d %d\n", u, dp[u][0], dp[u][1]);
}

int main () {
	init();
	solve(0);
	printf("%lld\n",  dp[0][1] % MOD);
	return 0;
}
