#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxd = 10;
const int status = 4;
const int g[4][12] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{3, 3, 3, 3, 3, 3, 0, 3, 3, 3},
	{3, 3, 3, 3, 3, 3, 1, 3, 3, 3},
	{3, 3, 3, 3, 3, 3, 2, 3, 3, 3}};

ll n, dp[maxd+5][status];

int main () {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 1; i <= maxd; i++) {
		dp[i][0] = (dp[i-1][0] + dp[i-1][1] + dp[i-1][2]) * 9;
		dp[i][1] = dp[i-1][0];
		dp[i][2] = dp[i-1][1];
		dp[i][3] = dp[i-1][3] * 10 + dp[i-1][2];
	}

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld", &n);

		int d = 0, u = 3;
		while (dp[d][3] < n)
			d++;

		while (d) {

			ll k = 0;

//			printf("%d:\n", d);
			for (int i = 0; i < 10; i++) {
				ll tmp = 0;

				for (int j = 3; j >= g[u][i]; j--)
					tmp += dp[d-1][j];

//				printf("n:%lld status: %d %d %lld\n", n, u, i, tmp);
				if (k + tmp >= n) {
					printf("%d", i);
					u = g[u][i];
					break;
				}
				k += tmp;
			}
			n -= k;
			d--;
		}
		printf("\n");
	}
	return 0;
}
