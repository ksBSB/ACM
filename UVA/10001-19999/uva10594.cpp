#include <stdio.h>
#include <string.h>
#include <queue>

#define ll long long
#define min(a,b) (a)<(b)?(a):(b)

using  namespace std;

const int MAXN = 50000;
ll INF = 1000000000000000;
const int N = 105;

struct edge {
	int next, im;
	int far, son;
	ll cap, flow;
	ll cost;
}s[MAXN];

int n, m, tmp, h[N];
ll K, D;

void add(int x, int y, ll c, ll cost, int im) {

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

	ll a[MAXN], b[MAXN], c[MAXN];

	tmp = 0;
	memset(h, -1, sizeof(h));

	for (int i = 0; i < m; i++)
		scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	scanf("%lld%lld", &K, &D);

	add(0, 1, K, 0, 1);
	add(1, 0, 0, 0, -1);

	for (int i = 0; i < m; i++) {

		add(a[i], b[i], D, c[i], 1);
		add(b[i], a[i], 0, -c[i], -1);
		add(b[i], a[i], D, c[i], 1);
		add(a[i], b[i], 0, -c[i], -1);
	}
}

void solve() {
	queue<int> que;
	ll ans = 0, f = 0, d[N];
	int u, vis[N], path[MAXN];

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

		if (d[n] == INF) break;
		ll a = INF;

		for (int i = n; i; i = s[path[i]].far)
			a = min(a, s[path[i]].cap - s[path[i]].flow);
		f += a;
		ans += a * d[n];

		for (int i = n; i; i = s[path[i]].far) {
			s[path[i]].flow += a;
			int im = s[path[i]].im;
			s[im].flow -= a;
		}
	}

	if (f < K)
		printf("Impossible.\n");
	else
		printf("%lld\n", ans);
}

int main () {

	while (scanf("%d%d", &n, &m) == 2) {
		init();
		solve();
	}
	return 0;
}
