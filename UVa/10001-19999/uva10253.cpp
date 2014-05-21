#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 35;

ll f[N], dp[N][N];

ll C(ll n, ll m) {
	double ans = 1;
	for (ll i = 0; i < m; i++)
		ans *= n - i;

	for (ll i = 1; i <= m; i++)
		ans /= i;
	return (ll)(ans+0.5);
}

void init () {
	f[1] = 1;
	int n = 30;
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i <= n; i++)
		dp[i][0] = 1;

	for (int i = 1; i <= n; i++) {
		dp[i][1] = 1;
		dp[0][i] = 0;
	}

	for (int i = 1; i <= n; i++) {

		for (int j = 2; j <= n; j++) {
//			dp[i][j] = 0;
			for (int p = 0; p * i <= j; p++)
				dp[i][j] += dp[i-1][j-i*p] * C(f[i]+p-1, p);
		}
		f[i+1] = dp[i][i+1];
	}
}

int main () {
	init ();
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("%lld\n", n == 1 ? 1 : 2 * f[n]);
	}
	return 0;
}
