#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 35;
const int maxm = 1800;
const int inf = 0x3f3f3f3f;

int N, M, W[maxn][maxn], dp[maxn][maxn][maxm];
int up[maxn][maxn], dn[maxn][maxn];

void init () {
	memset(up, 0, sizeof(up));
	memset(dn, inf, sizeof(dn));

	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &W[i][j]);

			up[i][j] = max(up[i-1][j], up[i][j-1]) + W[i][j];
			dn[i][j] = min(dn[i-1][j], dn[i][j-1]) + W[i][j];
			if (i == 1 && j == 1)
				up[i][j] = dn[i][j] = W[i][j];
		}
	}
}

int solve () {
	memset(dp, inf, sizeof(dp));
	dp[1][1][W[1][1]] = W[1][1] * W[1][1];

	for (int i = 1; i <= N; i++) {
		for (int j = (i == 1 ? 2 : 1); j <= M; j++) {
			for (int k = dn[i][j]; k <= up[i][j]; k++) {
				int& tmp = dp[i][j][k];

				if (dp[i-1][j][k-W[i][j]] != inf)
					tmp = min(tmp, dp[i-1][j][k-W[i][j]]);
				if (dp[i][j-1][k-W[i][j]] != inf)
					tmp = min(tmp, dp[i][j-1][k-W[i][j]]);
				if (tmp != inf)
					tmp += W[i][j] * W[i][j];
			}
		}
	}

	int ret = inf;
	for (int i = dn[N][M]; i <= up[N][M]; i++)
		if (dp[N][M][i] != inf)
			ret = min(ret, (N+M-1) * dp[N][M][i] - i * i);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d: %d\n", kcas, solve());
	}
	return 0;
}
