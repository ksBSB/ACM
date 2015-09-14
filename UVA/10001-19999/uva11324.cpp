#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1005;

int N, M, in[maxn], W[maxn], dp[maxn];
int cntlock, cntscc, pre[maxn], low[maxn], sccno[maxn];
stack<int> S;
vector<int> GN[maxn], GS[maxn];

void dfs (int u) {
	low[u] = pre[u] = ++cntlock;
	S.push(u);

	for (int i = 0; i < GN[u].size(); i++) {
		int v = GN[u][i];
		if (!pre[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (!sccno[v])
			low[u] = min(low[u], low[v]);
	}

	if (low[u] == pre[u]) {
		++cntscc;
		while (true) {
			int x = S.top();
			S.pop();
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
	for (int i = 1; i <= N; i++) GN[i].clear();

	int u, v;
	while (M--) {
		scanf("%d%d", &u, &v);
		GN[u].push_back(v);
	}

	findSCC();

	memset(W, 0, sizeof(W));
	memset(in, 0, sizeof(in));
	for (int i = 1; i <= cntscc; i++)
		GS[i].clear();

	for (int i = 1; i <= N; i++)
		W[sccno[i]]++;

	for (int u = 1; u <= N; u++) {
		for (int j = 0; j < GN[u].size(); j++) {
			int v = GN[u][j];
			if (sccno[u] != sccno[v]) {
				GS[sccno[u]].push_back(sccno[v]);
				in[sccno[v]]++;
			}
		}
	}
}

int solve (int n) {
	queue<int> Q;
	memset(dp, 0, sizeof(dp));

	for (int i = 1; i <= n; i++) if (!in[i]) {
		dp[i] = W[i];
		Q.push(i);
	}

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < GS[u].size(); i++) {
			int v = GS[u][i];
			in[v]--;
			dp[v] = max(dp[v], dp[u] + W[v]);
			if (!in[v])
				Q.push(v);
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, dp[i]);
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while(cas--) {
		init();
		printf("%d\n", solve(cntscc));
	}
	return 0;
}
