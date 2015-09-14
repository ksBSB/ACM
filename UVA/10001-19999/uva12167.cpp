#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int maxn = 20005;

int N, M, in[maxn], ot[maxn];
int cntlock, cntscc, pre[maxn], low[maxn], sccno[maxn];
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
			low[u] = min(low[u], low[v]);
	}

	if (low[u] == pre[u]) {
		cntscc++;
		while (true) {
			int x = S.top();
			S.pop();
			sccno[x] = cntscc;
			if (x == u) break;
		}
	}
}

void findSCC () {
	cntscc = cntlock = 0;
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

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();

		for (int i = 1; i <= cntscc; i++) in[i] = ot[i] = 1;
		for (int u = 1; u <= N; u++) {
			for (int j = 0; j < G[u].size(); j++) {
				int v = G[u][j];
				if (sccno[u] != sccno[v])
					in[sccno[v]] = ot[sccno[u]] = 0;
			}
		}
		int a = 0, b = 0;
		for (int i = 1; i <= cntscc; i++) {
			if (in[i]) a++;
			if (ot[i]) b++;
		}
		printf("%d\n", cntscc == 1 ? 0 : max(a, b));
	}
	return 0;
}
