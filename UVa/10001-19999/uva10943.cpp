#include <stdio.h>
#include <string.h>

long long n, k, dp[105][105];

int main() {
    for (int i = 1; i <= 100; i ++) {
	dp[i][1] = 1;
	dp[1][i] = i;
    }
    for (int i = 2; i <= 100; i ++) {
	for (int j = 2; j <= 100; j ++) {
	    dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % 1000000;
	}
    }
    while (~scanf("%lld%lld", &n, &k) && n || k) {
	printf("%lld\n", dp[n][k]);
    }
    return 0;
}