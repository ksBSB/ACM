#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1<<17;

int n, tmp, dp[N], cover[N], link[N];

void init () {
	int m, k;
	memset(dp, 0, sizeof(dp));
	memset(cover, 0, sizeof(cover));
	memset(link, 0, sizeof(link));

	tmp = (1<<n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &m);
		link[i] |= (1<<i);
		for (int j = 0; j < m; j++) {
			scanf("%d", &k);
			link[i] |= (1<<k);
		}
	}	
	for (int i = 0; i < tmp; i++) {
		for (int j = 0; j < n; j++) if (i & (1<<j)) {
			cover[i] |= link[j];
		}
	}
}

int solve () {
	for (int i = 0; i < tmp; i++) {
		for (int j = i; j; j = (j-1)&i) {
			if (cover[j] == tmp-1) {
				dp[i] = max(dp[i], dp[i^j]+1);
			}
		}
	}
	return dp[tmp-1];
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {
		init();
		printf("Case %d: %d\n", cas++, solve());
	}
	return 0;
}
