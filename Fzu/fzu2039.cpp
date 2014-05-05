#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int N  = 205;
const int INF = 0x3f3f3f3f;

int n, m, tmp, t, g[N][N], f[N][N];

void init() {
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));

	scanf("%d%d%d", &n, &m, &t);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			g[i][j + n] = 1;
	}

	int a, b;
	for (int i = 0; i < t; i++) {
		scanf("%d%d", &a, &b);
		g[a][b + n] = 0;
	}
	tmp = n + m + 1;

	for (int i = 1; i <= n; i++) g[0][i] = 1;
	for (int i = 1; i <= m; i++) g[n + i][tmp] = 1;
}

int solve() {
	queue<int> q;
	int d[N], v[N], ans = 0;
	
	while (true) {
		memset(d, 0, sizeof(d));
		memset(v, 0, sizeof(v));
		d[0] = INF;
		q.push(0);

		while ( !q.empty() ) {
			int u = q.front(); q.pop();
			for (int i = 0; i <= tmp; i++) {
				if (g[u][i] - f[u][i] > 0 && !d[i]) {
					d[i] = min(d[u], g[u][i] - f[u][i]);
					v[i] = u;
					q.push(i);
				}
			}
		}

		if (d[tmp] == 0) break;
		ans += d[tmp];

		for (int i = tmp; i; i = v[i]) {
			f[v[i]][i] += d[tmp];
			f[i][v[i]] -= d[tmp];
		}
	}

	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case %d: %d\n", i, solve() );
	}
	return 0;
}
