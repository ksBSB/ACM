#include <stdio.h>
#include <string.h>
const int N = 20;

char str[N];
long long n, dp[N][N];

int change(char c) {
	if (c >= '1' && c <= '9') return c - '1';
	else return c - 'A' + 9;;
}

void init() {
	n = strlen(str);
	memset(dp, 0, sizeof(dp));
	if (str[0] == '?') {
		for (int i = 0; i < n; i++)
			dp[0][i] = 1;
	}
	else
		dp[0][change(str[0])] = 1;
}

long long solve() {
	init();
	for (int i = 1; i < n; i++) {
		if (str[i] == '?') {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < j - 1; k++)
					dp[i][j] += dp[i - 1][k];
				for (int k = j + 2; k < n; k++)
					dp[i][j] += dp[i - 1][k];
			}
		}
		else {
			int j = change(str[i]);
			for (int k = 0; k < j - 1; k++) 
				dp[i][j] += dp[i - 1][k];
			for (int k = j + 2; k < n; k++)
				dp[i][j] += dp[i - 1][k];
		}
	}
	long long sum = 0;
	for (int i = 0; i < n; i++)
		sum += dp[n - 1][i];
	return sum;
}

int main() {
	while (scanf("%s", str) == 1) {
		printf("%lld\n", solve());
	}
	return 0;
}
