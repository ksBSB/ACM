#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const ll mod = 1000000007;
const int maxn = 55;

ll c[maxn][maxn], t[maxn], dp[maxn][maxn];

void init () {
	for (int i = 0; i <= 50; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mod;
	}

	t[0] = 1;
	for (int i = 1; i <= 50; i++)
		t[i] = t[i-1] * 2 % mod;

	for (int i = 0; i <= 50; i++)
		dp[i][1] = dp[1][i] = 1;

	for (int i = 2; i <= 50; i++) {
		for (int j = 2; j <= 50; j++) {
			dp[i][j] = dp[i][j-1] * (t[i] - 1) % mod;
			for (int k = 1; k < i; k++)
				dp[i][j] = (dp[i][j] + c[i][k] * t[i-k] % mod * dp[i-k][j-1] % mod) % mod;
		}
	}
}

int main () {
	init();
	int n, m;
	while (scanf("%d%d", &n, &m) == 2) {
		printf("%d\n", (int)dp[n][m]);
	}
	return 0;
}
