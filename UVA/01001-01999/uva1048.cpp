#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 50005;
const int maxm = 25;
const int inf = 0x3f3f3f3f;

struct Dijkstra {
	struct Edge {
		int u, v, w, rid;
		Edge (int u = 0, int v = 0, int w = 0, int rid = 0): u(u), v(v), w(w), rid(rid) {}
	};

	struct State {
		int u, d;
		State(int u = 0, int d = 0): u(u), d(d) {}
		bool operator < (const State& u) const { return d > u.d; }
	};

	int n, m, d[maxn], v[maxn], p[maxn], r[maxn];
	vector<Edge> edges;
	vector<int> G[maxn];

	void init (int n) {
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
	}

	void addEdge(int u, int v, int w, int rid) {
		edges.push_back(Edge(u, v, w, rid));
		m = edges.size();
		G[u].push_back(m-1);
	}

	void putPath(int u) {
		if (p[u] == -1) return;
		u = p[u];
		putPath(edges[u].u);
		printf(" %d", edges[u].rid);
	}

	int dijkstra(int s, int e) {
		memset(d, inf, sizeof(d));
		memset(v, 0, sizeof(v));

		p[s] = d[s] = 0;
		p[s] = -1;
		priority_queue<State> Q;
		Q.push(State(s, d[s]));

		while(!Q.empty()) {
			int u = Q.top().u;
			Q.pop();

			if (v[u]) continue;
			v[u] = 1;

			for (int i = 0; i < G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				if (d[e.v] > d[u] + e.w) {
					d[e.v] = d[u] + e.w;
					p[e.v] = G[u][i];
					Q.push(State(e.v, d[e.v]));
				}
			}
		}
		return d[e];
	}
}solver;

int N, M, C, K, id[maxn][maxm], W[maxm];
vector<int> Ticket[maxm], Trip[maxm], Idx;

int find(int x) { return lower_bound(Idx.begin(), Idx.end(), x) - Idx.begin(); }
int ID(int s, int c) { int& x = id[s][c]; if (x == 0) x = ++K; return x; }


void init () {
	Idx.clear();
	K = 0;
	memset(id, 0, sizeof(id));

	int k, x;
	for (int i = 1; i <= N; i++) {
		Ticket[i].clear();
		scanf("%d%d", &W[i], &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &x);
			Ticket[i].push_back(x);
			Idx.push_back(x);
		}
	}
	scanf("%d", &M);
	for (int i = 1; i <= M; i++) {
		Trip[i].clear();
		scanf("%d", &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &x);
			Trip[i].push_back(x);
			Idx.push_back(x);
		}
	}

	sort(Idx.begin(), Idx.end());
	C = unique(Idx.begin(), Idx.end()) - Idx.begin();
}

void solve (int x) {
	solver.init(C * 11 + 1);
	int sz = Trip[x].size();
	for (int i = 1; i <= N; i++) {
		int s = find(Ticket[i][0]);
		for (int b = 0; b < sz; b++) {
			int p = b;
			for (int j = 1; j < Ticket[i].size(); j++) {
				int e = find(Ticket[i][j]);
				if (e == find(Trip[x][p])) p++;
				solver.addEdge(ID(s, b), ID(e, p), W[i], i);
				if (p >= sz) break;
			}
		}
		//solver.addEdge(0, ID(s, s == find(Trip[x][0])), 0, 0);
		//solver.addEdge(0, ID(s, 0), 0, 0);
	}

	int s = ID(find(Trip[x][0]), 1);

	int e = ID(find(Trip[x][sz-1]), sz);
	printf("Cost = %d\n", solver.dijkstra(s, e));
	printf("  Tickets used:");
	solver.putPath(e);
	printf("\n");
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		init ();
		for (int i = 1; i <= M; i++) {
			printf("Case %d, Trip %d: ", cas, i);
			solve(i);
		}
		cas++;
	}
	return 0;
}
