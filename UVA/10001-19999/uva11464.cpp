#include <stdio.h>
#include <string.h>

const int N = 20;
const int INF = 0x3f3f3f3f;
const int dir[][2] = { {0, 1}, {0, -1}, {-1, 0} };

int n, ans, v[N][N], s[N][N];

void init() {

	ans = INF;
	memset(v, 0, sizeof(v));
	memset(s, 0, sizeof(s));

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &v[i][j]);
}

int count(int x, int y) {
	int tmp = 0;

	for (int i = 0; i < 3; i++) {
		int p = x + dir[i][0], q = y + dir[i][1];
		if (p < 0 || p >= n) continue;
		if (q < 0 || q >= n) continue;

		tmp += s[p][q];
	}
	return tmp;
}

void solve() {
	int tmp = 0;

	for (int i = 0; i < n; i++)
		if (v[0][i] != s[0][i]) tmp++;

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int k = count(i - 1, j);

			if (k % 2 == 1) {
				s[i][j] = 1;
				if (v[i][j] == 0)	tmp++;
			} else {
				s[i][j] = 0;
				if (v[i][j]) return;
			}
		}
	}

	if (tmp < ans)	ans = tmp;

}

void dfs(int c) {
	if (c == n) {
		solve();
		return;
	}

	s[0][c] = 1;
	dfs(c + 1);

	if ( v[0][c] == 0) {
		s[0][c] = 0;
		dfs(c + 1);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();

		dfs(0);

		printf("Case %d: ", i);
		if (ans == INF) printf("-1\n");
		else printf("%d\n", ans);
	}
	return 0;
}
