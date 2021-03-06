#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 105;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m, g[N][N];

void draw(int x, int y, int k, int sign) {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++)
			g[x+i][y+j] = sign;
	}
}

int get(int x, int y) {
	int v[15];
	memset(v, 0, sizeof(v));

	for (int i = 0; i < 4; i++) {
		int p = x + dir[i][0];
		int q = y + dir[i][1];
		v[g[p][q]] = 1;
	}

	for (int i = 1; i <= 10; i++)
		if (v[i] == 0)
			return i;
	return 0;
}

void solve (int x, int y) {

	if (y > m) {
		y = 1;
		x++;
	}

	if (x > n)
		return ;

	if (g[x][y]) {
		solve(x, y+1);
		return;
	}

	int sign = get(x, y);

	int p = 1;
	while (true) {
		if (p + x > n || p + y > m)
			break;

		if (g[x][y+p])
			break;
		int tmp = get(x, y+p);

		if (tmp != sign)
			break;
		p++;
	}

	draw(x, y, p, sign);
	solve(x, y + p);
}

int main () {
	scanf("%d%d", &n, &m);
	memset(g, 0, sizeof(g));
	solve (1, 1);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			printf("%c", 'A'+g[i][j]-1);
		printf("\n");
	}
	return 0;
}
