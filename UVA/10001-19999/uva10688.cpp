#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 505;
const int INF = 0x3f3f3f3f;

int n, k, dp[N][N];

int solve (int l, int r, int m) {
	int s = (r-l+1)*m;
	if (dp[l][r] != INF)
		return s + dp[l][r];

	if (r == l) return s;

	int& ans = dp[l][r];
	for (int i = l; i <= r; i++) {
		int u = i+k;
		if (i != l) u += solve(l, i-1, i+k);
		if (i != r) u += solve (i+1, r, i+k);
		ans = min(ans, u);
	}
	return ans + s;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		memset(dp, INF, sizeof(dp));
		scanf("%d%d", &n, &k);
		printf("Case %d: %d\n", i, solve(1, n, 0));
	}
	return 0;
}
