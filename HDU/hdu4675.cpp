#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 300000;
const int mod = 1e9 + 7;

int fac[maxn + 5], inv[maxn + 5];
vector<int> P[maxn + 5];

int pow_mod(int x, int n) {
	if (n < 0) return 0;
	int ret = 1;
	while (n) {
		if (n&1) ret = 1LL * ret * x % mod;
		x = 1LL * x * x % mod;
		n >>= 1;
	}
	return ret;
}

void presolve (int n) {
	for (int i = 0; i <= n; i++) P[i].clear();

	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i)
			P[j].push_back(i);
	}

	fac[0] = inv[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = 1LL * fac[i-1] * i % mod;
	inv[n] = pow_mod(fac[n], mod-2);
	for (int i = n-1; i; i--) inv[i] = 1LL * inv[i+1] * (i+1) % mod;
}

int C(int n, int k) {
	if (n < 0 || k < 0 || k > n) return 0;
	return 1LL * fac[n] * inv[k] % mod * inv[n-k] % mod;
}

int N, M, K, cnt[maxn + 5], ans[maxn + 5];

void init () {
	int x;
	memset(cnt, 0, sizeof(cnt));

	for (int i = 1; i <= N; i++) {
		scanf("%d", &x);
		for (int j = 0; j < P[x].size(); j++)
			cnt[P[x][j]]++;
	}
}

int main () {
	presolve(maxn);
	while (scanf("%d%d%d", &N, &M, &K) == 3) {
		init();
		for (int i = M; i; i--) {
			int k = M / i;
			ans[i] = 1LL * C(cnt[i], N-K) * pow_mod(k-1, cnt[i]-N+K) % mod * pow_mod(k, N-cnt[i]) % mod;

			for (int j = 2; j * i <= M; j++)
				ans[i] = (ans[i] - ans[j*i]) % mod;
			ans[i] = (ans[i] + mod) % mod;
		}
		for (int i = 1; i <= M; i++)
			printf("%d%c", ans[i], i == M ? '\n' : ' ');
	}
	return 0;
}
