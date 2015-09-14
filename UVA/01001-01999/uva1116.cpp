#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 10005;

struct Node {
	int idx, val;
	Node (int idx = 0, int val = 0): idx(idx), val(val) {}
	bool operator < (const Node& u) const { return val > u.val; }
};

struct Edge {
	int v, flag;
	Edge(int v = 0, int flag = 0): v(v), flag(flag) {}
	bool operator < (const Edge& u) const { return v < u.v || (v == u.v && flag < u.flag); }
};


int N, M, in[maxn], vi[maxn];
set<Edge> T[maxn];
vector<int> G[maxn], S;
typedef set<Edge>::iterator iter;

void init () {
	scanf("%d%d", &N, &M);

	memset(in, 0, sizeof(in));
	for (int i = 1; i <= N; i++) {
		T[i].clear();
		G[i].clear();
	}

	int u, v;
	for (int i = 1; i <= N + M; i++) {
		scanf("%d%d", &u, &v);
		T[u].insert(Edge(v, 1));
		T[v].insert(Edge(u, 1));
		in[u]++; in[v]++;
	}
}

void dfs (int u) {
	vi[u] = 1;
	S.push_back(u);
	for (int i = 0; i < G[u].size(); i++)
		if (!vi[G[u][i]]) dfs(G[u][i]);
}

void solve () {
	priority_queue<Node> Q;

	memset(vi, 0, sizeof(vi));
	for (int i = 1; i <= N; i++)
		Q.push(Node(i, in[i]));

	while (!Q.empty()) {
		Node cur = Q.top();
		Q.pop();
		
		int u = cur.idx;
		int w = cur.val;
		
		if (vi[u] || in[u] != w) continue;
		vi[u] = 1;

		//if (in[u] > 2) continue;

		S.clear();
		for (iter i = T[u].begin(); i != T[u].end(); i++) {
			Edge e = *i;
			int v = e.v;
			if (e.flag) { G[u].push_back(v); G[v].push_back(u); }

			for (int j = 0; j < 2; j++) {
				iter it = T[v].find(Edge(u, j));
				if (it != T[v].end()) { T[v].erase(it); in[v]--; }
			}
			S.push_back(v);
		}

		if (S.size() == 2) {
			for (int i = 0; i < 2; i++) {
				int v = S[i^1];

				for (int j = 0; j < 2; j++) {
					iter it = T[v].find(Edge(S[i], j));
					if (it != T[v].end()) { T[v].erase(it); in[v]--; }
				}

				in[v]++;
				T[v].insert(Edge(S[i], 0));
				Q.push(Node(v, in[v]));
			}
		}
	}

	S.clear();
	memset(vi, 0, sizeof(vi));
	vi[1] = 1;
	S.push_back(1);
	dfs(min(G[1][0], G[1][1]));
	int n = S.size();
	for (int i = 0; i < n; i++)
		printf("%d%c", S[i], i == n-1 ? '\n' : ' ');
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
		if (cas) printf("\n");
	}
	return 0;
}
