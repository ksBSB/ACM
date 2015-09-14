#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int maxn = 1005;

struct DMST {
	struct Edge {
		int u, v, d;
		Edge(int u = 0, int v = 0, int d = 0): u(u), v(v), d(d) {}
		bool operator < (const Edge& u) const { return d < u.d; }
	};

	int in[maxn], pre[maxn], id[maxn], vis[maxn];
	vector<Edge> edges;


	void init () { edges.clear(); }
	void addEdge(int u, int v, int d) { edges.push_back(Edge(u, v, d)); }

	bool directedMST(int root, int n, int& ans) {
		ans = 0;

		while (true) {
			// 删除自环+找最小入边
			memset(in, inf, sizeof(in));
			for (int i = 0; i < edges.size(); i++) {
				int u = edges[i].u, v = edges[i].v;
				if (edges[i].d < in[v] && u != v) {
					pre[v] = u;
					in[v] = edges[i].d;
				}
			}

			// 判断是否可以到达所有节点
			for (int i = 0; i < n; i++) {
				if (i == root) continue;
				if (in[i] == inf) return false;
			}

			int cntnode = 0;
			//memset(id, -1, sizeof(int) * n);
			//memset(vis, -1, sizeof(int) * n);
			memset(id, -1, sizeof(id));
			memset(vis, -1, sizeof(vis));
			in[root] = 0;

			for (int i = 0; i < n; i++) {
				ans += in[i];
				int v = i;
				while (vis[v] != i && id[v] == -1 && v != root) {
					vis[v] = i;
					v = pre[v];
				}
				if (v != root && id[v] == -1) {
					for (int u = pre[v]; u != v; u = pre[u])
						id[u] = cntnode;
					id[v] = cntnode++;
				}
			}

			// 没有找到环, 终止
			if (cntnode == 0) break;

			// 缩点，重新标记
			for (int i = 0; i < n; i++) {
				if (id[i] == -1)
					id[i] = cntnode++;
			}

			for (int i = 0; i < edges.size(); i++) {
				int v = edges[i].v;
				edges[i].u = id[edges[i].u];
				edges[i].v = id[edges[i].v];
				if (edges[i].u != edges[i].v)
					edges[i].d -= in[v];
			}
			n = cntnode;
			root = id[root];
		}
		return true;
	}
}solver;

int main () {
	int cas, n, m, u, v, w;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		solver.init();
		scanf("%d%d", &n, &m);
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &u, &v, &w);
			solver.addEdge(u, v, w);
		}
		int ans;
		if (solver.directedMST(0, n, ans))
			printf("Case #%d: %d\n", kcas, ans);
		else
			printf("Case #%d: Possums!\n", kcas);
	}
	return 0;
}
