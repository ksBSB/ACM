#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 5005;

int N, M, K;
ll arr[maxn], sum[maxn];
ll dp[maxn][maxn];

ll solve () {
	ll ret = 0;
	for (int i = M; i <= N; i++) {

		ll tmp = sum[i] - sum[i-M];
		for (int j = 1; j <= K; j++)
			dp[i][j] = max(dp[i-1][j], dp[i-M][j-1] + tmp);
		ret = max(ret, dp[i][K]);
	}
	return ret;
}

int main () {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &arr[i]);
		sum[i] = sum[i-1] + arr[i];
	}
	printf("%lld\n", solve());
	return 0;
}
