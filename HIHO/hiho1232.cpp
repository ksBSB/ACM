#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, M;
int fa[maxn][20], ca[maxn], da[maxn];
int fb[maxn][20], cb[maxn], db[maxn];

void init () {
	da[1] = db[1] = 0;
	fa[1][0] = fb[1][0] = 1;

	for (int i = 2; i <= N; i++) {
		scanf("%d", &fa[i][0]);
		da[i] = da[fa[i][0]] + 1;
	}
	for (int i = 2; i <= N; i++) {
		scanf("%d", &fb[i][0]);
		db[i] = db[fb[i][0]] + 1;
	}

	for (int k = 1; k < 20; k++) {
		for (int i = 1; i <= N; i++) {
			fa[i][k] = fa[fa[i][k-1]][k-1];
			fb[i][k] = fb[fb[i][k-1]][k-1];
		}
	}
	for (int i = 1; i <= N; i++) {
		sort(fa[i], fa[i] + 20);
		ca[i] = unique(fa[i], fa[i] + 20) - fa[i];
		sort(fb[i], fb[i] + 20);
		cb[i] = unique(fb[i], fb[i] + 20) - fb[i];
	}
}

int solve (int u, int v) {
	while (u != v) {
		if (u > v) {
			int t = lower_bound(fa[u], fa[u] + ca[u], v) - fa[u];
			if (t == ca[u]) t--;
			u = fa[u][t];
		} else {
			int t = lower_bound(fb[v], fb[v] + cb[v], u) - fb[v];
			if (t == cb[v]) t--;
			v = fb[v][t];
		}
	}
	return u;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		int u, v, k = 0;
		for (int i = 1; i <= M; i++) {
			scanf("%d%d", &u, &v);
			u = (u + k) % N + 1, v = (v + k) % N + 1;
			k = solve(u, v);
			printf("%d %d %d\n", k, da[u]-da[k]+1, db[v]-db[k]+1);
		}
	}
	return 0;
}
