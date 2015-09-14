#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 5005;
const int inf = 0x3f3f3f3f;

struct Edge {
	int u, v, d;
	Edge(int u = 0, int v = 0, int d = 0):u(u), v(v), d(d) {}
	bool operator < (const Edge& a) const { return d > a.d; }
} E[maxn * maxn];

int N, M, F[maxn], C[maxn];
vector<pii> G[maxn];

int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 0; i <= N; i++) {
		F[i] = i, C[i] = 1;
		G[i].clear();
	}

	int u, v, d;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &d);
		E[i] = Edge(u, v, d);
		G[u].push_back(make_pair(v, d));
		G[v].push_back(make_pair(u, d));
	}
	sort(E, E + M);
}

bool judge (int be) {
	int inedge = inf, otedge = 0;
	for (int u = 1; u <= N; u++) {
		if (find(u) != be) continue;

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].first, d = G[u][i].second;
			if (find(v) == be) inedge = min(inedge, d);
			else otedge = max(otedge, d);
		}
	}
	return inedge > otedge;
}

int solve () {
	int ans = 0;

	for (int i = 0; i < M; i++) {
		int u = E[i].u, v = E[i].v, d = E[i].d;

		if (find(u) != find(v)) {
			C[find(v)] += C[find(u)];
			F[find(u)] = find(v);
			if (judge(find(v)))
				ans += C[find(v)];
		}
	}

	//for (int i = 1; i <= N; i++)
	//	if (F[i] == i && C[i] == 1) ans++;
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
