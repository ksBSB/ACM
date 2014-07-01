#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 13;
int n, m;
ll set, dp[N+5][(1<<N)+5];

void solve (int d, int s, int pos) {
	if (pos == m) {
		dp[d][s] += set;
		return;
	}

	solve (d, s, pos + 1);

	if (pos + 2 <= m && (s&(1<<pos)) == 0 && (s&(1<<(pos+1))) == 0)
		solve(d, (s | (1<<pos) | (1<<(pos+1))), pos + 2);
}

int main () {
	while (scanf("%d%d", &n, &m), n + m) {

		memset(dp, 0, sizeof(dp));
		int e = (1<<m)-1;
		set = 1;
		solve(1, 0, 0);

		for (int i = 2; i <= n; i++) {
			for (int j = 0; j < (1<<m); j++) {
				if (dp[i-1][j])
					set = dp[i-1][j];
				else
					continue;
				solve(i, ~j & e, 0);
			}
		}
		printf("%lld\n", dp[n][e]);
	}
	return 0;
}
