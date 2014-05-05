#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
const int N = 70000;
const int M = 30;
const int MAX = 1 << 30;

int x[M], y[M], g[M][M];;
int n, m, dp[N], tmp;

void init() {
	memset(dp, -1, sizeof(dp));
	memset(g, 0, sizeof(g));
	scanf("%d%d", &n, &m);
	tmp = (1 << n) - 1;
	for (int i = 0; i < n; i++)
		scanf("%d%d", &x[i], &y[i]);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			for (int k = n - 1; k >= 0; k--) {
				g[i][j] <<= 1;
				if ((x[j] - x[i]) * (y[k] - y[i]) == (x[k] - x[i]) * (y[j] - y[i]))
					g[i][j]++;
			}
		}
	}
}

int handle(int k) {
	int cnt = 0;
	for (int i = 0; i < n; i++)
		if ((1 << i) & k) cnt++;
	return cnt;
}

int solve(int k) {
	int cnt = handle(k);
	int& ans = dp[k];
	if (cnt <= n - m) return ans = 0;
	else if (cnt == 1) return ans = 1;
	else if (ans > -1) return ans;
	ans = MAX;

	for (int i = 0; i < n; i++) {
		if ((1 << i) & k) {
			for (int j = i + 1; j < n; j++) {
				if ((1 << j) & k) {
					int t = k & (g[i][j] ^ tmp);
					ans = min(ans, solve(t) + 1);
				}
			}
		}
	}
	return ans;
}

int main () {
	int cas, t = 1;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("Case #%d:\n%d\n", t++, solve(tmp));
		if (cas) printf("\n");
	}
	return 0;
}
