#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int maxn = 1e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int N, M, K, p[maxn], vis[maxn];
ll d[maxn];
vector<pii> g[maxn];

void init () {
	scanf("%d%d%d", &N, &M, &K);
	int u, v, x;
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &u, &v, &x);
		g[u].push_back(make_pair(v, x));
		g[v].push_back(make_pair(u, x));
	}
}

int solve () {
	for (int i = 0; i <= N; i++)
		d[i] = INF;
	d[1] = 0;

	memset(p, 0, sizeof(p));
	queue<int> que;
	vis[1] = 1;
	que.push(1);

	for (int i = 1; i <= K; i++) {
		int u, x;
		scanf("%d%d", &u, &x);
		if (d[u] > x) {
			d[u] = x; p[u] = 1;

			if (vis[u] == 0) {
				vis[u] = 1;
				que.push(u);
			}
		}
	}

	while (!que.empty()) {
		int u = que.front();
		que.pop();
		vis[u] = 0;

		for (int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].first, x = g[u][i].second;

			if (d[v] >= d[u] + x && p[v])
				p[v] = 0;

			if (d[v] > d[u] + x) {
				d[v] = d[u] + x;
				if (vis[v] == 0) {
					vis[v] = 1;
					que.push(v);
				}
			}
		}
	}

	for (int i = 1; i <= N; i++)
		K -= p[i];
	return K;
}

int main () {
	init();
	printf("%d\n", solve());
	return 0;
}
