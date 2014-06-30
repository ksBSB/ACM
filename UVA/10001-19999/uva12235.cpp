#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 105;
const int M = (1<<8);
const int INF = 0x3f3f3f3f;

int n, K, dp[2][N][M+5][10];

int bitcount(int s) {
	return s == 0 ? 0 : bitcount(s>>1) + (s&1);
}

int main () {
	int cas = 1, a;
	while (scanf("%d%d", &n, &K) == 2 && n + K) {
		int all = 0;
		memset(dp[0], INF, sizeof(dp[0]));

		for (int i = 0; i < n; i++) {
			scanf("%d", &a);
			a -= 25;
			int p = i&1;
			int q = !p;
			memset(dp[q], INF, sizeof(dp[q]));
			dp[q][i][1<<a][a] = 1;

			for (int j = 0; j <= min(K, i); j++) {

				for (int s = all; s; s = (s-1)&all) {
					for (int x = 0; (1<<x) <= s; x++) {

						if (dp[p][j][s][x] != INF) {
							if (x == a) dp[q][j][s][x] = min(dp[q][j][s][x], dp[p][j][s][x]);
							else {
								dp[q][j][s|(1<<a)][a] = min(dp[q][j][s|(1<<a)][a], dp[p][j][s][x]+1);
								dp[q][j+1][s][x] = min(dp[q][j+1][s][x], dp[p][j][s][x]);
							}
						}
					}
				}
			}
			all |= (1<<a);
		}

		int ans = INF;
		for (int i = 0; i <= K; i++) {
			for (int s = all; s; s = (s-1)&all) {
				for (int x = 0; (1<<x) <= s; x++) if (dp[n&1][i][s][x] != INF) {
					ans = min(dp[n&1][i][s][x]+bitcount(s^all), ans);
				}
			}
		}
		printf("Case %d: %d\n\n", cas++, ans);
	}
	return 0;
}
