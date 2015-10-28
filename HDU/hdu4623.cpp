#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int be[] = {0, 0, 1, 2, 1, 3, 4, 5, 1, 2, 6, 7, 4, 8, 9, 10, 1, 0, 4, 0, 6, 11, 12, 0, 4, 3, 13, 2, 9};
const int maxn = 2 * 1e6 + 5;
int f[] = {1, 2, 3, 5, 6, 7, 10, 11, 13, 14, 15, 21, 22, 26};

int N, mod, bit[16], dp[maxn][16];
bool ok[16][16];

int idx(int* c) {
	int ret = 0;
	for (int i = 0; i <= N; i++)
		ret = ret * bit[i] + c[i];
	return ret;
}

void ridx(int n, int* c) {
	for (int i = N; i >= 0; i--) {
		c[i] = n % bit[i];
		n /= bit[i];
	}
}

int solve (int ed) {

	int c[16], suf[16];
	memset(c, 0, sizeof(c));
	memset(dp, 0, sizeof(dp));

	suf[N] = 1;
	for (int i = N-1; i >= 0; i--)
		suf[i] = suf[i+1] * bit[i+1];

	for (int i = 0; i <= N; i++) {
		c[i]++;
		dp[idx(c)][i] = bit[i]-1;
		c[i]--;
	}

	for (int s = 1; s < ed; s++) {
		ridx(s, c);
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N; j++) if (ok[i][j]) {
				int k = bit[j] - c[j] - 1;
				if (k == 0) continue;
				int v = s + suf[j];
				dp[v][j] = (dp[v][j] + dp[s][i] * k) % mod;
			}
		}
	}

	int ret = 0;
	for (int i = 0; i <= N; i++)
		ret = (ret + dp[ed][i]) % mod;
	return ret;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }

int main () {
	for (int i = 0; i < 14; i++) {
		for (int j = i; j < 14; j++)
			ok[i][j] = ok[j][i] = (gcd(f[i], f[j]) == 1);
	}

	int cas, m, c[16];
	scanf("%d", &cas);
	while (cas--) {

		N = 0;
		memset(c, 0, sizeof(c));
		scanf("%d%d", &m, &mod);
		for (int i = 1; i <= m; i++) {
			N = max(N, be[i]);
			c[be[i]]++;
		}
		for (int i = 0; i <= N; i++)
			bit[i] = c[i] + 1;
		printf("%d\n", solve(idx(c)));
	}
	return 0;
}
