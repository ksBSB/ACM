#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll pow_mod (ll x, int n, int mod) {
	ll ret = 1;
	while (n) {
		if (n&1) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

int main () {
	int cas = 1, C, k1, b1, k2;
	while (scanf("%d%d%d%d", &C, &k1, &b1, &k2) == 4) {
		printf("Case #%d:\n", cas++);

		int cnt = 0;
		for (int a = 1; a < C; a++) {
			int b = C - pow_mod(a, k1+b1, C);
			if ((pow_mod(a, k1, C) * (C - b) % C + pow_mod(b, k2, C) * b % C) % C == 0) {
				printf("%d %d\n", a, b);
				cnt++;
			}
		}

		if (cnt == 0)
			printf("-1\n");
	}
	return 0;
}
