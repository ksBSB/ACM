#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 50;
ll dp[N];

void init () {
	memset(dp, 0, sizeof(dp));
	dp[0] = dp[1] = 1;
	for (int i = 2; i <= 40; i++)
		dp[i] = dp[i-1] + dp[i-2];
}

void solve (ll n) {
	bool flag = false;	

	for (int i = 40; i; i--) {
		if (n >= dp[i]) {
			printf("1");
			n -= dp[i];
			flag = true;
		} else if (flag)
			printf("0");
	}
	printf("\n");
}

int main () {
	init ();
	int cas;
	ll n;
	scanf("%d", &cas);
	for (int i = 0; i < cas; i++) {
		scanf("%lld", &n);
		solve(n);
	}
	return 0;
}
