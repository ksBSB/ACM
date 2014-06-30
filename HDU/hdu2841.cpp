#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int N = 100005;
typedef long long ll;
ll dp[N];

ll solve (ll n, ll m) {
	ll ans = 0;
	memset(dp, 0, sizeof(dp));

	for (ll i = 1; i <= n; i++) {

		ll tmp = m * i / n;
		dp[i] += tmp;
		ans += dp[i];

		for (ll j = 2; j*i <= n; j++)
			dp[i*j] -= dp[i];
	}
	return ans;
}

int main () {
	int cas;
	cin >> cas;
	while (cas--) {
		ll n, m;
		cin >> n >> m;
		cout << solve(n, m) + solve(m, n) - 1 << endl;
	}
	return 0;
}
