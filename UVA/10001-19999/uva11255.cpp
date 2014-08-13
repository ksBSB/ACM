#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 40;

int N, col[3], u[3];
ll c[maxn+5][maxn+5];

void init () {
	for (int i = 0; i <= maxn; i++) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; j++)
			c[i][j] = c[i-1][j-1] + c[i-1][j];
	}
}

int gcd (int a, int b) {
	return b == 0 ? a : gcd (b, a % b);
}

ll solve (int k) {
	int n = 0;
	ll ret = 1;

	for (int i = 0; i < 3; i++) {
		if (u[i] % k)
			return 0;
		u[i] /= k;
		n += u[i];
	}

	for (int i = 0; i < 3; i++) {
		ret *= c[n][u[i]];
		n -= u[i];
	}
	return ret;
}

ll polya () {
	ll ret = 0;

	for (int i = 0; i < N; i++) {
		memcpy(u, col, sizeof(col));
		ret += solve(N/gcd(i, N));
	}

	if (N&1) {

		for (int i = 0; i < 3; i++) {
			if (col[i]) {
				memcpy(u, col, sizeof(col));
				u[i]--;
				ret += N * solve(2);
			}
		}
	} else {

		memcpy(u, col, sizeof(col));
		ret += N/2 * solve(2);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (col[i] && col[j]) {
					memcpy(u, col, sizeof(col));
					u[i]--; u[j]--;
					ret += N/2 * solve(2);
				}
			}
		}
	}
	return ret / 2 / N;
}

int main () {
	init();

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		N = 0;
		for (int i = 0; i < 3; i++) {
			scanf("%d", &col[i]);
			N += col[i];
		}
		printf("%lld\n", polya());
	}
	return 0;
}
