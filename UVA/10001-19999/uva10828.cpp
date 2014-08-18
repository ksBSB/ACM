#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;
const double eps = 1e-9;

double A[maxn][maxn];
int N, Q, d[maxn], inf[maxn];
vector<int> g[maxn];

void init () {
	memset(d, 0, sizeof(d));
	memset(inf, 0, sizeof(inf));
	for (int i = 0; i < maxn; i++)
		g[i].clear();

	int u, v;
	while (scanf("%d%d", &u, &v) == 2 && u + v) {
		u--; v--;
		d[u]++;
		g[v].push_back(u);
	}

	memset(A, 0, sizeof(A));
	for (int i = 0; i < N; i++) {
		A[i][i] = 1;

		for (int j = 0; j < g[i].size(); j++)
			A[i][g[i][j]] -= 1.0 / d[g[i][j]];

		if (i == 0)
			A[i][N] = 1;
	}
}

void gauss_jordan (double a[maxn][maxn], int n) {
	for (int i = 0; i < n; i++) {
		int r = i, p;
		for (p = i + 1; p < n; p++)
			if (fabs(a[p][i]) > fabs(a[r][i]))
				r = p;

		if (r != i) {
			for (int j = 0; j <= n; j++)
				swap (A[r][j], A[i][j]);
		}

		if (fabs(a[r][i]) < eps)
			continue;

		for (int k = 0; k < n; k++) {
			if (k != i) {
				for (int j = n; j >= i; j--)
					a[k][j] -= a[k][i] / a[i][i] * a[i][j];
			}
		}
	}
}

int main () {
	int cas = 1, x;
	while (scanf("%d", &N) == 1 && N) {
		init();
		gauss_jordan(A, N);

		for (int i = N - 1; i >= 0; i--) {
			if (fabs(A[i][i]) < eps && fabs(A[i][N]) > eps)
				inf[i] = 1;

			for (int j = i + 1; j < N; j++)
				if (fabs(A[i][j]) > eps && inf[j])
					inf[i] = 1;
		}

		scanf("%d", &Q);
		printf("Case #%d:\n", cas++);
		while (Q--) {
			scanf("%d", &x);
			x--;

			if (inf[x])
				printf("infinity\n");
			else
				printf("%.3lf\n", fabs(A[x][x]) < eps ? 0.0 : A[x][N] / A[x][x]);
		}
	}
	return 0;
}
