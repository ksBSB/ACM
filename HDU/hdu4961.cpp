#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5;
const int INF = 0x3f3f3f3f;

int n, arr[maxn+5], b[maxn+5], c[maxn+5], v[maxn+5];
vector<int> g[maxn+5];

void get_factor (int n) {
	for (int i = 1; i <= n; i++)
		g[i].clear();

	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i)
			g[j].push_back(i);
	}
}

void init () {

	memset(v, 0, sizeof(v));
	for (int i = 1; i <= n; i++) {
		int u = arr[i];
		int k = (v[u] == 0 ? i :v[u]);
		b[i] = arr[k];

		for (int j = 0; j < g[u].size(); j++)
			v[g[u][j]] = max(v[g[u][j]], i);
	}

	memset(v, INF, sizeof(v));
	for (int i = n; i >= 1; i--) {
		int u = arr[i];
		int k = (v[u] == INF ? i : v[u]);
		c[i] = arr[k];

		for (int j = 0; j < g[u].size(); j++)
			v[g[u][j]] = min(v[g[u][j]], i);
	}
}

int main () {
	get_factor(maxn);

	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		init();

		ll ans = 0;
		for (int i = 1; i <= n; i++)
			ans = ans + b[i] * 1LL * c[i];
		printf("%I64d\n", ans);
	}
	return 0;
}
