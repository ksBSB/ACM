#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N = 30;
const ll INF = 0x3f3f3f3f3f3f3f;
int x, y, z;
ll g[N][N][N], s[N][N][N];

void init() {
	memset(s, 0, sizeof(s));
	scanf("%d%d%d", &x, &y, &z);
	for (int i = 1; i <= x; i++) {
		for (int j = 1; j <= y; j++) {
			for (int k = 1; k <= z; k++) {
				scanf("%lld", &g[i][j][k]);
				s[j][k][i] = s[j][k-1][i] + s[j-1][k][i] - s[j-1][k-1][i] + g[i][j][k];
			}
		}
	}
}

ll count(int n, int m, int p, int q, int x) {
	return s[m][q][x] - s[n][q][x] - s[m][p][x] + s[n][p][x];
}

ll solve() {
	ll ans = -INF, dp[N];
	for (int n = 1; n <= y; n++) {
		for (int m = n; m <= y; m++) {
			for (int p = 1; p <= z; p++) {
				for (int q = p; q <= z; q++) {
					memset(dp, 0, sizeof(dp));
					for (int i = 1; i <= x; i++) {
						ll t = count(n-1, m, p-1, q, i);
						dp[i] = max(dp[i-1] + t, t);
						ans = max(dp[i], ans);
					}
				}
			}
		}
	}
	return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%lld\n", solve());
		if (cas) printf("\n");
	}
	return 0;
}
