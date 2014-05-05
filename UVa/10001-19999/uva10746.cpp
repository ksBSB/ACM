#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <vector>

using namespace std;

#define min(a,b) (a)<(b)?(a):(b)

const int N = 205;
const int T = 100;
const int INF = 1 << 30;

int n, m, tmp, g[N][N], f[N][N];
double cost[N][N];
vector<int> v[N];

void add(int x,  int y) {
	g[x][y]++;
	v[x].push_back(y);
	v[y].push_back(x);
}

void init() {

	tmp = 200;
	memset(g, 0, sizeof(g));
	memset(f, 0, sizeof(f));
	memset(cost, 0, sizeof(cost));
	for (int i = 0; i < N; i++)
		v[i].clear();

	for (int i = 1; i <= n; i++) {

		add(0, i + T);
		add(i + T, i);
		for (int j = 1; j <= m; j++) {
			add(i, j + n + T);
		}
	}

	for (int i = 1; i <= m; i++) {
		add(i + n + T, i + n);
		add(i + n, tmp);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%lf", &cost[i][j + n + T]);
			cost[j + n + T][i] = -cost[i][j + n + T];
		}
	}
}

void solve() {
	queue<int> que;
	double ans = 0, d[N];
	int c, flow = 0,  path[N], vis[N];

	while (1) {

		for (int i = 0; i <= tmp; i++)	
			d[i] = (i == 0) ? 0 : INF;
		memset(path, 0, sizeof(path));
		memset(vis, 0, sizeof(vis));
		que.push(0);
		vis[0] = 1;

		while (!que.empty() ) {
			c = que.front(), que.pop();
			vis[c] = 0;

			int top = v[c].size();
			for (int i = 0; i < top; i++) {
				if (g[c][v[c][i]] > f[c][v[c][i]] && d[v[c][i]] - d[c] - cost[c][v[c][i]] > 1e-6) {
					d[v[c][i]] = d[c] + cost[c][v[c][i]];
					path[v[c][i]] = c;

					if ( vis[v[c][i]] == 0) {
						que.push(v[c][i]);
						vis[v[c][i]] = 1;
					}
				}
			}
		}

		if (INF - d[tmp] < 1e-6) break;
		int t = INF;

		for (int i = tmp; i; i = path[i]) t = min(g[path[i]][i] - f[path[i]][i], t);

		flow += t;
		ans += t * d[tmp];

		for (int i = tmp; i; i= path[i]) {
			f[path[i]][i] += t;
			f[i][path[i]] -= t;
		}
	}
	printf("%.2lf\n", ans / n + 0.001);
}

int main () {
	while (scanf("%d%d", &n, &m), n + m) {
		init();
		solve();
	}
	return 0;
}
