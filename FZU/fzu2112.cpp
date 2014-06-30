#include <stdio.h>
#include <string.h>

const int N = 100005;

int n, m, f[N], d[N], vis[N];
int cnt, rec[N], g[N];

int getfar(int x) {
	int p, q, t;
	p = q = x;
	while (p != f[p]) p = f[p];

	while (q != f[q]) {
		t = q;
		q = f[q];
		f[q] = p;
	}
	return p;
}

void init() {
	memset(d, 0, sizeof(d));
	memset(g, 0, sizeof(g));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)	f[i] = i;

	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);

		vis[a] = vis[b] = 1;
		d[a]++, d[b]++;

		int x = getfar(a), y = getfar(b);
		if (x != y)	f[y] = x;
	}
}

void handle() {
	cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (vis[i]) {
			int x = getfar(i);
			if (vis[x] != 2) rec[cnt++] = x;
			if (d[i] & 1) g[x]++;
			vis[x] = 2;
		}
	}
}

int solve() {
	int ans = cnt - 1;
	for (int i = 0; i < cnt; i++)
		if (g[rec[i]] > 2) ans = ans + g[rec[i]] / 2 - 1;
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		handle();
		printf("%d\n", solve());
	}
	return 0;
}
