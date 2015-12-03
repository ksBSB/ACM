#include <cstdio>
#include <cstring>
#include <algorithm>

/* 
 * 五边形数：f(n) = sum( (-1)^(k+1) [ P(n-k(3k-1)/2) + P(n-k(3k+1)/2)] )
 */

using namespace std;
typedef long long ll;
const int maxn = 1e5;
const int mod = 1e9 + 7;

ll f[maxn + 5];

void presolve() {
	memset(f, 0, sizeof(f));
	f[0] = 1;
	for (int i = 1; i <= maxn; i++) {
		int bit = 1;
		for (int j = 1; j <= i; j++) {
			int v1 = i - j * (3 * j - 1) / 2;
			int v2 = i - j * (3 * j + 1) / 2;

			if (v1 < 0 && v2 < 0) break;

			if (v1 >= 0)
				f[i] = (f[i] + bit * f[v1]) % mod;
			if (v2 >= 0)
				f[i] = (f[i] + bit * f[v2]) % mod;
			bit *= -1;
		}
		f[i] = (f[i] + mod) % mod;
	}
}

int main () {
	presolve();

	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		printf("%lld\n", f[n]);
	}
	return 0;
}
