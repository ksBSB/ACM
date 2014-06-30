#include <stdio.h>
#include <string.h>

const int N = 10;

const int d[4][2] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
const int dir[3][3][2] = { { {0, 1}, {0, 0} }, { {1, 0}, {0, 0} }, { {0, 0} } };
const int cnt[3] = {2, 2, 1};

int r, v[N][N], tmp;
const int c = 4;

bool isInsert(int k, int x, int y) {
	for (int i = 0; i < cnt[k]; i++) {
		int p = x + dir[k][i][0], q = y + dir[k][i][1];
		if (p <= 0 || p > r) return false;
		if (q <= 0 || q > c) return false;
		if (v[p][q]) return false;
	}
	return true;
}

void clear(int k, int x, int y, int t) {
	for (int i = 0; i < cnt[k]; i++) {
		int p = x + dir[k][i][0], q = y + dir[k][i][1];
		v[p][q] = t;
	}
}

void dfs(int x, int y) {
	if (y > c)	x = x + 1, y = 1;

	if (x == r + 1) {
		tmp++; 
		return;
	}

	if (v[x][y]) dfs(x, y + 1);

	for (int i = 0; i < 3; i++) {
		if (isInsert(i, x, y)) {
			clear(i, x, y, 1);
			dfs(x, y + 1);
			clear(i, x, y, 0);
		}
	}
}

int find(int x, int y) {
	memset(v, 0, sizeof(v));
	for (int i = 0; i < 4; i++)
		v[x + d[i][0]][y + d[i][1]] = 1;
	tmp = 0;
	dfs(1,  1); 
	return tmp;
}

int solve() {

	int ans = 0;
	for (int i = 1; i < r; i++) {
		for (int j = 1; j < c; j++) {
			ans += find(i, j);
		}
	}
	return ans;
}

int main () {
	int t[10];
	for (r = 1; r <= 4; r++) {
		t[r] = solve();
	}

	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		printf("%d\n", t[n]);
	}
	return 0;
}
