#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 805;

int N, A[maxn][maxn], B[maxn][maxn];
int C[maxn][maxn];
int a[maxn][maxn], ca[maxn];
int b[maxn][maxn], cb[maxn];

void init () {
	int x;
	memset(ca, 0, sizeof(ca));
	memset(cb, 0, sizeof(cb));
	memset(C, 0, sizeof(C));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &x);
			A[i][j] = x % 3;
			if (A[i][j])
				a[j][ca[j]++] = i;
		}
	}

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			scanf("%d", &x);
			B[i][j] = x % 3;
			if (B[i][j])
				b[i][cb[i]++] = j;
		}

	for (int k = 1; k <= N; k++) {
		for (int i = 0; i < ca[k]; i++) {
			for (int j = 0; j < cb[k]; j++)
				C[a[k][i]][b[k][j]] = (C[a[k][i]][b[k][j]] + A[a[k][i]][k] * B[k][b[k][j]]) % 3;
		}
	}
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j < N; j++)
				printf("%d ", C[i][j]);
			printf("%d\n", C[i][N]);
		}
	}
	return 0;
}
