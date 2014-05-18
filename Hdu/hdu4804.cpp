#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 105;
const ll MOD = 1e9+7;

int n, m, c, d;
ll dp[2][25][(1<<11)+5];
char g[N][N];

ll solve () {
	int now = 0, pre = 1;
	int e = (1<<m)-1;

	memset(dp[now], 0, sizeof(dp[now]));
	dp[now][0][e] = 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			swap(now, pre);
			memset(dp[now], 0, sizeof(dp[now]));

			for (int k = 0; k <= d; k++) {
				for (int s = 0; s <= e; s++) {
					if (g[i][j] == '1') {
						if (s & (1<<j))
							dp[now][k+1][s] = (dp[now][k+1][s] + dp[pre][k][s])%MOD;

						if (j && !(s&(1<<(j-1))) && (s&(1<<j)))
							dp[now][k][s|(1<<(j-1))] = (dp[now][k][s|(1<<(j-1))] + dp[pre][k][s])%MOD;

						dp[now][k][s^(1<<j)] = (dp[now][k][s^(1<<j)] + dp[pre][k][s])%MOD;
					} else {
						if (s & (1<<j))
							dp[now][k][s] = (dp[now][k][s] + dp[pre][k][s])%MOD;
					}
				}
			}
		}
	}
	ll ans = 0;
	for (int i = c; i <= d; i++)
		ans = (ans + dp[now][i][e])%MOD;
	return ans;
}

int main () {
	while (scanf("%d%d%d%d", &n, &m, &c, &d) == 4) {
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		printf("%lld\n", solve());
	}
	return 0;
}
