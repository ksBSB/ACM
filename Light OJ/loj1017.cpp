#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, W, M, G[maxn], Y[maxn];

void init () {
	scanf("%d%d%d", &N, &W, &M);
	int x;
	for (int i = 0; i < N; i++)
		scanf("%d%d", &x, &Y[i]);
	sort(Y, Y + N);
	x = 0;
	for (int i = 0; i < N; i++) {
		while (x < N && Y[x] <= Y[i] + W) x++;
		G[i] = x;
	}
}

int dp[maxn][maxn];

int solve () {
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < N; j++) {
			dp[i][G[j]] = max(dp[i][G[j]], dp[i-1][j] + G[j] - j);
			dp[i][j+1] = max(dp[i][j+1], dp[i][j]);
		}
	}
	return dp[M][N];
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
