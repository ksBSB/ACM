#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 205;

int N, dp[maxn][maxn];

int solve () {
	for (int i = 2; i < 2 * N; i++) {
		for (int j = 1; j <= N; j++)
			dp[i][j] += max(dp[i-1][j], dp[i-1][j+1]);
	}
	return dp[2*N-1][1];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		memset(dp, 0, sizeof(dp));

		for (int i = 1; i <= N; i++) {
			for (int j = N-i+1; j <= N; j++)
				scanf("%d", &dp[i][j]);
		}
		for (int i = 1; i < N; i++) {
			for (int j = 1; j <= N-i; j++)
				scanf("%d", &dp[i+N][j]);
		}
		printf("Case %d: %d\n", kcas, solve());
	}
	return 0;
}
