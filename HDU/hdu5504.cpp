#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 100;

int N;
ll x, dp[maxn][2];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);

		dp[0][0] = dp[0][1] = 1;
		for (int i = 1; i <= N; i++) {
			scanf("%lld", &x);
			dp[i][0] = dp[i][1] = x;
			for (int j = 0; j < i; j++) {
				dp[i][0] = min(dp[i][0], min(dp[j][0] * x, dp[j][1] * x));
				dp[i][1] = max(dp[i][1], max(dp[j][0] * x, dp[j][1] * x));
			}
		}

		ll ans = dp[1][1];
		for (int i = 2; i <= N; i++)
			ans = max(ans, dp[i][1]);
		printf("%lld\n", ans);
	}
	return 0;
}
