#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 505;
//const double eps = 1e-3;

struct BellmanFord {

	struct Edge {
		int u, v, d;
		Edge(int u = 0, int v = 0, int d = 0):u(u), v(v), d(d) {}
	};

	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool inq[maxn];
	int d[maxn], p[maxn], c[maxn];

	void init (int n) {
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
	}

	void addEdge (int u, int v, int d) {
		edges.push_back(Edge(u, v, d));
		m = edges.size();
		G[u].push_back(m-1);
	}

	bool negativeCycle() {
		queue<int> que;
		memset(c, 0, sizeof(c));
		memset(inq, 0, sizeof(inq));

		for (int i = 0; i < n; i++) {
			d[i] = 0, inq[i] = true;
			que.push(i);
		}

		while (!que.empty()) {
			int u = que.front();
			que.pop();
			inq[u] = false;

			for (int i = 0; i < G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				if (d[e.v] > d[u] + e.d) {
					d[e.v] = d[u] + e.d;
					p[e.v] = G[u][i];
					if (!inq[e.v]) {
						que.push(e.v);
						inq[e.v] = true;
						if (++c[e.v] > n) return true;
					}
				}
			}
		}
		return false;
	}
}solver;

int N, M, T;

void init () {
	solver.init(N+1);
	T = 0;

	int u, v, d;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &d);
		solver.addEdge(u, v, d);
		T = max(T, d);
	}
	for (int i = 1; i <= N; i++)
		solver.addEdge(0, i, 0);
}

bool judge(int x) {
	for (int i = 0; i < solver.m; i++) solver.edges[i].d -= x;
	bool ret = solver.negativeCycle();
	for (int i = 0; i < solver.m; i++) solver.edges[i].d += x;
	return !ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		if (!judge(1)) printf("No Solution\n");
		else if (judge(T+1)) printf("Infinite\n");
		else {
			int l = 1, r = T+1;
			while (l < r - 1) {
				int mid = (l + r) >> 1;
				if (judge(mid)) l = mid;
				else r = mid;
			}
			printf("%d\n", l);
		}
	}
	return 0;
}
