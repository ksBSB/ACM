#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 305;
const int maxd = 7;
const char day[maxd][maxd] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
typedef long long ll;
typedef ll Mat[maxn][maxn];

int N, M;
Mat A;

int solve (char *s, char *e) {
	int p = 0;
	while (strcmp(s, day[p])) p++;
	int q = p;
	while (strcmp(e, day[q])) q = (q + 1) % maxd;

	return (q - p + 8) % maxd;
}

void init () {
	int n, x;
	char s[maxn], e[maxn];
	memset(A, 0, sizeof(A));

	for (int i = 0; i < M; i++) {
		scanf("%d%s%s", &n, s, e);

		for (int j = 0; j < n; j++) {
			scanf("%d", &x);
			A[i][x-1] = (A[i][x-1] + 1) % maxd;
		}

		A[i][N] = solve(s, e);
	}
}

ll pow_mod(ll x, int n, ll mod) {
	ll ret = 1;

	while (n) {
		if (n&1)
			ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

ll inv (ll k) {
	return pow_mod(k, maxd-2, maxd);
}

int gauss_elimin (int n, int m) {

	int i = 0, j = 0;

	while (i < m && j < n) {
		int r = i;
		for (int k = i; k < m; k++) {
			if (A[k][j]) {
				r = k;
				break;
			}
		}

		if (r != i) {
			for (int k = 0; k <= n; k++)
				swap(A[i][k], A[r][k]);
		}

		if (A[i][j] == 0) {
			j++;
			continue;
		}

		for (int k = 0; k < m; k++) {
			if (A[k][j] == 0 || i == k)
				continue;

			ll f = A[k][j] * inv(A[i][j]) % maxd;

			for (int t = j; t <= n; t++)
				A[k][t] = ((A[k][t] - f * A[i][t]) % maxd + maxd) % maxd;
		}
		i++;
	}

	for (int k = i; k < m; k++)
		if (A[k][n])
			return 0;

	if (i < n)
		return 2;


	for (int k = 0; k < n; k++) {
		A[k][n] = A[k][n] * inv(A[k][k]) % maxd;
		if (A[k][n] < 3)
			A[k][n] += maxd;
		printf("%lld%c", A[k][n], k == n-1 ? '\n' : ' ');
	}

	return 1;
}

int main () {
	while (~scanf("%d%d", &N, &M) && N) {
		init();
		int type = gauss_elimin(N, M);
		if (type == 0)
			printf("Inconsistent data.\n");
		else if (type == 2)
			printf("Multiple solutions.\n");
	}
	return 0;
}
