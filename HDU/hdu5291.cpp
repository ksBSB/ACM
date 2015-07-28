#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 80000;
const int maxm = 205;
const int mod = 1e9+7;
#define coe(x) ((x)/2+1)

int N, M, A[maxm], dp[2][maxn + 5];

int query(int x, int now) {
	if (x < 0 || x > 2*M)
		return 0;
	return dp[now][x];
}

int solve () {
	int now = 0, pre = 1;
	memset(dp[now], 0, sizeof(dp[now]));

	dp[now][M] = 1;
	for (int i = 0; i < N; i++) {
		now = pre;
		pre = pre^1;
		int sumL = 0, sumR = 0, addL = 0, addR = 0;

		for (int k = -A[i]; k <= A[i]; k++) {
			int tmp = query(k, pre);
			dp[now][0] = 0;
			dp[now][0] = (dp[now][0] + 1LL * tmp * coe(A[i]-(k < 0 ? -k : k)) % mod) % mod;
			if (k <= 0) {
				sumL = (sumL + tmp) % mod;
				if ((k&1) == 0)
					addL = (addL + tmp) % mod;
			}

			if (k >= 0) {
				sumR = (sumR + tmp) % mod;
				if ((k&1) == 0)
					addR = (addR + tmp) % mod;
			}
		}

		if (A[i]&1) {
			addR = (sumR - addR + mod) % mod;
			addL = (sumL - addL + mod) % mod;
		}

		for (int k = 1; k <= M*2; k++) {
			sumR = (sumR + query(A[i] + k, pre)) % mod;
			addR = (sumR + mod - addR) % mod;
			sumR = (sumR + mod - query(k-1, pre)) % mod;

			dp[now][k] = ((dp[now][k-1] + addR - addL) % mod + mod) % mod;

			sumL = (sumL + query(k, pre)) % mod;
			addL = (sumL + mod - addL) % mod;
			sumL = (sumL + mod - query(k - A[i] - 1, pre)) % mod;
		}
	}
	return dp[now][M];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		M = 0;
		for (int i = 0; i < N; i++) {
			scanf("%d", &A[i]);
			M += A[i];
		}
		printf("%d\n", solve());
	}
	return 0;
}
