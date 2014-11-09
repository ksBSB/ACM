#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int inf = 0x3f3f3f3f;
int N, M, g[maxn][maxn], dp[maxn][maxn], vi[maxn][maxn];

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &g[i][j]);
//	memset(vi, -1, sizeof(vi));
	memset(dp, 0, sizeof(dp));
}

void solve () {

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int x = dp[i-1][j], y = j;
			if (j > 1 && dp[i-1][j-1] < x) {
				x = dp[i-1][j-1];
				y = j-1;
			}

			if (j < M && dp[i-1][j+1] <= x) {
				x = dp[i-1][j+1];
				y = j+1;
			}

			dp[i][j] = x + g[i][j];
			vi[i][j] = y;
		}
	}

	int ans = dp[N][1], idx = 1, pos[maxn];
	for (int i = 2; i <= M; i++) if (dp[N][i] <= ans) {
		ans = dp[N][i];
		idx = i;
	}

	for (int i = N; i; i--) {
		pos[i] = idx;
		idx = vi[i][idx];
	}
	for (int i = 1; i <= N; i++)
		printf("%d%c", pos[i], i == N ? '\n' : ' ');
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		printf("Case %d\n", kcas);
		init();
		solve();
	}

	return 0;
}
