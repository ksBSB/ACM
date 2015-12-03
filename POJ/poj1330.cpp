#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1e4 + 5;
const int inf = 0x3f3f3f3f;
const int BIT = 20;

int dep[maxn], f[maxn][BIT+5];
vector<int> G[maxn];

void ST (int n) {
	for (int k = 1; k <= BIT; k++) {
		for (int i = 1; i <= n; i++) 
			f[i][k] = f[f[i][k-1]][k-1];
	}

	int s;
	for (int i = 1; i <= n; i++) if (f[i][0] == 0) {
		s = i; break;
	}
	memset(dep, inf, sizeof(dep));
	dep[s] = 0;

	queue<int> que;
	que.push(s);
	while (!que.empty()) {
		int u = que.front();
		que.pop();

		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (dep[v] > dep[u] + 1) {
				dep[v] = dep[u] + 1;
				que.push(v);
			}
		}
	}
}

int LCA(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);

	int mv = dep[v] - dep[u];
	for (int i = 0; i <= BIT && mv; mv >>= 1, i++)
		if (mv&1) v = f[v][i];

	if (u == v) return u;

	for (int i = BIT; i >= 0; i--) {
		if (f[u][i] == f[v][i]) continue;
		u = f[u][i]; v = f[v][i];
	}
	return f[u][0];
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		memset(f, 0, sizeof(f));

		int n, u, v;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			f[v][0] = u;
			G[u].push_back(v);
		}
		ST(n);
		scanf("%d%d", &u, &v);
		printf("%d\n", LCA(u, v));
	}
	return 0;
}
