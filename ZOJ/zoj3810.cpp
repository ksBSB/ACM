#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;
const char s[10][10] = {"BBBBBB", "GGRGRR", "GRRGRB", "GRGGRB", "GRGRRB", "GRGBBB"};
const char c[5] = "BGRY";

int g[maxn][maxn];

void solve (int n) {
	memset(g, 0, sizeof(g));

	for (int i = 0; i < n; i++)
		g[0][i] = 3;

	int k = (n - 1) / 2, col = 1;
	for (int i = 0; i < k; i++) {
		for (int j = 1; j <= i+1; j++)
			g[j][i+1] = col;
		for (int j = i+1; j < n; j++)
			g[j][i] = col;
		col = 3 - col;
	}

	for (int i = k; i < n; i++) {
		for (int j = 2; j <= i+2; j++)
			g[j][i+2] = col;
		g[i+2][i+1] = col;
		for (int j = i+2; j < n; j++)
			g[j][i] = col;
		col = 3 - col;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			printf("%c", c[g[i][j]]);
		printf("\n");
	}
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		if (n == 1)
			printf("B\n");
		else if (n == 6) {
			for (int i = 0; i < 6; i++)
				printf("%s\n", s[i]);
		} else if (n >= 5) {
			solve(n);
		} else
			printf("No solution!\n");
	}
	return 0;
}
