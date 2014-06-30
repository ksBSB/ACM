#include <stdio.h>
#include <string.h>
const int N = 205;

int n, q, num[N], rec[N];
long long dp[15][N * N];

void read() {	
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);
}

void solve(int cas) {
	int D, N, sum = 0;
	long long ans = 0;
	scanf("%d%d", &D, &N);
	for (int i = 0; i < n; i++) {
		rec[i] = (num[i] % D + D) % D;
		sum += rec[i];
	}

	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = N - 1; j >= 0; j--) {
			for (int k = 0; k <= sum; k++)
				dp[j + 1][k + rec[i]] += dp[j][k];
		}
	}
			

	for (int i = 0; i <= sum; i += D)
		ans += dp[N][i];
	printf("QUERY %d: %lld\n", cas, ans);
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &n, &q), n + q) {
		read();
		printf("SET %d:\n", cas++);
		for (int i = 0; i < q; i++)
			solve(i + 1);
	}
	return 0;
}
