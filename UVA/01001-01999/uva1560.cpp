#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10;
const int R = 5;
const int C = 6;

int arr[maxn][maxn], v[maxn][maxn], p[maxn][maxn];

bool judge (int s) {
	memset(p, 0, sizeof(p));
	memset(v, 0, sizeof(v));

	for (int i = 0; i < C; i++) {
		if (s&(1<<i)) {
			p[1][i+1] = 1;

			for (int j = 0; j <= 2; j++)
				v[1][i+j] ^= 1;
			v[2][i+1] ^= 1;
		}
	}

	for (int i = 2; i <= R; i++) {
		for (int j = 1; j <= C; j++)
			if (v[i-1][j]^arr[i-1][j]) {
				p[i][j] = 1;

				for (int k = -1; k <= 1; k++)
					v[i][j+k] ^= 1;
				v[i+1][j] ^= 1;
			}
	}

	for (int i = 1; i <= C; i++)
		if (v[R][i]^arr[R][i])
			return false;

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j < C; j++)
			printf("%d ", p[i][j]);
		printf("%d\n", p[i][C]);
	}
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {

		for (int i = 1; i <= R; i++)
			for (int j = 1; j <= C; j++)
				scanf("%d", &arr[i][j]);

		printf("PUZZLE #%d\n", kcas);
		for (int s = 0; s < (1<<C); s++)
			if (judge(s))
				break;
	}
	return 0;
}
