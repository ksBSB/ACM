#include <stdio.h>
#include <string.h>
#include <queue>

using  namespace std;

const int MAXN = 50000;
const int INF = 1 << 30;
const int N = 105;

struct edge {
	int next, im;
	int far, son;
	int cap, flow;
	int cost;
}s[MAXN];

int n, m, tmp, h[N];

void add(int x, int y, int c, int cost, int im) {

	s[tmp].next = h[x];
	h[x] = tmp;

	s[tmp].im = tmp + im;
	s[tmp].far = x;
	s[tmp].son = y;
	s[tmp].cap = c;
	s[tmp].flow = 0;
	s[tmp].cost = cost;
	tmp++;
}

void init() {

	scanf("%d", &m);
	int a, b, c;

	tmp = 0;
	memset(h, -1, sizeof(h));

	add(0, 1, 2, 0, 1);
	add(1, 0, 0, 0, -1);
	add(n, n + 1, 2, 0, 1);
	add(n + 1, n, 0, 0, -1);

	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, 1, c, 1);
		add(b, a, 0, -c, -1);
		add(b, a, 1, c, 1);
		add(a, b, 0, -c, -1);
	}
}

void solve() {
	queue<int> que;
	int ans = 0, f = 0;
	int u, d[N], vis[N], path[MAXN];

	while (1) {

		for (int i = 0; i <= n + 1; i++) d[i] = (i == 0) ? 0 : INF;
		memset(path, -1, sizeof(path));
		memset(vis, 0, sizeof(vis));

		que.push(0);
		vis[0] = 1;

		while ( !que.empty() ) {
			u = que.front(), que.pop();
			vis[u] = 0;

			for (int i = h[u]; i != -1; i = s[i].next) {
				int v = s[i].son;
				if ( s[i].cap > s[i].flow && d[v] > d[u] + s[i].cost) {
					d[v] = d[u] + s[i].cost;
					path[v] = i;

					if (vis[v] == 0) {
						que.push(v);
						vis[v] = 1;
					}
				}
			}
		}

		if (d[n + 1] == INF) break;
		int a = INF;

		for (int i = n + 1; i; i = s[path[i]].far)
			a = min(a, s[path[i]].cap - s[path[i]].flow);
		f += a;
		ans += a * d[n + 1];

		for (int i = n + 1; i; i = s[path[i]].far) {
			s[path[i]].flow += a;
			int im = s[path[i]].im;
			s[im].flow -= a;
		}
	}

	if (f < 2)
		printf("Back to jail\n");
	else
		printf("%d\n", ans);
}

int main () {

	while (scanf("%d", &n), n) {
		init();
		solve();
	}
	return 0;
}
