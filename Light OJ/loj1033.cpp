#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, dp[maxn][maxn];
char s[maxn], t[maxn];

int solve () {
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			if (s[i] == t[j])
				dp[i][j] = dp[i-1][j-1] + 1;
			else
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
	}
	return dp[N][N];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", s + 1);
		N = strlen(s + 1);
		for (int i = 1; i <= N; i++)
			t[i] = s[N-i+1];
		printf("Case %d: %d\n", kcas, N - solve());
	}
	return 0;
}
