#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int mod = 1000000007;
const int maxn = 1005;

int fac[maxn];
int N, K, son[maxn];
ll dp[maxn][maxn];
vector<int> G[maxn];

void dfs (int u, int f) {
	son[u] = 1;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f)
			continue;
		dfs(v, u);
		son[u] += son[v];
	}	
}

void init () {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++)
		G[i].clear();

	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
}

void exgcd (ll a, ll b, ll& d, ll& x, ll&y) {
	if (!b)
		d = a, x = 1, y = 0;
	else {
		exgcd(b, a%b, d, y, x);
		y -= x * (a/b);
	}
}

ll inv (ll a) {
	ll d, x, y;
	exgcd(a, mod, d, x, y);
	return d == 1 ? (x + mod) % mod : -1;
}

int solve () {
	memset(dp, 0, sizeof(dp));	
	dp[0][0] = 1;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= K; j++) {
			if (dp[i-1][j] == 0)
				continue;
			dp[i][j] = (dp[i][j] + dp[i-1][j] * (son[i] - 1) % mod * inv(son[i])) % mod;
			dp[i][j+1] = (dp[i][j+1] + dp[i-1][j] * inv(son[i])) % mod;
		}
	}
	return dp[N][K] * fac[N] % mod;
}

int main () {
	fac[1] = 1;
	for (int i = 2; i <= 1000; i++)
		fac[i] = 1LL * i * fac[i-1] % mod;

	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init ();
		printf("Case #%d: %d\n", kcas, solve());
	}
	return 0;
}
