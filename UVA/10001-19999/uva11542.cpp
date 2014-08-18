#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 500;
typedef long long ll;
typedef int Matrix[maxn+5][maxn+5];

int np, pri[maxn+5], vis[maxn+5];

void prime_table (int n) {
	np = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;

		pri[np++] = i;
		for (int j = i + i; j <= n; j += i)
			vis[j] = 1;
	}
}

Matrix A;

int solve (Matrix a, int m, int n) {
	int i = 0, j = 0, k, r, u;
	while (i < m && j < n) {
		r = i;
		for (k = i; k < m; k++)
			if (A[k][j]) {
				r = k;
				break;
			}

		if (A[r][j]) {
			if (r != i) {
				for (k = 0; k <= n; k++)
					swap(A[r][k], A[i][k]);
			}

			for (u = i + 1; u < m; u++) {
				if (A[u][j])
					for (k = i; k <= n; k++)
						A[u][k] ^= A[i][k];
			}
			i++;
		}
		j++;
	}	
	return i;
}

int main () {
	prime_table(maxn);

	int cas;
	scanf("%d", &cas);

	while (cas--) {
		ll x;
		int n, maxp = 0;
		scanf("%d", &n);
		memset(A, 0, sizeof(A));

		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			for (int j = 0; j < np; j++) {
				while (x % pri[j] == 0) {
					maxp = max(maxp, j);
					x /= pri[j];
					A[j][i] ^= 1;
				}
			}
		}

		int ret = solve(A, maxp+1, n);
		printf("%lld\n", (1LL<<(n-ret))-1);
	}
	return 0;
}
