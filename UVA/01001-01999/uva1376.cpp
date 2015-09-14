#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 2005;
const int maxm = 2 * 1e6 + 5;
const int inf = 0x3f3f3f3f;

struct Dijkstra {
	struct Edge {
		int u, v, d;
		Edge(int u = 0, int v = 0, int d = 0): u(u), v(v), d(d) {}
	};

	struct State {
		int u, d;
		State (int u = 0, int d = 0): u(u), d(d) {}
		bool operator < (const State& u) const { return d > u.d; }
	};

	int n, m, dis[maxm], vis[maxm];
	vector<Edge> edges;
	vector<int> G[maxm];

	void init (int n) {
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
	}

	void addEdge(int u, int v, int d) {
		edges.push_back(Edge(u, v, d));
		m = edges.size();
		G[u].push_back(m-1);
	}

	int dijkstra (int s, int e) {
		memset(vis, 0, sizeof(int) * n);
		memset(dis, inf, sizeof(int) * n);
		dis[s] = 0;

		priority_queue<State> que;
		que.push(State(s, dis[s]));

		while (!que.empty()) {
			int u = que.top().u;
			que.pop();

			if (vis[u]) continue;
			vis[u] = 1;

			for (int i = 0; i < G[u].size(); i++) {
				Edge& edge = edges[G[u][i]];
				int v = edge.v, d = edge.d;
				if (dis[v] > dis[u] + d) {
					dis[v] = dis[u] + d;
					que.push(State(v, dis[v]));
				}
			}
		}
		return dis[e];
	}
}solver;

int N, M, K, id[maxn * 2][maxn];

inline int ID (int x, int y) {
	if (y < 0 || x >= 2 * N - 2) return 0;
	if (x < 0 || y >= M - 1) return 1;
	int& t = id[x][y];
	if (t == 0) t = ++K;
	return t;
}

void init () {
	K = 1;
	memset(id, 0, sizeof(id));
	int w;

	solver.init(2 * ((N-1)*(M-1) + 1));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M-1; j++) {
			scanf("%d", &w);
			int u = ID(2*i-1, j), v = ID(2*i, j);
			solver.addEdge(u, v, w);
			solver.addEdge(v, u, w);
		}
	}

	for (int i = 0; i < N-1; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &w);
			int u = ID(2*i+1, j), v = ID(2*i, j-1);
			solver.addEdge(u, v, w);
			solver.addEdge(v, u, w);
		}
	}

	for (int i = 0;i  < N-1; i++) {
		for (int j = 0; j < M-1; j++) {
			scanf("%d", &w);
			int u = ID(2*i, j), v = ID(2*i+1, j);
			solver.addEdge(u, v, w);
			solver.addEdge(v, u, w);
		}
	}
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		printf("Case %d: Minimum = %d\n", cas++, solver.dijkstra(0, 1));
	}
	return 0;
}
