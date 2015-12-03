#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 65540;
const int maxm = 65;

int K;
ll N, dp[maxm][maxn];

ll solve () {
	int s = 0, bit[maxm];
	for (int i = 60; i >= 0; i--) {
		bit[i] = N % 2;
		N /= 2;
	}

	memset(dp, 0, sizeof(dp));
	for (int i = 0; i <= 60; i++) {
		for (int j = 0; j < bit[i]; j++)
			dp[i][(s*3+j)%K]++;
		s = (s * 3 + bit[i]) % K;

		for (int j = 0; j < K; j++) {
			dp[i+1][j*3 % K] += dp[i][j];
			dp[i+1][(j*3+1)%K] += dp[i][j];
		}
	}
	dp[60][s]++;
	dp[60][0]--;

	ll ans = 0;
	for (int i = 0; i < K; i++)
		ans ^= dp[60][i];
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld%d", &N, &K);
		printf("%lld\n", solve());
	}
	return 0;
}
