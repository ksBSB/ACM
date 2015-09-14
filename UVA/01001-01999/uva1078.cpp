#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int inf = 0x3f3f3f3f;
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;

const int inv[] = {2, 3, 0, 1};
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};

int R, C, grid[maxn][maxn][4];
int N, id[maxn][maxn][4][2];

inline int readint() { int x; scanf("%d", &x); return x; }
inline int ID (int r, int c, int d, int doubled) {
	int& x = id[r][c][d][doubled];
	if (x == 0) x = ++N;
	return x;
}
inline bool cango(int r, int c, int d) {
	if (r < 0 || r >= R || c < 0 || c >= C) return false;
	return grid[r][c][d] > 0;
}

struct Dijkstra {
	struct Edge {
		int u, v, w;
		Edge (int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
	};

	struct State {
		int u, d;
		State(int u = 0, int d = 0): u(u), d(d) {}
		bool operator < (const State& u) const { return d > u.d; }
	};

	int n, m, d[maxn * maxn * 10], v[maxn * maxn * 10];
	vector<Edge> edges;
	vector<int> G[maxn * maxn * 10];

	void init (int n) {
		this->n = n;
		edges.clear();
		for (int i = 0; i < n; i++) G[i].clear();
	}

	void addEdge(int u, int v, int w) {
		edges.push_back(Edge(u, v, w));
		m = edges.size();
		G[u].push_back(m-1);
	}

	void dijkstra(int s) {
		memset(d, inf, sizeof(d));
		memset(v, 0, sizeof(v));

		d[s] = 0;
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
					Q.push(State(e.v, d[e.v]));
				}
			}
		}
	}
}solver;

void init () {
	N = 0;
	memset(id, 0, sizeof(id));
	memset(grid, 0, sizeof(grid));
	solver.init(R * C * 8 + 1);

	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C-1; c++)
			grid[r][c][RIGHT] = grid[r][c+1][LEFT] = readint();
		if (r != R-1) for (int c = 0; c < C; c++)
			grid[r][c][DOWN] = grid[r+1][c][UP] = readint();
	}
}

int main () {
	int cas = 0, r1, c1, r2, c2;
	while (scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2) == 6 && R) {
		r1--, c1--, r2--, c2--;
		init();
		for (int d = 0; d < 4; d++) if(cango(r1, c1, d))
			solver.addEdge(0, ID(r1+dr[d], c1+dc[d], d, 1), grid[r1][c1][d]* 2);

		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				for (int dir = 0; dir < 4; dir++) if (cango(r, c, inv[dir])) {
					for (int newdir = 0; newdir < 4; newdir++) if (cango(r, c, newdir)) {
						for (int doubled = 0; doubled < 2; doubled++) {
							int newr = r + dr[newdir];
							int newc = c + dc[newdir];
							int v = grid[r][c][newdir], newdoubled = 0;
							if (dir != newdir) {
								if (!doubled) v += grid[r][c][inv[dir]];
								newdoubled = 1; v += grid[r][c][newdir];
							}
							solver.addEdge(ID(r, c, dir, doubled), ID(newr, newc, newdir, newdoubled), v);
						}
					}
				}
			}
		}

		solver.dijkstra(0);
		int ans = inf;
		for (int d = 0; d < 4; d++) if (cango(r2, c2, inv[d]))
			for (int doubled = 0; doubled < 2; doubled++) {
				int v = solver.d[ID(r2, c2, d, doubled)];
				if (!doubled) v += grid[r2][c2][inv[d]];
				ans = min(ans, v);
			}
		printf("Case %d: ", ++cas);
		if (ans == inf) printf("Impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}
