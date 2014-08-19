#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxc = 20;
const int maxn = 40;

typedef long long ll;
typedef double Mat[maxn][maxn];

ll A, M, B, N, C[maxc+5][maxc+5];
Mat G;

void getc (int n) {
	for (int i = 0; i <= n; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
}

void init () {
	memset(G, 0, sizeof(G));
	int n = N * M;

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= i; j++) {
			int l = j, r = i - j;
			double tmp = C[i][l] * pow(A * 1.0, l / M) * pow(B * 1.0, r / N);
			l %= M; r %= N;
			G[l*N+r][i] += tmp;
		}
	}
	G[n][n] = 1;
	G[n][n+1] = 1;
}

void gauss_elimin (int n) {
	/*
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			printf("%lf ", G[i][j]);
		printf("\n");
	}
	*/

	for (int i = 0; i < n; i++) {
		int r = i;

		for (int j = i + 1; j < n; j++) 
			if (fabs(G[j][i]) > fabs(G[r][i]))
				r = j;

		if (r != i) {
			for (int j = 0; j <= n; j++)
				swap(G[r][j], G[i][j]);
		}

		if (fabs(G[i][i]) < 1e-9)
			continue;

		for (int k = i + 1; k < n; k++) {
			double f = G[k][i] / G[i][i];
			for (int j = 0; j <= n; j++)
				G[k][j] -= G[i][j] * f;
		}
	}

	for (int i = n-1; i >= 0; i--) {
		for (int j = i+1; j < n; j++)
			G[i][n] -= G[j][j] * G[i][j];
		G[i][i] = G[i][n] / G[i][i];
		if (fabs(G[i][i]) < 1e-9)
			G[i][i] = 0;
	}

	printf("%.0f", G[n-1][n-1]);
	for (int i = n-2; i >= 0; i--)
		printf(" %.0f", G[i][i]);
	printf("\n");
}

int main () {
	getc(maxc);

	while (scanf("%lld%lld%lld%lld", &A, &M, &B, &N) == 4 && A + M + B + N) {
		init();
		gauss_elimin (N * M + 1);
	}
	return 0;
}
