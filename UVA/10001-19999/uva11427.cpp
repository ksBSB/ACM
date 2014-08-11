#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

double dp[maxn][maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int a, b, n;
		scanf("%d/%d%d", &a, &b, &n);
		double p = (double)a / b;
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		dp[0][1] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j * b <= a * i; j++) {
				dp[i][j] = dp[i-1][j] * (1-p);
				if (j)
					dp[i][j] += dp[i-1][j-1] * p;
			}
		}

		double q = 0;
		for (int i = 0; i * b <= a * n; i++)
			q += dp[n][i];
		printf("Case #%d: %d\n", kcas, (int)(1/q));
	}
	return 0;
}
