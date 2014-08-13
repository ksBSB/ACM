#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int maxn = 1505;

int N;
ll x, y, z, T;
ll dp[maxn][maxn];

ll solve () {
	ll ans = 0;
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i < N; i++) {

		for (int j = 0; j <= i; j++) {
			ll v = (T + j * z);
			ll w = v * (i-j) * y;
			dp[i+1][j] = max(dp[i+1][j], dp[i][j] + w);
			dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + w);
			ans = max(ans, dp[i][j] + (x * v + w) * (N-i));
		}
	}

	for (int i = 0; i <= N; i++)
		ans = max(ans, dp[N][i]);
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%I64u%I64u%I64u%I64u", &N, &x, &y, &z, &T);
	//	scanf("%d%lld%lld%lld%lld", &N, &x, &y, &z, &T);
	//	printf("Case #%d: %lld\n", kcas, solve());
		printf("Case #%d: %I64u\n", kcas, solve());
	}
	return 0;
}
