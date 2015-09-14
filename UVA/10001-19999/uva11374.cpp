#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;

const int maxn = 505;
const int inf = 0x3f3f3f3f;

struct Edge {
	int v, w, bo;
	Edge (int v = 0, int w = 0, int bo = 0): v(v), w(w), bo(bo) {}
};

int N, S, E, D[maxn][maxn], V[maxn][maxn];
vector<int> ans;
vector<Edge> G[maxn];
pii Q[maxn * maxn], pre[maxn][maxn];

void init () {
	for (int i = 1; i <= N; i++) G[i].clear();

	int n, u, v, w;
	for (int i = 0; i < 2; i++) {
		scanf("%d", &n);
		while (n--) {
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(Edge(v, w, i));
			G[v].push_back(Edge(u, w, i));
		}
	}
}

void dijkstra() {
	memset(V, 0, sizeof(V));
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= N; j++) D[i][j] = inf;

	queue<pii> Q;
	Q.push(make_pair(S, 0));
	pre[S][0] = make_pair(-1, -1);
	D[S][0] = 0, V[S][0] = 1;

	while (!Q.empty()) {
		pii cur = Q.front(); Q.pop();
		int u = cur.first, eco = cur.second;
		V[u][eco] = 0;

		for (int i = 0; i < G[u].size(); i++) {
			if (eco && G[u][i].bo) continue;
			int v = G[u][i].v, w = G[u][i].w, e = G[u][i].bo ? u : eco;
			if (D[v][e] > D[u][eco] + w) {
				D[v][e] = D[u][eco] + w;
				pre[v][e] = make_pair(u, eco);
				if (V[v][e] == 0) {
					V[v][e] = 1;
					Q.push(make_pair(v, e));
				}
			}
		}
	}
}

void put(int u, int e) {
	if (u == -1 && e == -1) return;
	put(pre[u][e].first, pre[u][e].second);
	ans.push_back(u);
}

int main () {
	int cas = 0;
	while (scanf("%d%d%d", &N, &S, &E) == 3) {
		if (cas++) printf("\n");
		init ();
		dijkstra();

		int ret = inf, rec = 0;
		for (int i = 0; i <= N; i++) {
			if (ret > D[E][i]) {
				ret = D[E][i];
				rec = i;
			}
		}
		ans.clear();
		put(E, rec);
		for (int i = 0; i < ans.size(); i++)
			printf("%d%c", ans[i], i == ans.size()-1 ? '\n' : ' ');

		if (rec) printf("%d\n", rec);
		else printf("Ticket Not Used\n");
		printf("%d\n", ret);
	}
	return 0;
}
