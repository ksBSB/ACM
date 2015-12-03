#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 55;
const int maxs = 1<<17;
const int inf = 0x3f3f3f3f;

int N, M, K, X[maxn], Y[maxn], dp[maxs][maxn];
char G[maxn][maxn];

void init () {
	K = 0;
	scanf("%d%d", &N, &M);

	for (int i = 1; i <= N; i++) {
		scanf("%s", G[i] + 1);
		for (int j = 1; j <= M; j++) {
			if (G[i][j] == 'g') {
				K++;
				X[K] = i;
				Y[K] = j;
			}

			if (G[i][j] == 'x') {
				X[0] = i;
				Y[0] = j;
			}
		}
	}
}

int getdistance(int x, int y) {
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	return max(x, y);
}

int solve () {
	memset(dp, inf, sizeof(dp));
	K++;
	dp[0][0] = 0;
	for (int s = 0; s < (1<<K); s++) {
		for (int i = 0; i < K; i++) {
			if (s&(1<<i)) continue;
			int v = s | (1<<i);
			for (int j = 0; j < K; j++)
				dp[v][j] = min(dp[v][j], dp[s][i] + getdistance(X[i]-X[j], Y[i]-Y[j]));
		}
	}
	return dp[(1<<K)-1][0];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d: %d\n", kcas, solve());
	}
	return 0;
}
