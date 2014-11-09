#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1000;
typedef long long ll;
typedef int Mat[maxn+5][maxn+5];

int gauss (Mat A, int m, int n) {
	int i = 0, j = 0, k, r, u;
	while (i < m && j < n) {
		r = i;
		for (k = i; k < m; k++) {
			if (A[k][j]) {
				r = k;
				break;
			}
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
	return n - i;
}

int N;
Mat a;

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		ll x;
		scanf("%d", &N);
		memset(a, 0, sizeof(a));
		for (int i = 0; i < N; i++) {
			scanf("%I64d", &x);
			for (int j = 0; j < 45; j++)
				a[j][i] = (x>>j)&1;
		}
		int ans = gauss(a, 45, N);
		printf("%s\n", ans ? "Yes" : "No");
	}
	return 0;
}
