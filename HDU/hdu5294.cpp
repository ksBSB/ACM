#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 60000 + 5;
const int inf = 0x3f3f3f3f;

int N, M, E, first[maxn], jump[maxn * 2], link[maxn * 2], val[maxn * 2];

inline void addEdge(int u, int v, int w) {
	jump[E] = first[u];
	link[E] = v;
	val[E] = w;
	first[u] = E++;
}

void init () {
	E = 0;
	memset(first, -1, sizeof(first));

	int u, v, w;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u - 1, v - 1, w);
		addEdge(v - 1, u - 1, w);
	}
}

struct Node {
	int w, d, v;
	Node (int w = 0, int d = 0, int v = 0) {
		this->w = w;
		this->d = d;
		this->v = v;
	}
	bool operator < (const Node &a) const {
		if (w != a.w)
			return w > a.w;
		return d > a.d;
	}
};
int dp[maxn], dis[maxn], vis[maxn];

int dijkstra(int s, int t) {
	priority_queue<Node> Q;
	memset(vis, 0, sizeof(vis));
	memset(dp, inf, sizeof(dp));
	memset(dis, inf, sizeof(dis));

	dp[s] = dis[s] = 0;
	Q.push(Node(dp[s], dis[s], s));
	vis[s] = 1;

	while (!Q.empty()) {
		int u = Q.top().v;
		vis[u] = 0;
		Q.pop();

		for (int i = first[u]; i + 1; i = jump[i]) {
			int v = link[i];
			int w = val[i];

			if (dp[u] + w < dp[v] || (dp[u] + w == dp[v] && dis[u] + 1 < dis[v])) {
				dp[v] = dp[u] + w;
				dis[v] = dis[u] + 1;
				if (vis[v] == 0) {
					vis[v] = 1;
					Q.push(Node(dp[v], dis[v], v));
				}
			}
		}
	}
	return dis[t];
}

int dfs (int u, int f) {
	if (u == N - 1)
		return 1;

	int ret = 0;
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == f || dp[u] + val[i] != dp[v])
			continue;
		if (dfs(v, u) > 0) ret++;
	}
	return ret;
}

void solve () {
	int ans = M - dijkstra(0, N-1);
	printf("%d %d\n", dfs(0, -1), ans);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		solve();
	}
	return 0;
}
