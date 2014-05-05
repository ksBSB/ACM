#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 505;

int n, m, a[N][N], b[N][N], dp[N][N];

void init () {
	int k;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			a[i][j] += a[i][j-1];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &b[i][j]);
			b[i][j] += b[i-1][j];
		}
	}
}

int solve () {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = max(dp[i-1][j] + a[i][j], dp[i][j-1] + b[i][j]);
		}
	}
	return dp[n][m];
}

int main () {
	while (scanf("%d%d", &n, &m) == 2 && n + m) {
		init();
		printf("%d\n", solve());
	}	
	return 0;
}
