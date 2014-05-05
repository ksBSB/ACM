#include <stdio.h>
#include <string.h>
const int N = 90000;

int n, m, k, w[N], g[N];

int read() {
	int a;
	memset(g, 0, sizeof(g));
	memset(w, 0, sizeof(w));
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i <= m; i++) {
		scanf("%d", &a);
		w[a] = i + 1;
	}
	for (int i = 0; i <= k; i++)
		scanf("%d", &g[i]);
}

int solve() {
	int dp[N], cnt = 0;
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i <= k; i++) {
		if (!w[g[i]]) continue;
		int flag = 1;

		for (int j = 0; j < cnt; j++) {
			if (w[g[i]] < w[dp[j]]) {
				dp[j] = g[i];
				flag = 0;
				break;
			}
		}

		if (flag) dp[cnt++] = g[i];
	}
	return cnt;
}

int main() {
	int cas, t = 1;
	scanf("%d", &cas);
	while (cas--) {
		read();
		printf("Case %d: %d\n", t++, solve());
	}
	return 0;
}
