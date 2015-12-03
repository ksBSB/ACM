#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 50005;

int N, K, A[maxn<<1], C[maxn<<1];
int dp[2][205], T[maxn<<2], P[maxn<<1];

int get_bit(int n) {
	if (n == 1) return 1;
	int ret = 0;
	while (n) {
		ret++;
		n /= 10;
	}
	return ret;
}

void init () {
	P[0] = C[0] = 0;
	T[0] = 1;
	for (int i = 1; i <= (N<<2); i++)
		T[i] = T[i-1] * 10 % K;

	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
		int tmp = get_bit(A[i]);
		C[i] = C[i-1] + tmp;
		P[i] = (P[i-1] * T[tmp] + A[i]) % K;
	}

	for (int i = 1; i <= N; i++) {
		int tmp = get_bit(A[i]);
		C[i+N] = C[i+N-1] + tmp;
		P[i+N] = (P[i+N-1] * T[tmp] + A[i]) % K;
	}
}

ll solve () {
	ll ret = 0;
	int nw = 0, nx = 1;
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= N; i++) {
		nw = nx; nx = 1-nw;
		memset(dp[nx], 0, sizeof(dp[nx]));
		for (int j = 0; j < K; j++) {
			int t = (j * T[C[i]-C[i-1]] + A[i]) % K;
			dp[nx][t] += dp[nw][j];
		}
		dp[nx][A[i] % K]++;
		ret += dp[nx][0];
	}

	for (int i = 1; i <= N; i++) {
		nw = nx; nx = 1-nw;
		memset(dp[nx], 0, sizeof(dp[nx]));
		for (int j = 0; j < K; j++) {
			int t = (j * T[C[i+N]-C[i+N-1]] + A[i]) % K;
			dp[nx][t] += dp[nw][j];
		}
		int x = (P[i+N] - P[i-1] * T[C[i+N] - C[i-1]] % K + K) % K;
		dp[nx][x]--;
		ret += dp[nx][0];
	}
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &K) == 2) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
