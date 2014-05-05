#include <stdio.h>
#include <string.h>

const int N = 105;
const int d[5][2] = { {0, 0}, {1, -1}, {1, 0}, {1, 1}, {2, 0} };
int n, v[N][N];
char g[N][N];

bool insert(int x, int y) {
	for (int i = 0; i < 5; i++) {
		int p = x + d[i][0], q = y + d[i][1];
		if (p < 0 || p >= n || q < 0 || q >= n) return false;
		if (v[p][q] || g[p][q] != '#') return false;
	}
	return true;
}

void clear (int x, int y, int val) {
	for (int i = 0; i < 5; i++)
		v[x + d[i][0]][y + d[i][1]] = val;
}

bool dfs(int x, int y) {
	if (y == n) {
		y = 0; x++;
	}
	if (x == n) return true;

	if (g[x][y] == '.' || v[x][y]) return dfs(x, y + 1);	

	if (!insert(x, y)) return false;

	clear(x, y, 1);
	bool flag = dfs(x, y + 1);
	clear(x, y, 0);

	return flag;
}

int main () {
	memset(v, 0, sizeof(v));
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%s", g[i]);
	printf("%s\n", dfs(0, 0) ? "YES" : "NO");
	return 0;
}
