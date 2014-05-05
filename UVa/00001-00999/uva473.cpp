#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;
int n, m, t, k, dp[N][N];

int solve () {
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < n; i++) {
		scanf("%d%*c", &k);
		for (int j = m; j >= 1; j--) {
			for (int x = t; x >= k; x--) {
				dp[j][x] = max(dp[j][x], dp[j-1][t]+1);
				dp[j][x] = max(dp[j][x], dp[j][x-k]+1);
			}
		}
	}
	return dp[m][t];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d", &n, &t, &m);
		printf("%d\n", solve());
		if (cas) printf("\n");
	}
	return 0;
}
