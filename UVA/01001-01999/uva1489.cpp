#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 55;
const ll MOD = 1000000003LL;

ll N, K;
ll dp[maxn][maxn], num[maxn];

int main () {
	while (scanf("%lld%lld", &N, &K) == 2 && (N + K)) {
		ll ans = 0;
		for (int i = 1; i <= N; i++)
			scanf("%lld", &num[i]);

		int bit;
		for (bit = 30; bit >= 0; bit--) {
			memset(dp, 0, sizeof(dp));
			dp[0][0] = 1;

			ll cnt = 0, bits = (1<<bit);
			for (int i = 1; i <= N; i++) {

				if (num[i]&bits) {
					cnt++;
					for (int j = 0; j <= cnt; j++)
						dp[i][j] = dp[i-1][j] * (num[i] - bits + 1) % MOD;
					dp[i][1] = (dp[i][1] + dp[i-1][0]) % MOD;
					for (int j = 2; j <= cnt; j++)
						dp[i][j] = (dp[i-1][j-1] * bits + dp[i][j]) % MOD;

					num[i] -= bits;
				} else {
					for (int j = 0; j <= cnt; j++)
						dp[i][j] = dp[i-1][j] * (num[i] + 1) % MOD;
				}
			}

			for (int i = 1; i <= cnt; i++)
				if ( ((cnt - i)&1) == ((K>>bit)&1) )
					ans = (ans + dp[N][i]) % MOD;

			if ( (cnt&1) != ((K>>bit)&1) ) 
				break;
		}
		if (bit == -1)
			ans++;
		printf("%lld\n", ans);
	}
	return 0;
}
