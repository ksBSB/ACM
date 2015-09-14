#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e4 + 5;

int N, M, f[maxn], cnt[maxn];
int cntlock, cntscc, pre[maxn], low[maxn];
vector<int> G[maxn];

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) G[i].clear();

	int u, v;
	while (M--) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}
}

bool draw(int e, int u) {
	while (f[u] != e) {
		cnt[u]++;
		if (cnt[u] >= 2) return false;
		u = f[u];
	}
	return true;
}

bool dfs (int u) {
	low[u] = pre[u] = ++cntlock;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!pre[v]) {
			f[v] = u;
			if (!dfs(v)) return false;
			low[u] = min(low[u], low[v]);
		} else {
			low[u] = min(low[u], pre[v]);
			if (!draw(v, u)) return false;
		}
	}
	if (low[u] == pre[u]) cntscc++;
	return true;
}

bool findSCC() {
	cntscc = cntlock = 0;
	memset(cnt, 0, sizeof(cnt));
	memset(pre, 0, sizeof(pre));
	for (int i = 0; i < N; i++)
		if (!pre[i] && !dfs(i)) return false;
	return cntscc <= 1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%s\n", findSCC() ? "YES" : "NO");
	}
	return 0;
}
