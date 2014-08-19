#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int MOD = 6;
typedef int Mat[maxn][maxn];

int N, K;
Mat A, B, X, Y, tmp;

void put (Mat x, int r, int c) {
	for (int i = 0; i < K; i++) {
		for (int j = 0;  j < K; j++)
			printf("%d ", x[i][j]);
		printf("\n");
	}
}

void mul_mat (Mat ret, Mat a, Mat b, int r, int t, int c) {
	memset(tmp, 0, sizeof(tmp));

	for (int k = 0; k < t; k++) {
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % MOD;
	}
	memcpy(ret, tmp, sizeof(tmp));
}

void pow_mat (Mat ret, Mat x, int n) {
	memset(Y, 0, sizeof(Y));
	for (int i = 0; i < K; i++)
		Y[i][i] = 1;

	while (n) {
		if (n&1)
			mul_mat(Y, Y, x, K, K, K);
		mul_mat(x, x, x, K, K, K);
		n >>= 1;
	}
	memcpy(ret, Y, sizeof(Y));
}


void init () {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < K; j++)
			scanf("%d", &A[i][j]);


	for (int i = 0; i < K; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &B[i][j]);
}

int main () {
	while (scanf("%d%d", &N, &K) == 2 && N + K) {
		init();

		mul_mat(X, B, A, K, N, K);


		pow_mat(X, X, N*N-1);

		mul_mat(X, A, X, N, K, K);
		mul_mat(X, X, B, N, K, N);

		int ans = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				ans += X[i][j];
		printf("%d\n", ans);
	}
	return 0;
}
