#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 20;
const int maxm = 1<<17;

int N, dp[maxn][maxm], W[maxn][maxn];

int bitcount(int s) { return s == 0 ? 0 : bitcount(s>>1) + (s&1); }

int solve () {
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < N; i++)
		dp[0][1<<i] = W[0][i];
	int n = (1<<N);
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < n; j++) {
			if (bitcount(j) != i) continue;
			for (int k = 0; k < N; k++) {
				if (j&(1<<k)) continue;
				int v = j | (1<<k);
				dp[i][v] = max(dp[i][v], dp[i-1][j] + W[i][k]);
			}
		}
	}
	return dp[N-1][n-1];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				scanf("%d", &W[i][j]);
		}
	printf("Case %d: %d\n", kcas, solve());
	}
	return 0;
}
