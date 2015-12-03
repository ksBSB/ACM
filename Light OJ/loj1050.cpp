#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 505;

int R, B;
double dp[maxn][maxn];

void init () {
	memset(dp, 0, sizeof(dp));
	dp[0][1] = 1;
	for (int i = 0; i <= 500; i++) {
		for (int j = i + 1; j <= 500; j++) {

			if (j > 1)
				dp[i][j] = dp[i][j-2] * j / (i + j);
			if (i)
				dp[i][j] += dp[i-1][j-1] * i / (i + j);
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	init();
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d", &R, &B);
		printf("Case %d: %.6lf\n", kcas, dp[R][B]);
	}
	return 0;
}
