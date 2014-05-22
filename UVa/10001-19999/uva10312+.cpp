#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 30;
ll f[N], dp[N][2];

ll solve (int n, int s) {

	ll& ans = dp[n][s];

	if (~ans)
		return ans;
	if (n <= 1)
		return ans = 1;

	ans = 0;

	for (int i = 1; i < n + s; i++)
		ans += solve(i, 1) * solve(n-i, 0);
	return ans;
}

int main () {
	f[1] = f[2] = 1;
	for (int i = 3; i <= 26; i++)
		f[i] = f[i-1] * (4*i-6) / i;

	int n;
	while (scanf("%d", &n) == 1) {
		memset(dp, -1, sizeof(dp));
		printf("%lld\n", solve(n, 0) - f[n]);
	}
	return 0;
}
