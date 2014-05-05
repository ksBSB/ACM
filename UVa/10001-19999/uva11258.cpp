#include <stdio.h>
#include <string.h>
#include <limits.h>
const int N = 205;
long long dp[N];
int n;
char str[N];
long long max(long long a, long long b) { return a > b ? a : b; }

void solve() {
	n = strlen(str);
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 10 && j <= i; j++) {
			long long sum = 0;
			for (int k = 0; k < j; k++) {
				sum = sum * 10 + str[i - j + k] - '0';
				if (sum >= 0 && sum <= INT_MAX)
					dp[i] = max(dp[i], dp[i - j] + sum);
				else
					break;
			}
		}
	}
}

int main() {
	int cas;
	scanf("%d%*c", &cas);
	while (cas--) {
		gets(str);
		solve();
		printf("%lld\n", dp[n]);
	}
	return 0;
}
