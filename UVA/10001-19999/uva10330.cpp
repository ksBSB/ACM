#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

#define min(a,b) (a)<(b)?(a):(b)

const int N = 205;
const int tmp = 100;
const int INF = 0x3f3f3f3f;

int n, g[N][N], f[N][N];

void init() {
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));

	int a, b, c, t;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &c);
		g[i + tmp][i] = c;
	}

	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		scanf("%d%d%d", &a, &b, &c);
		g[a][b + tmp] = c;
	}

	scanf("%d%d", &a, &b);
	for (int i = 0; i < a; i++) {
		scanf("%d", &c);
		g[0][c + tmp] = INF;
	}

	for (int i = 0; i < b; i++) {
		scanf("%d", &c);
		g[c][n + tmp + 1] = INF;
	}
}

int solve() {
	n = n + tmp + 1;
	int a[N], vis[N];
	int ans = 0;
	queue<int> q;

	while (1) {

		memset(vis, 0, sizeof(vis));
		memset(a, 0, sizeof(a));

		int c = 0, t;

		vis[c] = 0;
		a[c] = INF;
		q.push(c);

		while (!q.empty()) {

			c = q.front(), q.pop();

			for (int i = 0; i <= n; i++) {

				t = min(g[c][i] - f[c][i], a[c]);

				if (t > a[i]) {
					vis[i] = c;
					a[i] = t;
					q.push(i);
				}
			}
		}

		if (a[n] == 0) break;
		ans += a[n];

		for (int i = n; i; i = vis[i]) {

			f[i][vis[i]] -= a[n];
			f[vis[i]][i] += a[n];
		}
	}
	return ans;
}

int main () {

	while (scanf("%d", &n) == 1) {

		init();
		printf("%d\n", solve());
	}
	return 0;
}
