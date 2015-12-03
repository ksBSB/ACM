#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 50;

ll dp[maxn + 5][maxn + 5][2];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		int n, bit[maxn + 5];
		scanf("%d", &n);
		for (int i = maxn; i >= 0; i--) {
			bit[i] = (n&1);
			n >>= 1;
		}

		int p = 0;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= maxn; i++) {
			for (int k = 0; k < maxn; k++) {
				for (int x = 0; x < 2; x++)
					for (int y = 0; y < 2; y++) {
						int v = k + (x&y);
						dp[i][v][y] += dp[i-1][k][x];
					}
			}
			for (int j = 0; j < bit[i]; j++)
				dp[i][p][j]++;
			if (bit[i-1] && bit[i]) p++;
		}
		ll ret = p;
		for (int i = 0; i < maxn; i++)
			ret += (dp[maxn][i][0] + dp[maxn][i][1]) * i;
		printf("Case %d: %lld\n", kcas, ret);
	}
	return 0;
}
