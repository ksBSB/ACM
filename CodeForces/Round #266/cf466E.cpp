#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;

const int maxn = 1e5 + 5;

int N, M, K = 0, f[maxn], c[maxn], vis[maxn];
vector<int> G[maxn];
vector<pii> P, Q[maxn];

inline int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

void init () {

	scanf("%d%d", &N, &M);

	for (int i = 0; i <= N; i++)
		f[i] = i;

	int op, x, y;
	while (M--) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &x, &y);
			f[x] = y;
			G[y].push_back(x);
		} else if (op == 2) {
			scanf("%d", &x);
			P.push_back(make_pair(getfar(x), x));
		} else {
			scanf("%d%d", &x, &y);
			pii u = P[y-1];

			Q[x].push_back(make_pair(u.first, K));
			Q[u.second].push_back(make_pair(x, K));
			K++;
		}
	}
}

void dfs (int u) {
	vis[u] = 1;
	for (int i = 0; i < G[u].size(); i++)
		dfs(G[u][i]);

	for (int i = 0; i < Q[u].size(); i++) {
		int v = Q[u][i].first, id = Q[u][i].second;
		if (vis[v])
			c[id]++;
	}
	vis[u] = 0;
}

int main () {
	init();

	for (int i = 1; i <= N; i++) {
		if (f[i] == i)
			dfs(i);
	}

	for (int i = 0; i < K; i++)
		printf("%s\n", c[i] == 2 ? "YES" : "NO");
	return 0;
}
