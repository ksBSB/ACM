#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2 * 1e5 + 5;

int N, M, X[105];
double dp[2][maxn];

int main () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) scanf("%d", &X[i]);
	if (M == 1)
		printf("%.10lf\n", 1.0);
	else {

		int nw = 0, nx = 1, s = 0;
		memset(dp[nx], 0, sizeof(dp[nx]));
		dp[nx][0] = M - 1;

		for (int i = 1; i <= N; i++) {
			swap(nw, nx);
			memset(dp[nx], 0, sizeof(dp[nx]));
			for (int j = 0; j <= i * M; j++) {
				double p = dp[nw][j] / (M-1);
				dp[nx][j+1] += p;
				dp[nx][j+M+1] -= p;

				dp[nx][j + X[i]] -= p;
				dp[nx][j + X[i] + 1] += p;
			}
			for (int j = 1; j <= (i + 1) * M; j++)
				dp[nx][j] += dp[nx][j-1];
			s += X[i];
		}

		double ans = 0;
		for (int i = 0; i < s; i++) ans += dp[nx][i];
		printf("%.10lf\n", ans + 1);
	}
	return 0;
}
