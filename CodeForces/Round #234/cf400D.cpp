#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1e5+5;
const int K = 505;
const int INF = 0x3f3f3f3f;

int n, m, k, t[N], f[N];
int c[K], d[K][K];

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

void init () {
	scanf("%d%d%d", &n, &m, &k);
	memset(d, INF, sizeof(d));
	for (int i = 1; i <= n; i++) f[i] = i;

	int p = 1, u, v, x;
	for (int i = 1; i <= k; i++) {
		scanf("%d", &c[i]);
		for (int j = 0; j < c[i]; j++) t[p++] = i;
	}

	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &u, &v, &x);

		int ui, vi;
		if (x == 0) {
			ui = getfar(u);
			vi = getfar(v);
			if (ui != vi) f[vi] = ui;
		}

		ui = t[u]; vi = t[v];
		d[ui][vi] = d[vi][ui] = min(d[ui][vi], x);
	}
}

bool judge () {

	int p = 1;
	for (int i = 1; i <= k; i++) {
		int u = getfar(p);
		for (int j = 0; j < c[i]; j++) {
			int v = getfar(p);
			if (v != u) return false;
			p++;
		}
	}
	return true;
}

void solve () {
	for (int i = 1; i <= k; i++) d[i][i] = 0;

	for (int x = 1; x <= k; x++) {
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j <= k; j++) {
				d[i][j] = min(d[i][j], d[i][x] + d[x][j]);
			}
		}
	}
}

int main () {
	init ();
	if (judge()) {
		solve ();
		printf("Yes\n");
		for (int i = 1; i <= k; i++) {
			for (int j = 1; j < k; j++) printf("%d ", d[i][j] != INF ? d[i][j] : -1);
			printf("%d\n", d[i][k] != INF ? d[i][k] : -1);
		}
	} else
		printf("No\n");
	return 0;
}
