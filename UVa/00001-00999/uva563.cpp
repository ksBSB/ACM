#include <stdio.h>
#include <string.h>
#include <queue>

#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)

using namespace std;

const int N = 5010;
const int T = 2500;
const int INF = 1 << 20;
const int dir[10][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int r, c, n, tmp;
int p[N][N], f[N][N];
int g[N][T + 10], son[N];

void add(int x, int y) {
	p[x][y] = 1;
	g[x][son[x]++] = y;
}

void init() {

	memset(g, 0, sizeof(g));
	memset(son, 0, sizeof(son));

	memset(p, 0, sizeof(p));
	memset(f, 0, sizeof(f));

	scanf("%d%d%d", &r, &c, &n);
	tmp = 5001;

	for (int i = 1; i <= r; i++) {

		for (int j = 1; j <= c; j++) {

			if (i == 1 || j == 1 || i == r || j == c)
				add( (i-1) * c + j, 0);

			add( (i-1) * c + j + T, (i-1) * c + j);

			for (int k = 0; k < 4; k++) {

				int p = i + dir[k][0], q = j + dir[k][1];

				if (p <= 0 || p > r) continue;
				if (q <= 0 || q > c) continue;

				add( (i-1) * c + j, (p-1) * c + q + T);
			}
		}
	}

	int a, b;
	for (int i = 0; i < n; i++) {

		scanf("%d%d\n", &a, &b);
		add(tmp, (a-1) * c + b + T);	
	}
}

int solve() {
	int ans = 0;
	int k, s[N], path[N];
	queue<int> que;

	while (1) {

		memset(path, 0, sizeof(path));
		memset(s, 0, sizeof(s));

		path[tmp] = tmp;
		s[tmp] = INF;
		que.push(tmp);

		while (!que.empty() ) {
			k = que.front(), que.pop();

			for (int i = 0; i < son[k]; i++) {


				if ( !s[g[k][i]] && p[k][g[k][i]] > f[k][g[k][i]]) {

					s[g[k][i]] = min(s[k], p[k][g[k][i]] - f[k][g[k][i]]);
					path[g[k][i]] = k;
					que.push(g[k][i]);
				}
			}
		}

		if (s[0] == 0) break;

		ans += s[0];
		for (int i = 0; i != tmp; i = path[i]) {
			f[path[i]][i] += s[0];
			f[i][path[i]] -= s[0];
		}
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		int ans = solve();
		printf("%s\n", ans == n ? "possible" : "not possible");
	}
	return 0;
}
