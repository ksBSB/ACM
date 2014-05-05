#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int,int> pii;

const int N = 1e5;
const int INF = 0x3f3f3f3f;

int n, m, c, a[N*3+10], vis[N*3+10];
int nindex, g[N*3+10];

struct state {
	int v;
	int	val;
	int next;
}edge[N*20];

inline void addEdge (int u, int v, int val) {
	edge[nindex].v = v;
	edge[nindex].val = val;
	edge[nindex].next = g[u];
	g[u] = nindex++;
}

void init () {

	nindex = 0;
	memset(g, -1, sizeof(g));
	memset(vis, 0, sizeof(vis));
	scanf("%d%d%d", &n, &m, &c);

	int a, b, d;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &d);
		vis[d] = 1;
	//	addEdge(i, d+N, 0);
		addEdge(d+N, i, 0);
		if (d > 1)
			addEdge(i, d + N - 1, c);
		if (d < n)
			addEdge(i, d + N + 1, c);
	}

	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &d);
		addEdge(a, b, d);
		addEdge(b, a, d);
	}

	for (int i = 2; i <= n; i++) {
		if (vis[i] && vis[i-1]) {
			addEdge(i+N, i-1+N, c);
			addEdge(i-1+N, i+N, c);
		}
	}
}

int dijkstra() {
	memset(a, INF, sizeof(a));

	priority_queue< pii, vector<pii>, greater<pii> > que; 

	a[1] = 0;
	que.push(make_pair(a[1], 1));

	while ( !que.empty()) {
		pii cur = que.top();
		que.pop();

		int x = cur.second;

		for (int j = g[x]; j != -1; j = edge[j].next) {
			int u = edge[j].v;

			if (a[u] > a[x] + edge[j].val) {
				a[u] = a[x] + edge[j].val;
				que.push(make_pair(a[u], u));
			}
		}
	}

	if (a[n] == INF)
		return -1;
	else
		return a[n];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init();
		printf("Case #%d: %d\n", i, dijkstra());
	}
	return 0;
}
