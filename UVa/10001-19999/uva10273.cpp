#include <stdio.h>
#include <string.h>

const int N = 1005;
const int M = 15;
const int INF = 1 << 30;
const int tmp = 2520;

int n, s[N], g[N][M], vis[N];

void init() {

	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &s[i]);
		for (int j = 0; j < s[i]; j++)
			scanf("%d", &g[i][j]);
	}
}

bool find(int d, int& id) {

	int Min = INF;
	bool flag = false;

	for (int i = 0; i < n; i++) {

		if (vis[i]) continue;

		int c = d % s[i];
		if (Min > g[i][c]) {
			id = i;
			Min = g[i][c];
			flag = true;
		} else if (Min == g[i][c])
			flag = false;

	}

	return flag;
}

void solve() {
	
	int id, del = -1, cnt = 0;
	memset(vis, 0, sizeof(vis));

	for (int i = 0; i - del <= tmp; i++) {
		if (find(i, id)) {
			del = i;
			vis[id] = 1;
			cnt++;
		}
	}
	printf("%d %d\n", n - cnt, del + 1);
}

int main () {
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		init();
		solve();
	}
	return 0;
}
