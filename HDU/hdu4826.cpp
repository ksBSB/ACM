#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 105;
const int INF = 0x3f3f3f3f;
int n, m, g[N][N], dp[N][N][2];

void init () {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &g[i][j]);
}

int solve () {

	for (int i = 1; i <= m; i++)
		dp[0][i][0] = dp[n+1][i][1] = -INF;

	dp[0][1][0] = 0;
	for (int i = 1; i <= n; i++) {
		dp[i][1][0] = dp[i-1][1][0] + g[i][1];
		dp[i][1][1] = -INF;
	}

	for (int j = 2; j <= m; j++) {

		for (int i = 1; i <= n; i++)
			dp[i][j][0] = max(dp[i-1][j][0], max(dp[i][j-1][0], dp[i][j-1][1])) + g[i][j];

		for (int i = n; i >= 1; i--)
			dp[i][j][1] = max(dp[i+1][j][1], max(dp[i][j-1][0], dp[i][j-1][1])) + g[i][j];
	}
	return max(dp[1][m][0], dp[1][m][1]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		printf("Case #%d:\n%d\n", i, solve());
	}
	return 0;
}
