#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

const int N = 1000005;

int n, vis[N], a[N];
__int64 sum[N], cnt,  dp[N];

void init() {
	memset(vis, -1, sizeof(vis));
	memset(sum, 0, sizeof(sum));

	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		sum[i - vis[a[i]]]++;
		vis[a[i]] = i;
	}

	for (int i = n - 1; i >= 0; i--)
		sum[i] += sum[i + 1];
}

void solve() {
	memset(dp, 0, sizeof(dp));
	dp[1] = n;

	memset(vis, 0, sizeof(vis));
	vis[a[n - 1]] = cnt = 1;

	for (int i = 2; i <= n; i++) {
		dp[i] = dp[i - 1] - cnt + sum[i];

		vis[a[n - i]]++;
		if (vis[a[n - i]] == 1) cnt++;
	}
}

int main () {
	while (scanf("%d", &n), n) {
		init();
		solve();
		int q, w;
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d", &w);
			printf("%I64d\n", dp[w]);
		}
	}
	return 0;
}
