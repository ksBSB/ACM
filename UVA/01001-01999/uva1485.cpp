#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1000;
const ll MOD = 1e9+7;

int N, K;
ll dp[maxn+5][maxn+5];

void init () {
	memset(dp, 0, sizeof(dp));

	dp[0][0] = 1;
	for (int i = 0; i <= maxn; i++) {
		for (int j = 0; j <= i; j++) {
			dp[j][i+1] = (dp[j][i+1] + (j + 1) * dp[j][i]) % MOD;
			dp[j+1][i+1] = (dp[j+1][i+1] + (i - j) * dp[j][i]) % MOD;
		}
	}
}

int main () {
	init();
	while (scanf("%d%d", &N, &K) == 2) {
		printf("%lld\n", dp[K][N]);
	}
	return 0;
}
