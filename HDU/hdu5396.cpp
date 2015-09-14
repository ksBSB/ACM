#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100;
const int mod = 1e9 + 7;
typedef long long ll;

int C[maxn + 5][maxn + 5], F[maxn + 5];

int N, dp[maxn + 5][maxn + 5];
char order[maxn + 5];

void init () {
	for (int i = 0; i <= maxn; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
	}
	F[0] = 1;
	for (int i = 1; i <= maxn; i++)
		F[i] = 1LL * i * F[i-1] % mod;
}

int main () {
	init ();
	while (scanf("%d", &N) == 1) {
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < N; i++) scanf("%d", &dp[i][i]);
		scanf("%*c");
		gets(order);

		N--;
		for (int i = N-1; i >= 0; i--) {
			for (int j = i + 1; j <= N; j++) {
				int len = j - i - 1;
				for (int k = i; k < j; k++) {
					int l = k - i, r = j - k - 1;

					ll ret = 0;
					if (order[k] == '+') {
						ret = (ret + 1LL * dp[i][k] * F[r]) % mod;
						ret = (ret + 1LL * dp[k+1][j] * F[l]) % mod;

					} else if (order[k] == '-') {
						ret = (ret + 1LL * dp[i][k] * F[r]) % mod;
						ret = ((ret - 1LL * dp[k+1][j] * F[l]) % mod + mod) % mod;
					} else if (order[k] == '*')
						ret = 1LL * dp[i][k] * dp[k+1][j] % mod;
					dp[i][j] = (dp[i][j] + ret * C[len][l]) % mod;
				}
				//printf("%d %d: %d\n", i, j, dp[i][j]);
			}
		}
		printf("%d\n", dp[0][N]);
	}
	return 0;
}
