#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1005;
const int M = 30;
const int INF = 0x3f3f3f3f;

int n, k, v[N][M], dp[N][M], c[N];

void init () {
	char str[N];
	memset(c, 0, sizeof(c));
	memset(v, 0, sizeof(v));
	memset(dp, INF, sizeof(dp));

	scanf("%d%s", &k, str);		
	n = strlen(str);
	for (int i = 0; i < n; i += k) {
		for (int j = 0; j < k; j++) {
			int u = str[j+i] - 'a';
			if (v[i][u] == 0) c[i]++;
			v[i][u]++;
		}
	}
}

int solve () {
	if (n == k) return c[0];

	int ans = INF;
	for (int i = 0; i < 26; i++) if (v[0][i]) dp[0][i] = c[0];

	for (int i = k; i < n; i += k) {
		for (int j = 0; j < 26; j++) if (v[i-k][j]) {

			for (int t = 0; t < 26; t++) {
				if (!v[i][t]) continue;
				if (v[i][j] && (j != t || c[i] == 1)) {
					dp[i][t] = min(dp[i][t], dp[i-k][j]+c[i]-1);
				} else 
					dp[i][t] = min(dp[i][t], dp[i-k][j]+c[i]);
				if (n == i + k)
					ans = min(dp[i][t], ans);
			}
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
