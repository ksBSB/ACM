#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1005;
const int INF = 0x3f3f3f3f;

struct state {
	int v, k, c, l;
}s[N];
int n, dp[N];

bool cmp(const state& a, const state& b) {
	return a.v < b.v;
}

int solve (int u) {
	if (dp[u] != -1) return dp[u];

	int& ans = dp[u];
	ans = INF;
	
	if (u == 0) return ans = 0;

	int sum = s[u].k;
	for (int i = u; i; i--) {
		sum += (s[i].l * s[u].c);
		int f = solve (i-1);
		ans = min (ans, sum + f);
	}
	return ans;
}

int main () {
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 1; i <= n; i++)
			scanf("%d%d%d%d", &s[i].v, &s[i].k, &s[i].c, &s[i].l);

		memset(dp, -1, sizeof(dp));
		sort (s + 1, s + n + 1, cmp);
		printf("%d\n", solve(n));
	}
	return 0;
}
