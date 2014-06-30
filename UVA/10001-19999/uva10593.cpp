#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 505;

int n, dp[N][N];
char g[N][N];

int solve () {
	int ans = 0;
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (g[i][j] == 'x') {
				int tmp = min(dp[i-1][j], dp[i][j-1]);
				dp[i][j] = tmp + (g[i-tmp][j-tmp] == 'x');

				if (dp[i][j] > 1)
					ans += dp[i][j] - 1;
			}
		}
	}

	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (g[i][j] == 'x') {
				int tmp = min(dp[i-1][j-1], dp[i-1][j+1]);

				if (tmp == 0 || g[i-1][j] != 'x')
					dp[i][j] = 1;
				else if (g[i-tmp*2][j] == 'x' && g[i-tmp*2+1][j] == 'x')
					dp[i][j] = tmp + 1;
				else
					dp[i][j] = tmp;

				if (dp[i][j] > 1)
					ans += dp[i][j] - 1;
			}
		}
	}
	return ans;
}

int main () {
	while (scanf("%d%*c", &n) == 1 && n) {
		for (int i = 1; i <= n; i++)
			gets(g[i]+1);
		printf("%d\n", solve());
	}
	return 0;
}
