#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 205;

int n, ans, v[N][N];

void init() {
	char str[N * 2];
	ans = 0;
	memset(v, -1, sizeof(v));

	for (int i = 0; i < n; i++) {
		gets(str);
		int len = strlen(str);
		for (int j = 0; j < len; j++) {
			if (str[j] == '-') v[i][j] = 0;
		}
	}
}

void dfs(int x, int y, int d, int dir) {
	if (x < 0 || x > n) {
		ans = max(ans, d);
		return;
	}

	for (int i = y - d; i <= y + d; i++) {
		if (v[x][i] == -1) {
			ans = max(ans, d);
			return ;
		}
	}

	dfs(x + dir, y, d + 1, dir);
}

void solve() {
	for (int i = 0; i < n; i++) {
		int t = (n - i) * 2 + i - 1;
		for (int j = i; j < t; j++) if (v[i][j] == 0) {
			if ((j + i) % 2)
				dfs(i, j, 0, 1);
			else 
				dfs(i, j, 0, -1);
		}
	}
}

int main() {
	int cas = 1;
	while(scanf("%d%*c", &n) == 1 && n) {
		init();
		solve();
		printf("Triangle #%d\n", cas++);
		printf("The largest triangle area is %d.\n\n", ans * ans);
	}
	return 0;
}
