#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn = 1005;
const int inf = 0x3f3f3f3f;

int N, M, D[maxn], P[maxn], V[maxn], C[maxn];
ll dp[maxn];
vector<int> T[maxn];
vector<pii> G[maxn];

struct State {
	int dis, idx;
	State (int dis = 0, int idx = 0):dis(dis), idx(idx) {}
	bool operator < (const State& u) const { return dis > u.dis; }
};

void init () {
	for (int i = 1; i <= N; i++) G[i].clear();

	int u, v, w;
	scanf("%d", &M);
	while (M--) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
}

void dijkstra (int s, int e) {
	memset(V, 0, sizeof(V));
	memset(D, inf, sizeof(D));
	
	D[s] = 0;
	priority_queue<State> Q;
	Q.push(State(D[s], s));


	while (!Q.empty()) {
		int u = Q.top().idx;
		Q.pop();

		if (V[u]) continue;
		V[u] = 1;

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].first, w = G[u][i].second;
			if (D[v] > D[u] + w) {
				D[v] = D[u] + w;
				Q.push(State(D[v], v));
			}
		}
	}
}

ll dfs(int u) {
	ll& ans = dp[u];
	if (ans != -1) return ans;
	if (u == 2) return ans = 1;
	ans = 0;

	for (int i = 0; i < T[u].size(); i++)
		ans += dfs(T[u][i]);
	return ans;
}

ll solve () {
	dijkstra(2, 1);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= N; i++) {
		T[i].clear();
		for (int j = 0; j < G[i].size(); j++) {
			int v = G[i][j].first, w = G[i][j].second;
			if (D[i] > D[v])
				T[i].push_back(v);
		}
	}
	return dfs(1);
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init ();
		printf("%lld\n", solve());
	}
	return 0;
}
