#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1005;

ll dp[N][5][2], ans[N];

void init () {
	for (int s = 0; s < 2; s++) {

		dp[1][0][s] = 1;

		for (int i = 2; i < N; i++) {
			for (int j = 0; j <= 4; j++) {
				dp[i][j][s] = dp[i-1][j][s];
				if (j)
					dp[i][j][s] += dp[i-1][j-1][s];
			}
		}
	}

	memset(ans, 0, sizeof(ans));
	for (int i = 1; i < N; i++) {
		if (i < 4 || (i&1))
			continue;

		int t = (i + 4) / 2;
		ans[i] = dp[t][3][0] + dp[t][4][1] + dp[t][4][0];
	}
}

int main () {
	init ();
	int n, cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		printf("Case %d: %lld\n", cas++, ans[n]);
	}
	return 0;
}
