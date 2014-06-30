#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 50;

int s, e;
ll dp[N][N];

ll solve () {
	memset(dp, 0, sizeof(dp));

	dp[1][s] = 1;
	for (int i = 2; i < N; i++) {

		for (int j = s+i-2; j < N; j++) {
			if (dp[i-1][j]) {
				for (int k = j+1; k < N; k++) {
					if (k % (k - j))
							continue;
					dp[i][k] += dp[i-1][j];
				}
			}
		}
	}

	ll ans = 0;
	for (int i = 1; i < N; i++)
		ans += dp[i][e];
	return ans;
}

int main () {
	while (scanf("%d%d", &s, &e) == 2 && s + e) {
		printf("%d %d %lld\n", s, e, solve());
	}
	return 0;
}
