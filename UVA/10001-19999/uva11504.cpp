#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, M, in[maxn];
int cntlock, cntscc, pre[maxn], sccno[maxn], low[maxn];
vector<int> G[maxn];
stack<int> S;

void dfs (int u) {
	pre[u] = low[u] = ++cntlock;
	S.push(u);

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!pre[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (!sccno[v])
			low[u] = min(low[u], pre[v]);
	}

	if (low[u] == pre[u]) {
		cntscc++;
		while (true) {
			int x = S.top(); S.pop();
			sccno[x] = cntscc;
			if (x == u) break;
		}
	}
}

void findSCC() {
	cntlock = cntscc = 0;
	memset(pre, 0, sizeof(pre));
	memset(sccno, 0, sizeof(sccno));
	for (int i = 1; i <= N; i++)
		if (!pre[i]) dfs(i);
}

void init () {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) G[i].clear();

	int u, v;
	while (M--) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}
	findSCC();
}

int solve () {
	memset(in, 0, sizeof(in));

	for (int i = 1; i <= N; i++) {
		int u = sccno[i];
		for (int j = 0; j < G[i].size(); j++) {
			int v = sccno[G[i][j]];
			if (u != v) in[v] = 1;
		}
	}

	int ret = 0;
	for (int i = 1; i <= cntscc; i++)
		if (!in[i]) ret++;
	return ret;
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
