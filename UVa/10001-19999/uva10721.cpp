#include <stdio.h>
#include <string.h>
#define ll long long
const int N = 105;

ll cnt[N][N];
int n, k, m;

void init() {
	memset(cnt, 0, sizeof(cnt));
	cnt[0][0] = 1;
}

void solve() {
	init();
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			for (int t = 1;  t <= m && t <= j; t++)
				cnt[i][j] += cnt[i - 1][j - t];
		}
	}	
	printf("%lld\n", cnt[k][n]);
}

int main () {
	while (scanf("%d%d%d", &n, &k, &m) == 3) {
		solve();
	}
	return 0;
}
