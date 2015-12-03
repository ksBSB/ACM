#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;

int f[maxn];

void init () {
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

int solve(int n, int k) {
	int ret = f[n], sig = -1;
	for (int i = 1; ; i++) {
		int v1 = k * i * (3 * i - 1) / 2;
		int v2 = k * i * (3 * i + 1) / 2;
		if (v1 > n && v2 > n) break;
		if (v1 <= n) ret = (ret + sig * f[n-v1]) % mod;
		if (v2 <= n) ret = (ret + sig * f[n-v2]) % mod;
		sig *= -1;
	}
	return (ret + mod) % mod;
}

int main () {
	init();
	int cas, n, k;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &n, &k);
		printf("%d\n", solve(n, k));
	}
	return 0;
}
