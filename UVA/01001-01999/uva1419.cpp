#include <stdio.h>
#include <string.h>

const int N = 105;

int r, c, v[N];
char g[N][N];

bool judge(int x, int y, int l, int w) {
	if (w - x < 2 || l - y < 2) return false;
	for (int i = y; i < l; i++) if (g[w-1][i] != g[x][y]) return false;
	for (int i = x; i < w; i++) if (g[i][l-1] != g[x][y]) return false;
	for (int i = x + 1; i < w - 1; i++) {
		for (int j = y + 1; j < l - 1; j++) if (g[i][j] != '.') return false;
	}
	return true;;
}

void solve() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) if (g[i][j] != '.' && v[g[i][j] - 'A'] == 0) {
			v[g[i][j]-'A'] = 1;
			int l = j, w = i;
			while (g[i][l] == g[i][j]) l++;
			while (g[w][j] == g[i][j]) w++;
			if (judge(i, j, l, w)) v[g[i][j]-'A'] = 2;
		}
	}
}

int main() {
	while (scanf("%d%d%*c", &r, &c) == 2 && r + c) {
		memset(v, 0, sizeof(v));
		for (int i = 0; i < r; i++) gets(g[i]);
		solve();
		for (int i = 0; i < 30; i++) if (v[i] == 2) printf("%c", 'A' + i);
		printf("\n");
	}
	return 0;
}
