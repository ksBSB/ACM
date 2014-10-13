#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 55;
const int maxm = 2505;

int N, M;
double dp[maxn][maxn][maxm];

double solve () {
	int S = N * M;
	memset(dp, 0, sizeof(dp));
	dp[1][1][1] = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int n = i * j;
			for (int k = max(i, j); k <= n; k++) {
				dp[i][j][k+1] += dp[i][j][k] * (n - k) / (S - k);
				dp[i+1][j][k+1] += dp[i][j][k] * (N - i) * j / (S - k);
				dp[i][j+1][k+1] += dp[i][j][k] * (M - j) * i / (S - k);
				dp[i+1][j+1][k+1] += dp[i][j][k] * (N - i) * (M - j) / (S - k);
			}
		}
	}

	/*
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			printf("%d %d:", i, j);
			for (int k = max(i, j); k <= i * j; k++)
				printf("%.3lf ", dp[i][j][k]);
			printf("\n");
		}
	}
	*/

	double ans = 0;
	for (int i = max(N, M); i <= S; i++)
		ans += (dp[N][M][i] - dp[N][M][i-1]) * i;
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (scanf("%d%d", &N, &M) == 2) {
		printf("%.8lf\n", solve());
	}
	return 0;
}
