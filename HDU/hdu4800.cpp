#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10005;
const int maxm = 125;

int M;
double G[maxm][maxm], dp[maxn][maxm];

double solve () {
	int n, x;
	scanf("%d", &n);
	for (int i = 0; i < M; i++) dp[0][i] = 1;

	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		dp[i+1][x] = 0;
		for (int j = 0; j < M; j++) {
			double p = G[j][x];
			if (j != x) dp[i+1][j] = dp[i][j] * p;
			dp[i+1][x] = max(dp[i][j] * p, dp[i+1][x]);
		}
	}
	double ans = 0;
	for (int i = 0; i < M; i++) ans = max(ans, dp[n][i]);
	return ans;
}

int main () {
	while (scanf("%d", &M) == 1) {
		M = M * (M-1) * (M-2) / 6;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < M; j++)
				scanf("%lf", &G[i][j]);
		printf("%.6lf\n", solve());
	}
	return 0;
}
