#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int mod = 1e9 + 7;

int N, K;

long long pow_mod(long long x, int n) {
	if (n < 0) return 0;
	long long ret = 1;
	while (n) {
		if (n&1) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &K);
		if (N == K) {
			printf("1\n");
			continue;
		}

		int ans = pow_mod(2, N-K);
		ans = (ans + pow_mod(2, N-K-2) * (N-K-1)) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
