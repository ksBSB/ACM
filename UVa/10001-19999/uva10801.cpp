#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int N = 105;
const int INF = 0x3f3f3f3f;
int n, aid, cnt, time[N], d[N];
int g[N][N];

void add(int a, int b, int s) {
	int dis = abs(b - a) * s;
	if (g[a][b] > dis)
		g[a][b] = g[b][a] = dis;
}

void init() {
	for (int i = 0; i < n; i++)
		scanf("%d", &time[i]);

	memset(d, 0x3f, sizeof(d));
	memset(g, 0x3f, sizeof(g));
	d[0] = 0;

	for (int i = 0; i < n; i++) {
		char ch = '\0';
		int num[N];
		for (int j = 0; ch != '\n'; j++) {
			scanf("%d%c", &num[j], &ch);
			for (int k = 0; k < j; k++)
				add(num[j], num[k], time[i]);
		}
	}
}

void solve() {
	int vis[N];
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < 99; i++) {
		int x, m = INF, flag = 0;
		for (int j = 0; j < 100; j++)
			if (!vis[j] && d[j] < m) { m = d[j], x = j, flag = 1; }
		if (!flag) return;
		vis[x] = 1;
		for (int j = 0; j < 100; j++) {
			if (!vis[j] && d[j] > d[x] + g[x][j] + 60)
				d[j] = d[x] + g[x][j] + 60;
		}
	}
}

int main () {
	while (scanf("%d%d", &n, &aid) == 2) {
		init();
		solve();
		if (aid == 0) printf("0\n");
		else if (d[aid] != INF) printf("%d\n", d[aid] - 60);
		else printf("IMPOSSIBLE\n");
	}
	return 0;
}
