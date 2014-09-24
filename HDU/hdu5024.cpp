#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;

char g[maxn][maxn];
int N, dp[maxn][maxn][10];

void init () {
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (g[i][j] == '#')
				continue;

			dp[i][j][0] = dp[i][j-1][0] + 1;
			dp[i][j][1] = dp[i-1][j][1] + 1;
			dp[i][j][2] = dp[i-1][j-1][2] + 1;
			dp[i][j][3] = dp[i-1][j+1][3] + 1;
		}
	}

	for (int i = N; i; i--) {
		for (int j = N; j; j--) {
			if (g[i][j] == '#')
				continue;

			dp[i][j][4] = dp[i][j+1][4] + 1;
			dp[i][j][5] = dp[i+1][j][5] + 1;
			dp[i][j][6] = dp[i+1][j+1][6] + 1;
			dp[i][j][7] = dp[i+1][j-1][7] + 1;
		}
	}
}

int solve () {
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ret = max(ret, max(dp[i][j][0], dp[i][j][4]) + max(dp[i][j][1], dp[i][j][5]) - 1);
			ret = max(ret, max(dp[i][j][2], dp[i][j][6]) + max(dp[i][j][3], dp[i][j][7]) - 1);
		}
	}
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 1; i <= N; i++)
			scanf("%s", g[i] + 1);
		init();
		printf("%d\n", solve());
	}
	return 0;
}
