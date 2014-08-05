#include <cstdio>
#include <cstring>
#include <bitset>
#include <algorithm>

using namespace std;
const int maxn = 805;

int N, C[maxn][maxn];
bitset<maxn> x[maxn][2], y[maxn][2];

void init () {
	int u;
	memset(C, 0, sizeof(C));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 2; j++) {
			x[i][j].reset();
			y[i][j].reset();
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &u);
			u %= 3;
			if (u)
				x[i][u-1].set(j, 1);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &u);
			u %= 3;
			if (u)
				y[j][u-1].set(i, 1);
		}
	}
}

int solve (int u, int v) {
	int ret = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			bitset<maxn> k = x[u][i]&y[v][j];

			ret = (ret + (i+1)*(j+1)*k.count()) % 3;
		}
	}
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();
		for (int i = 0; i < N; i++) {
			printf("%d", solve(i, 0));
			for (int j = 1; j < N; j++)
				printf(" %d", solve(i, j));
			printf("\n");
		}
	}
	return 0;
}
