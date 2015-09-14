#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 105;
const int maxm = 1005;
const ll inf = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int v, w, idx;
	Edge (int v = 0, int w = 0, int idx = 0):v(v), w(w), idx(idx) {}
};

struct State {
	int u;
	ll dis;
	State (int u = 0, ll dis = 0): u(u), dis(dis) {}
	bool operator < (const State& u) const { return dis > u.dis; }
};

int N, M, L, S[maxn], P[maxn], V[maxn];
vector<Edge> G[maxn];
ll D[maxn], T[maxm];

void init () {
	memset(T, 0, sizeof(T));
	int u, v, w, idx;
	for (int i = 0; i <= N; i++) G[i].clear();
	for (int i = 1; i <= M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(Edge(v, w, i));
		G[v].push_back(Edge(u, w, i));
	}
}

ll dijkstra(int s, int e) {
	for (int i = 1; i <= N; i++)
		V[i] = P[i] = 0, D[i] = inf;
	D[s] = 0;

	priority_queue<State> Q;
	Q.push(State(s, D[s]));

	while (!Q.empty()) {
		int u = Q.top().u;
		Q.pop();

		if (V[u]) continue;
		V[u] = 1;

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].v, w = G[u][i].w, idx = G[u][i].idx;
			if (idx == e) continue;
			if (D[v] > D[u] + w) {
				D[v] = D[u] + w;
				P[v] = idx;
				Q.push(State(v, D[v]));
			}
		}
	}

	ll ret = 0;
	for (int i = 1; i <= N; i++)
		ret += (D[i] == inf ? L : D[i]);
	return ret;
}

void solve (int s) {
	ll c = dijkstra(s, 0);
	memcpy(S, P, sizeof(P));
	for (int i = 0; i <= M; i++) T[i] += c;

	for (int i = 1; i <= N; i++) if (S[i])
		T[S[i]] += dijkstra(s, S[i]) - c;
}

int main () {
	while (scanf("%d%d%d", &N, &M, &L) == 3) {
		init ();
		for (int i = 1; i <= N; i++)
			solve(i);

		ll ans = 0;
		for (int i = 1; i <= M; i++) ans = max(ans, T[i]);
		printf("%lld %lld\n", T[0], ans);
	}
	return 0;
}
