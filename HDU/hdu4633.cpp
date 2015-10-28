#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int mod = 10007;

int inv24, P[100];

int pow_mod(int x, int n, int mod) {
	int ret = 1;
	while (n) {
		if (n&1) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

int solve () {
	return (P[74] + 3 * (P[20] * 2 + P[38]) % mod + 6 * P[38] % mod + 8 * P[26] % mod) % mod * inv24 % mod;
}

int main () {
	inv24 = pow_mod(24, mod-2, mod);

	int cas, k;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &k);
		P[0] = 1;
		for (int i = 1; i <= 74; i++) P[i] = P[i-1] * k % mod;
		printf("Case %d: %d\n", kcas, solve());
	}
	return 0;
}
