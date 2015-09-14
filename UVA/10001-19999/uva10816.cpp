#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int, double> pii;
const int maxn = 105;
const int maxm = 10005;
const double inf = 1e20;
const double eps = 1e-8;

struct Edge {
	int u, v;
	double t, d;
	Edge(int u = 0, int v = 0, double t = 0, double d = 0): u(u), v(v), t(t), d(d) {}
	bool operator < (const Edge& a) const { return t < a.t || (fabs(t-a.t) < eps && d < a.d); }
}E[maxm];

struct State {
	int u;
	double d;
	State(int u = 0, double d = 0): u(u), d(d) {}
	bool operator < (const State& a) const { return d > a.d; }
};

int N, M, S, T, F[maxn], P[maxn], done[maxn];
double D[maxn];
vector<int> ans;
vector<pii> G[maxn];

int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void init () {
	scanf("%d%d", &S, &T);
	for (int i = 1; i <= N; i++)
		G[i].clear(), F[i] = i;

	for (int i = 0; i < M; i++)
		scanf("%d%d%lf%lf", &E[i].u, &E[i].v, &E[i].t, &E[i].d);
	sort(E, E + M);
}

void put(int u) {
	if (u == 0) return;
	put(P[u]);
	ans.push_back(u);
}

double dijkstra(int s, int e) {
	memset(done, 0, sizeof(done));
	for (int i = 0; i <= N; i++) D[i] = inf;
	P[s] = D[s] = 0;

	priority_queue<State> Q;
	Q.push(State(s, D[s]));

	while (!Q.empty()) {
		int u = Q.top().u;
		Q.pop();

		if (done[u]) continue;
		done[u] = 1;

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].first;
			if (D[v] > D[u] + G[u][i].second) {
				P[v] = u;
				D[v] = D[u] + G[u][i].second;
				Q.push(State(v, D[v]));
			}
		}
	}
	ans.clear();
	put(e);
	for (int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size()-1 ? '\n' : ' ');
	return D[e];
}

void solve () {
	double temp;
	bool flag = false;
	for (int i = 0; i < M; i++) {
		int u = E[i].u, v = E[i].v;
		if (flag && fabs(E[i-1].t - E[i].t) > eps) break;

		if (find(u) != find(v))
			F[find(u)] = find(v);

		G[u].push_back(make_pair(v, E[i].d));
		G[v].push_back(make_pair(u, E[i].d));

		if (find(S) == find(T)) {
			temp = E[i].t;
			flag = true;
		}
	}

	double dis = dijkstra(S, T);
	printf("%.1lf %.1lf\n", dis, temp);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		solve();
	}
	return 0;
}
