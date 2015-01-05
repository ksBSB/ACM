#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

int M, N, a[maxn][maxn], b[maxn][maxn], c[maxn][maxn];

bool judge() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (b[i][j] == 0) {
				for (int k = 0; k < N; k++) a[k][j] = 0;
				for (int k = 0; k < M; k++) a[i][k] = 0;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (a[i][j] == 1) {
				for (int k = 0; k < N; k++) c[k][j] = 1;
				for (int k = 0; k < M; k++) c[i][k] = 1;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			if (b[i][j] != c[i][j])
				return true;
	}

	printf("YES\n");
	for (int i = 0; i < N; i++) {
		printf("%d", a[i][0]);
		for (int j = 1; j < M; j++)
			printf(" %d", a[i][j]);
		printf("\n");
	}
	return false;
}

int main () {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			a[i][j] = 1;
			scanf("%d", &b[i][j]);
		}
	}

	if (judge())
		printf("NO\n");
	return 0;
}
