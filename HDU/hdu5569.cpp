#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int inf = 0x3f3f3f3f;

int N, M, A[maxn][maxn], dp[maxn][maxn];

int solve () {
	memset(dp, inf, sizeof(dp));
	dp[1][0] = dp[0][1] = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if ((i + j)&1)
				dp[i][j] = min(dp[i-1][j] + A[i-1][j] * A[i][j], dp[i][j-1] + A[i][j-1] * A[i][j]);
			else
				dp[i][j] = min(dp[i-1][j], dp[i][j-1]);
		}
	}
	return dp[N][M];
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++)
				scanf("%d", &A[i][j]);
		}	
		printf("%d\n", solve());
	}
	return 0;
}
