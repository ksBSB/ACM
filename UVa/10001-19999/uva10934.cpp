#include <stdio.h>
#include <string.h>

const int N = 105;
typedef long long ll;

int k;
ll n, dp[N][N];

void init () {
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 63; j++)
			dp[i][j] = dp[i][j-1] + dp[i-1][j-1]+1;
	}
}

bool judge () {

	for (int i = 1; i <= 63; i++) {
		if (dp[k][i] >= n) {
			printf("%d\n", i);
			return true;
		}
	}
	return false;
}

int main () {
	init ();
	while (scanf("%d%lld", &k, &n) == 2 && k && n) {
		if (!judge()) printf("More than 63 trials needed.\n");
	}
	return 0;
}
