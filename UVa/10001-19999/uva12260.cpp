#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1005;
struct state {
	int p, j;
}s[N];
int n, k, sum, dp[N][N], val[N][N];

bool cmp(const state& a, const state& b) {
	if (a.p != b.p) return a.p > b.p;
	return a.j < b.j;
}

void init () {
	char str[N];

	sum = 0;
	memset(dp, 0, sizeof(dp));
	memset(val, 0, sizeof(val));
	scanf("%d%s", &n, str);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &s[i].p, &s[i].j);
		sum += s[i].p;
	}

	if (str[0] == 'P') k = 1;
	else k = 0;
	sort(s + 1, s + n + 1, cmp);
}

void solve () {
	for (int i = 1; i <= n-k; i++) {
		for (int j = 1; j <= (i+1)/2; j++) {
			if (dp[i-1][j] > dp[i-1][j-1] + s[i+k].j) {
				dp[i][j] = dp[i-1][j];
				val[i][j] = val[i-1][j];
			} else if (dp[i-1][j] == dp[i-1][j-1] + s[i+k].j) {
				dp[i][j] = dp[i-1][j];
				val[i][j] = min(val[i-1][j], val[i-1][j-1]+s[i+k].p);
			} else {
				dp[i][j] = dp[i-1][j-1] + s[i+k].j;
				val[i][j] = val[i-1][j-1] + s[i+k].p;
			}
		}
	}
	printf("%d %d\n", sum - val[n-k][(n-k+1)/2], dp[n-k][(n-k+1)/2]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
