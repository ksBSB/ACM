#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1000000;

int fac[maxn + 5], inv[maxn + 5];

int pow_mod(ll x, int n) {
	ll ret = 1;
	while (n) {
		if (n&1) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

void presolve() {
	fac[0] = 1;
	for (int i = 1; i <= maxn; i++)
		fac[i] = 1LL * i * fac[i-1] % mod;
	inv[maxn] = pow_mod(fac[maxn], mod-2);
	for (int i = maxn-1; i >= 0; i--)
		inv[i] = 1LL * (i+1) * inv[i+1] % mod;
}

int N, ans, sz[maxn + 5];
vector<int> G[maxn + 5];
ll dp[maxn + 5];

ll C(int n, int k) {
	if (k > n || k < 0 || n < 0) return 0;
	return 1LL * fac[n] * inv[k] % mod * inv[n-k] % mod;
}

ll dfs (int u, int f) {
	ll& ret = dp[u];
	ret = 1;
	sz[u] = 0;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f) continue;
		ret = ret * dfs(v, u) % mod;
		sz[u] += sz[v];
	}

	int s = sz[u];
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f) continue;
		ret = ret * C(s, sz[v]) % mod;
		s -= sz[v];
	}
	sz[u]++;
	return ret;
}

void dfs(int u, int f, ll k) {
	// k 为以u为根对应的反向树有多少种方式
	ll ret = k;
	k = (k * dp[u]) % mod;

	int s = N-1;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f) continue;

		// 扣除现在枚举的子树
		ll iv = k * pow_mod(dp[v] * C(sz[u]-1, sz[v]) % mod, mod-2) % mod;
		dfs(v, u, iv * C(N-sz[v]-1, sz[u]-sz[v]-1) % mod);
		ret = ret * C(s, sz[v]) % mod * dp[v] % mod;
		s -= sz[v];
	}
	ans = (ans + ret * ret % mod) % mod;
}

int main () {
	presolve();
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		int u, v;
		for (int i = 1; i <= N; i++) G[i].clear();
		for (int i = 1; i < N; i++) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}

		ans = 0;
		dfs(1, 0);
		dfs(1, 0, 1);
		printf("%d\n", ans);
	}
	return 0;
}
