#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 205;

double P[maxn], dp[maxn][2];
int N, A[maxn];
char sig[maxn][2];

double solve (int bit, double s) {
	dp[0][0] = 1 - s, dp[0][1] = s;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 2; j++)
			dp[i][j] = dp[i-1][j] * P[i];
		double p = 1 - P[i];
		int v = (A[i]>>bit)&1;

		if (sig[i][0] == '&') {
			dp[i][v&0] += dp[i-1][0] * p;
			dp[i][v&1] += dp[i-1][1] * p;
		} else if (sig[i][0] == '|') {
			dp[i][v|0] += dp[i-1][0] * p;
			dp[i][v|1] += dp[i-1][1] * p;
		} else {
			dp[i][v^0] += dp[i-1][0] * p;
			dp[i][v^1] += dp[i-1][1] * p;
		}
	}
	return dp[N][1];
}

int main () {
	int cas = 1, s;
	while (scanf("%d", &N) == 1) {
		scanf("%d", &s);
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
		for (int i = 1; i <= N; i++) scanf("%s", sig[i]);
		for (int i = 1; i <= N; i++) scanf("%lf", &P[i]);

		double ans = 0;
		for (int i = 0; i <= 20; i++)
			ans += solve(i, (s>>i)&1) * (1<<i);
		printf("Case %d:\n%.6lf\n", cas++, ans);
	}
	return 0;
}
