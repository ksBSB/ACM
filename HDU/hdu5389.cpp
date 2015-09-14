#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int mod = 258280327;
const int maxn = 1e5 + 5;

int N, A, B, dp[maxn][15], D[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d%d", &N, &A, &B);
		A %= 9, B %= 9;

		int s = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &D[i]);
			s = (s + D[i]) % 9;
		}

		if ((s - A + 9) % 9 != B) {
			int ans = 0;
			if (s == A)
				ans++;
			if (s == B)
				ans++;
			printf("%d\n", ans);
			continue;
		}

		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < 10; j++) {
				dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;
				dp[i][(j+D[i])%9] = (dp[i][(j+D[i])%9] + dp[i-1][j]) % mod;
			}
		}
		printf("%d\n", dp[N][A]);
	}
	return 0;
}
