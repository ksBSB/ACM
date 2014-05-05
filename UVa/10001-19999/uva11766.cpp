#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1005;

int n, w[N][N], dp[N];

void init () {
	int a, b;
	memset(w, 0, sizeof(w));
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		w[a+1][n-b]++;
	}
}

int solve () {

	for (int i = 1; i <= n; i++) {
		dp[i] = 0;
		for (int j = 0; j < i; j++)
			dp[i] = max(dp[i], dp[j] + min(w[j+1][i], i - j));
	}
	return n - dp[n];
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init ();
		printf("Case %d: %d\n", cas++, solve());
	}
	return 0;
}
