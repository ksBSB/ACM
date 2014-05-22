#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
ll dp[40];

ll solve(int n) {

	memset(dp, 0, sizeof(dp));
	dp[0] = dp[1] = 1;
	for (int i = 2; i <= n; i++) {

		for (int j = 1; j <= min(3, i); j++)
			dp[i] += dp[i-j];
	}
	
	ll ans = 0;
	for (int i = 0; i <= min(n, 2); i++)
		ans += dp[n-i];
	return (1LL<<n)-ans;
}

int main () {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("%lld\n", solve(n));
	}
	return 0;
}
