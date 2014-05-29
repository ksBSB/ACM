#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 40;

int n, k;
ll b[N][N*N], w[N][N*N];

void init () {
	memset(b, 0, sizeof(b));
	memset(w, 0, sizeof(w));
	b[0][0] = w[1][0] = 1;
	for (int i = 1; i <= n; i++) {
		b[i][0] = b[i-1][0];

		int l = (i+1)/2 * 2 - 1;
		for (int j = 1; j <= l && j <= k; j++)
			b[i][j] = b[i-1][j] + (ll)(l-j+1) * b[i-1][j-1];
	}

	for (int i = 2; i <= n; i++) {
		w[i][0] = w[i-1][0];

		int l = i/2 * 2;
		for (int j = 1; j <= l && j <= k; j++)
			w[i][j] = w[i-1][j] + (ll)(l-j+1) * w[i-1][j-1];
	}
}

int main () {
	while (scanf("%d%d", &n, &k) == 2 && n + k) {
		init();

		ll ans = 0;
		for (int i = 0; i <= k; i++)
			ans = ans + b[n][i] * w[n][k-i];
		printf("%lld\n", ans);
	}
	return 0;
}
