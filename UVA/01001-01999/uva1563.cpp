#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 80;
typedef int Mat[maxn][maxn];

int p, n;
char s[maxn];
Mat A;

inline int cat (char ch) {
	if (ch == '*')
		return 0;
	return ch - 'a' + 1;
}

void solve () {
	n = strlen(s);
	memset(A, 0, sizeof(A));
	for (int i = 0; i < n; i++) {
		int k = 1;
		for (int j = 0; j < n; j++) {
			A[i][j] = k;
			k = k * (i+1) % p;
		}
		A[i][n] = cat(s[i]) % p;
	}
}

int pow_mod(int x, int k, int mod) {
	int ret = 1;
	while (k) {
		if (k&1)
			ret = ret * x % mod;
		x = x * x % mod;
		k >>= 1;
	}
	return ret;
}

int inv (int v, int mod) {
	return pow_mod(v % mod, mod-2, mod);
}


void gauss_elimin () {
	for (int i = 0; i < n; i++) {
		int r = i;

		for (int j = i+1; j < n; j++)
			if (A[r][i] < A[j][i])
				r = j;

		if (r != i) {
			for (int j = 0; j <= n; j++)
				swap(A[i][j], A[r][j]);
		}

		if (A[i][i] == 0)
			continue;

		for (int k = i + 1; k < n; k++) {
			int f = A[k][i] * inv(A[i][i], p) % p;
			for (int j = i; j <= n; j++)
				A[k][j] = ((A[k][j] - A[i][j] * f) % p + p) % p;
		}
	}

	for (int i = n-1; i >= 0; i--) {
		for (int j = i+1; j < n; j++)
			A[i][n] = ((A[i][n] - A[i][j] * A[j][n]) % p + p) % p;
		A[i][n] = A[i][n] * inv(A[i][i], p) % p;
	}

	printf("%d", A[0][n]);
	for (int i = 1; i < n; i++)
		printf(" %d", A[i][n]);
	printf("\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%s", &p, s);
		solve();
		gauss_elimin();
	}
	return 0;
}
