#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 305;
const ll MOD = 1e9;

char s[N];
ll dp[N][N];

ll solve (int x, int y) {

	if (x == y)
		return dp[x][y] = 1;

	if (s[x] != s[y])
		return dp[x][y] = 0;

	ll& ans = dp[x][y];

	if (ans >= 0)
		return ans;
	ans = 0;

	for (int i = x+2; i <= y; i++) {
		if (s[x] == s[i])
			ans = (ans + solve(x+1, i-1) * solve(i, y))%MOD;
	}
	return ans;
}

int main () {
	while (scanf("%s", s) == 1) {
		memset(dp, -1, sizeof(dp));
		printf("%lld\n", solve(0, strlen(s)-1));
	}
	return 0;
}
