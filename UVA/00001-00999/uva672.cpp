#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;
struct state {
	int t, p, s;
}g[N];
int n, K, T, dp[N];

bool cmp(const state& a, const state& b) {
	return a.t < b.t;
}

void init () {
	scanf("%d%d%d", &n, &K, &T);
	for (int i = 1; i <= n; i++) scanf("%d", &g[i].t);
	for (int i = 1; i <= n; i++) scanf("%d", &g[i].p);
	for (int i = 1; i <= n; i++) scanf("%d", &g[i].s);
	sort(g + 1, g + n + 1, cmp);

	g[0].t = 0; g[0].s = 0;
	memset(dp, -1, sizeof(dp));
}

int solve() {

	dp[0] = 0;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			if (dp[j] == -1) continue;

			int u = g[i].t - g[j].t;
			int l = max(0, g[j].s - u), r = min(K, g[j].s + u);
			if (g[i].s >= l && g[i].s <= r) {
				dp[i] = max(dp[i], dp[j] + g[i].p);
			}
		}
		ans = max(dp[i], ans);
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
		if (cas) printf("\n");
	}
	return 0;
}
