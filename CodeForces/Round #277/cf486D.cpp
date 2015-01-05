#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7;
const int maxn = 2005;

int N, D, W[maxn];
vector<int> G[maxn];

ll dfs(int u, int f, int rt) {
	int n = G[u].size();
	ll ret = 1;

	for (int i = 0; i < n; i++) {
		int v = G[u][i];

		if (v == f || W[rt] < W[v] || (W[rt] == W[v] && v > rt) || W[rt] - W[v] > D)
			continue;
		ret = ret * (dfs(v, u, rt) + 1) % mod;
	}
	return ret;
}

int main () {
	scanf("%d%d", &D, &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &W[i]);
	int u, v;
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	ll ans = 0;
	for (int i = 1; i <= N; i++)
		ans = (ans + dfs(i, -1, i)) % mod;
	printf("%lld\n", ans);
	return 0;
}
