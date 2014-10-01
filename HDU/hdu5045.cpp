#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 15;
const int maxm = 2005;
const int maxs = (1<<10) + 5;
const double INF = 0x3f3f3f3f;

int N, M;
double p[maxn][maxm], dp[maxm][maxm];

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= M; j++)
			scanf("%lf", &p[i][j]);
	}
}

double solve () {
	int T = 1<<N;
	for (int i = 0; i <= M; i++)
		for (int j = 0; j < T; j++)
			dp[i][j] = -INF;
	dp[0][0] = 0;

	for (int i = 1; i <= M; i++) {
		for (int s = 0; s < T; s++) {
			for (int k = 0; k < N; k++) {
				if (s & (1<<k))
					continue;
				dp[i][s | (1<<k)] = max(dp[i][s | (1<<k)], dp[i-1][s] + p[k][i]);
			}
		}
		dp[i][0] = dp[i][T-1];
	}

	double ret = 0;
	for (int i = 0; i < T; i++)
		ret = max(ret, dp[M][i]);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d: %.5lf\n", kcas, solve());
	}
	return 0;
}
