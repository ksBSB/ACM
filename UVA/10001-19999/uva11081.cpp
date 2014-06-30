#include <stdio.h>
#include <string.h>
const int N = 70;
const int tmp = 10007;

int dp[N][N][N], dp1[N][N][N], dp2[N][N][N];
char s1[N], s2[N], s3[N];

int solve() {
	int len1 = strlen(s1 + 1);
	int len2 = strlen(s2 + 1);
	int len3 = strlen(s3 + 1);
	memset(dp, 0, sizeof(dp));
	memset(dp1, 0, sizeof(dp1));
	memset(dp2, 0, sizeof(dp2));

	for (int i = 0; i <= len1; i++)
	   for (int j = 0; j <= len2; j++)
			dp[i][j][0] = dp1[i][j][0] = dp2[i][j][0] = 1;	   

	for (int k = 1; k <= len3; k++) {
		for (int i = 0; i <= len1; i++) {
			for (int j = 0; j <= len2; j++) {
				if (i) {
					dp1[i][j][k] = dp1[i - 1][j][k];
					if (s1[i] == s3[k])
						dp1[i][j][k] += dp[i - 1][j][k - 1];
					dp1[i][j][k] %= tmp;
				}
				if (j) {
					dp2[i][j][k] = dp2[i][j - 1][k];
					if (s2[j] == s3[k])
						dp2[i][j][k] += dp[i][j - 1][k - 1];
					dp2[i][j][k] %= tmp;
				}
				dp[i][j][k] = (dp1[i][j][k] + dp2[i][j][k]) % tmp;
			}
		}
	}
	return dp[len1][len2][len3];
}

int main() {
	int cas;
	scanf("%d",&cas);
	while (cas--) {
		scanf("%s%s%s", s1 + 1, s2 + 1, s3 + 1);
		printf("%d\n", solve());
	}
	return 0;
}
