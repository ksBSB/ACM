#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int mod = 1000000007;
const int maxn = 1005;

int n;
char s[maxn];
ll bit[maxn], dp[maxn][maxn], ct[maxn][maxn];

int solve () {
	memset(ct, 0, sizeof(ct));
	memset(dp, 0, sizeof(dp));

	int l = strlen(s), c = n;
	ll sum = 0;
	for (int i = 0; i < l; i++) {
		for (int k = 0; k <= n; k++) {
			if (ct[i][k] == 0)
				continue;

			for (int j = 0; j < 2; j++) {
				if (j && k == 0)
					continue;

				ct[i+1][k-j] = (ct[i+1][k-j] + ct[i][k]) % mod;
				dp[i+1][k-j] = (dp[i+1][k-j] + dp[i][k] + bit[l-i-1] * j * ct[i][k]) % mod;
			}
		}

		for (int j = 0; j < s[i]-'0'; j++) {
			ct[i+1][c-j] = (ct[i+1][c-j] + 1) % mod;
			dp[i+1][c-j] = (dp[i+1][c-j] + sum + bit[l-i-1] * j) % mod;
		}

		if (s[i] == '1') {
			sum = (sum + bit[l-i-1]) % mod;
			c--;
		}
	}

	return dp[l][0];
}

int main () {
	bit[0] = 1;
	for (int i = 1; i <= 1000; i++)
		bit[i] = bit[i-1] * 2 % mod;
	while (scanf("%d%s", &n, s) == 2) {
		printf("%d\n", solve());
	}
	return 0;
}
