#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 25;
typedef unsigned long long ll;

char str[maxn];
ll dp[maxn][maxn][maxn];

ll solve () {
	int n = strlen(str), c = 0;
	for (int i = 0; i < n; i++) if (str[i] == '-') c++;

	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;

	for (int i = 0; i < n; i++) {
		if (str[i] == '+') {
			for (int x = 0; x < n; x++) {
				for (int y = 0; y < n; y++) {
					if (dp[i][x][y] == 0) continue;

					dp[i+1][x][y+1] += dp[i][x][y]; // 当前位置不变
					if (i - x - y > 0) // 和1~i之间满足+的位置交换
						dp[i+1][x][y+1] += dp[i][x][y] * (i-x-y);
					dp[i+1][x][y] += dp[i][x][y] * y; // 和1~i之间不满足+的位置交换
				}
			}
		} else {
			for (int x = 0; x < n; x++) {
				for (int y = 0; y < n; y++) {
					if (dp[i][x][y] == 0) continue;

					if (i - x - y > 0) // 和1~i之间满足+的位置交换
						dp[i+1][x+1][y] += dp[i][x][y] * (i-x-y);
					if (y) // 和1~i之间不满足+的位置交换
						dp[i+1][x+1][y-1] += dp[i][x][y] * y;
				}
			}
		}
	}
	return dp[n][c][0];
}

int main () {
	while (scanf("%s", str) == 1) {
		printf("%llu\n", solve());
	}
	return 0;
}
