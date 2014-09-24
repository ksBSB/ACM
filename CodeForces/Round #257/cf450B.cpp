#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 1e9+7;

ll s[2][2] = {1, 0, 0, 1};

void mat_mod (ll a[2][2], ll b[2][2]) {
	ll c[2][2];
	memset(c, 0, sizeof(c));
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				c[i][j] = ((c[i][j] + a[i][k] * b[k][j]) % mod + mod) % mod;
	}
	memcpy(a, c, sizeof(c));
}

void mat_pow(int n) {
	ll x[2][2] = {0, 1, -1, 1};
	while (n) {
		if (n&1)
			mat_mod(s, x);
		mat_mod(x, x);
		n >>= 1;
	}
}

int main () {
	int x, y, n;
	scanf("%d%d%d", &x, &y, &n);
	if (n == 1)
		printf("%lld\n", (x % mod + mod) % mod);
	else {
		mat_pow(n-2);
		printf("%lld\n", ((x * s[1][0] % mod + y * s[1][1] % mod) % mod + mod) % mod);
	}
	return 0;
}
