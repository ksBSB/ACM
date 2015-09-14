#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 55;
const double eps = 1e-3;

struct BellmanFord {

	struct Edge {
		int u, v;
		double d;
		Edge(int u = 0, int v = 0, double d = 0):u(u), v(v), d(d) {}
	};

	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool inq[maxn];
	int p[maxn], c[maxn];
	double d[maxn];

	void init (int n) {
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
	}

	void addEdge (int u, int v, double d) {
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
	scanf("%d%d", &N, &M);
	solver.init(N);
	T = 0;

	int u, v, d;
	while (M--) {
		scanf("%d%d%d", &u, &v, &d);
		solver.addEdge(u-1, v-1, d);
		T = max(T, d);
	}
}

bool judge(double x) {
	for (int i = 0; i < solver.m; i++) solver.edges[i].d -= x;
	bool ret = solver.negativeCycle();
	for (int i = 0; i < solver.m; i++) solver.edges[i].d += x;
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init ();
		printf("Case #%d: ", kcas);
		if (!judge(T + 1)) printf("No cycle found.\n");
		else {
			double l = 0, r = T;
			while (r - l > eps) {
				double mid = (l + r) / 2;
				if (judge(mid)) r = mid;
				else l = mid;
			}
			printf("%.2lf\n", l);
		}
	}
	return 0;
}
