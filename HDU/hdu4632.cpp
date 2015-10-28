#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int mod = 10007;

char str[maxn];
int N, dp[maxn][maxn];

int solve () {
	N = strlen(str + 1);
	for (int i = 1; i <= N; i++) dp[i][i] = 1;
	for (int i = 1; i < N; i++)
		if (str[i] == str[i+1]) dp[i][i+1] = 3;
		else dp[i][i+1] = 2;

	for (int i = N; i; i--) {
		for (int j = i + 2; j <= N; j++) {
			dp[i][j] = ((dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1]) % mod + mod) % mod;
			if (str[i] == str[j])
				dp[i][j] = (dp[i][j] + dp[i+1][j-1] + 1) % mod;
		}
	}
	return dp[1][N];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", str + 1);
		printf("Case %d: %d\n", kcas, solve());
	}
	return 0;
}
