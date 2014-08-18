#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int dir[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const int maxn = 30;
const int R = 5;
const int C = 6;
typedef int Mat[maxn+5][maxn+5];

Mat A;
int v[R+5][C+5];

void init () {
	memset(A, 0, sizeof(A));
	memset(v, 0, sizeof(v));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int x = i * C + j;
			scanf("%d", &A[x][maxn]);
			for (int k = 0; k < 5; k++) {
				int p = i + dir[k][0];
				int q = j + dir[k][1];
				if (p < 0 || p >= R || q < 0 || q >= C)
					continue;
				A[x][p*C+q] = 1;
			}
		}
	}
}

void gauss_elimination (Mat a, int n) {

	for (int i = 0; i < n; i++) {

		int r = i;
		while (A[r][i] == 0)
			r++;

		if (r != i) {
			for (int j = 0; j <= n; j++)
				swap(A[i][j], A[r][j]);
		}

		for (int j = i + 1; j < n; j++) {
			if (A[j][i]) {
				for (int k = 0; k <= n; k++)
					A[j][k] ^= A[i][k];
			}
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++)
			A[i][n] ^= (A[j][n] * A[i][j]);
		if (A[i][n])
			v[i/C][i%C] = 1;
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		gauss_elimination(A, maxn);
		printf("PUZZLE #%d\n", kcas);
		for (int i = 0; i < R; i++) {
			printf("%d", v[i][0]);
			for (int j = 1; j < C; j++)
				printf(" %d", v[i][j]);
			printf("\n");
		}
	}
	return 0;
}
