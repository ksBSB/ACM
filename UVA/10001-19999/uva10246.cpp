#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int  maxn = 100;
const int inf = 0x3f3f3f3f;
typedef pair<int,int> pii;

int N, M, Q, W[maxn], D[maxn], ans[maxn][maxn];
bool done[maxn];
vector<pii> G[maxn];

struct State {
	int u, d;
	State(int u = 0, int d = 0): u(u), d(d) {}
	bool operator < (const State& a) const { return d > a.d; }
};

void init () {
	for (int i = 1; i <= N; i++) {
		G[i].clear();
		scanf("%d", &W[i]);
	}

	int u, v, w;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
}

void Dijkstra(int s) {
	memset(D, inf, sizeof(D));
	memset(done, false, sizeof(done));
	D[s] = 0;

	priority_queue<State> que;
	que.push(State(s, D[s]));

	while (!que.empty()) {
		int u = que.top().u;
		que.pop();

		if (done[u]) continue;
		done[u] = true;

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].first, w = G[u][i].second;
			if (W[v] > W[s]) continue;
			if (D[v] > D[u] + w) {
				D[v] = D[u] + w;
				que.push(State(v, D[v]));
			}
		}
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			ans[i][j] = min(ans[i][j], D[i] + D[j] + W[s]);
}

int main () {
	int cas = 0;
	while (scanf("%d%d%d", &N, &M, &Q) == 3 && N + M + Q) {
		if (cas) printf("\n");
		init();
		memset(ans, inf, sizeof(ans));
		for (int i = 1; i <= N; i++)
			Dijkstra(i);

		int u, v;
		printf("Case #%d\n", ++cas);
		for (int i = 0; i < Q; i++) {
			scanf("%d%d", &u, &v);
			if (ans[u][v] == inf) printf("-1\n");
			else printf("%d\n", ans[u][v]);
		}
	}
	return 0;
}
