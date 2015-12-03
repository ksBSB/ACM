#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50;
typedef long long ll;

int N, M, d[maxn][maxn];
char a[maxn], b[maxn];

int lcs () {
	memset(d, 0, sizeof(d));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (a[i] == b[j])
				d[i][j] = d[i-1][j-1] + 1;
			else
				d[i][j] = max(d[i-1][j], d[i][j-1]);
		}
	}
	return d[N][M];
}

ll dp[maxn*2][maxn][maxn];

ll solve (int K) {
	memset(dp, 0, sizeof(dp));
	//dp[0][0][0] = 1;
	for (int i = 0; i <= N; i++)
		dp[i][i][0] = 1;
	for (int i = 0; i <= M; i++)
		dp[i][0][i] = 1;

	for (int k = 1; k <= K; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (a[i] == b[j])
					dp[k][i][j] = dp[k-1][i-1][j-1];
				else
					dp[k][i][j] = dp[k-1][i-1][j] + dp[k-1][i][j-1];
			}
		}
	}
	return dp[K][N][M];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s%s", a+1, b+1);
		N = strlen(a+1);
		M = strlen(b+1);
		int ans = N + M - lcs();
		printf("Case %d: %d %lld\n", kcas, ans, solve(ans));
	}
	return 0;
}
