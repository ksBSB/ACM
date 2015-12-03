#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 505;

int N, M, dp[maxn][maxn];
int A[maxn][maxn], B[maxn][maxn];
//int H[maxn][maxn], C[maxn][maxn];

void init () {
	scanf("%d%d", &N, &M);
	int x;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &x);
			A[i][j] = A[i][j-1] + x;
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &x);
			B[i][j] = B[i-1][j] + x;
		}
	}
}

int solve () {
	//memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++)
			dp[i][j] = max(dp[i-1][j] + A[i][j], dp[i][j-1] + B[i][j]);
	}
	return dp[N][M];
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
