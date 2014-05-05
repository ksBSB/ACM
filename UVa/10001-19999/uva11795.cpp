#include <stdio.h>
#include <string.h>

typedef long long ll;
const int N = 17;
const int M = 1<<N;

int n, g[N], h[M];
ll dp[M];

int get() {
	char str[M];
	scanf("%s", str);
	int len = strlen(str), ans = 0;
	for (int i = 0; i < len; i++) if (str[i] == '1')
		ans |= (1<<i);
	return ans;
}

void init () {
	scanf("%d", &n);
	h[0] = get();
	for (int i = 0; i < n; i++) g[i] = get();
	for (int i = 0; i < (1<<n); i++) {
		h[i] = h[0];
		for (int j = 0; j < n; j++) if (i & (1<<j)) {
			h[i] |= g[j];
		}
	}
}

ll solve() {
	dp[0] = 1;
	for (int i = 1; i < (1<<n); i++) {
		dp[i] = 0;
		for (int j = 0; j < n; j++) if (i&(1<<j) && h[i^(1<<j)]&(1<<j))
			dp[i] += dp[i^(1<<j)];
	}
	return dp[(1<<n)-1];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %lld\n", i, solve());
	}
	return 0;
}
