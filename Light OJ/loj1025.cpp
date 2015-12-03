#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 65;
typedef long long ll;

char s[maxn];
ll dp[maxn][maxn];

ll solve () {
	int n = strlen(s+1);
	for (int i = 1; i <= n; i++) dp[i][i] = 1;
	for (int i = 1; i < n; i++) dp[i][i+1] = (s[i] == s[i+1] ? 3 : 2);

	for (int i = n; i; i--) {
		for (int j = i + 2; j <= n; j++) {
			dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
			if (s[i] == s[j])
				dp[i][j] += dp[i+1][j-1] + 1;
		}
	}
	return dp[1][n];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", s+1);
		printf("Case %d: %lld\n", kcas, solve());
	}
	return 0;
}
