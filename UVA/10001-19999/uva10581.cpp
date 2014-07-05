#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 220;
const int maxp = 10;

int M, N;
ll K, dp[maxp+5][maxn+5][maxn+5];

ll dfs (int d, int x, int s) {
	if (d == N) {
		if (0 == s)
			return 1;
		else
			return 0;
	}

	ll& ans = dp[d][x][s];

	if (ans != -1)
		return ans;

	ans = 0;

	for (int i = x; ; i++) {
		if ((N-d) * i > s)
			break;
		ans += dfs(d+1, i, s-i);
	}
	return ans;
}

void solve () {
	int s = M, t = 1;
	for (int i = 1; i < N; i++) {
		for (int j = t; ; j++) {
			ll u = dp[i][j][s-j];

			if (K > u) {
				K -= u;
			} else {
				printf("%d\n", j);
				s -= j;
				t = j;
				break;
			}
		}
	}
	printf("%d\n", s);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%lld", &M, &N, &K);

		memset(dp, -1, sizeof(dp));
		for (int i = 1; i * N <= M; i++)
			ll u = dfs(1, i, M-i);
		solve();
	}
	return 0;
}
