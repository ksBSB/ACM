#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;
const int N = 40005;
const ll MOD = 1e9+7;

int n, m;
ll v[N];
vector<int> g[N];

void init () {
	scanf("%d%d", &n, &m);

	memset(v, 0, sizeof(v));
	for (int i = 0; i <= n; i++)
		g[i].clear();

	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		g[b].push_back(a);
	}
}

ll dfs(int x) {
	if (v[x])
		return v[x];

	for (int i = 0; i < g[x].size(); i++)
		v[x] += dfs(g[x][i]);
	return ++v[x];
}

void gcd (ll a, ll b, ll& x, ll& y, ll& d) {
	if (b == 0) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, y, x, d);
		y -= x*(a/b);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();

		ll ans = 1, b = 1;
		for (ll i = 1; i <= n; i++)
			ans = (ans * i) % MOD;

		for (int i = 1; i <= n; i++)
			b = (b * dfs(i)) % MOD;

		ll p, k, d = 1;
		gcd(b, MOD, p, k, d);
		ans = ((ans * p) % MOD + MOD) % MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
