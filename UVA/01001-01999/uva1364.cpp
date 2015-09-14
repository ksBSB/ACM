#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 1005;

int N, M, vis[maxn][maxn], color[maxn], odd[maxn];
int cntlock, cntbcc, pre[maxn], low[maxn], iscut[maxn], bccno[maxn];
stack<pii> S;
vector<int> G[maxn], BCC[maxn];

bool bipartite (int u, int d) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (bccno[v] != d) continue;
		if (color[v] == color[u]) return false;
		if (!color[v]) {
			color[v] = 3 - color[u];
			if (!bipartite(v, d)) return false;
		}
	}
	return true;
}

int dfs (int u, int fa) {
	int lowu = pre[u] = ++cntlock, child = 0;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		pii e = make_pair(u, v);

		if (!pre[v]) {
			child++;
			S.push(e);
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);

			if (lowv >= pre[u]) {
				iscut[u] = true;
				BCC[++cntbcc].clear();

				while (true) {
					e = S.top(); S.pop();
					if (bccno[e.first] != cntbcc) {
						BCC[cntbcc].push_back(e.first);
						//bccno[e.first] = cntbcc;
					}
					if (bccno[e.second] != cntbcc) {
						BCC[cntbcc].push_back(e.second);
						//bccno[e.second] = cntbcc;
					}
					if (u == e.first && v == e.second) break;
				}
			}

		} else if (v != fa && pre[v] < pre[u]) {
			S.push(e);
			lowu = min(lowu, pre[v]);
		}
	}

	if (fa < 0 && child == 1) iscut[u] = 0;
	return low[u] = lowu;
}

void findBCC () {
	cntlock = cntbcc = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	for (int i = 1; i <= N; i++)
		if (!pre[i]) dfs(i, -1);
}

void init () {
	int u, v;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= N; i++) G[i].clear();

	while (M--) {
		scanf("%d%d", &u, &v);
		vis[u][v] = vis[v][u] = 1;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j < i; j++) {
			if (vis[i][j]) continue;
			G[i].push_back(j);
			G[j].push_back(i);
		}
	}

	findBCC();
}


int solve () {
	memset(odd, 0, sizeof(odd));

	for (int i = 1; i <= cntbcc; i++) {
		for (int j = 0; j < BCC[i].size(); j++)
			bccno[BCC[i][j]] = i;

		memset(color, 0, sizeof(color));
		color[BCC[i][0]] = 1;
		if (!bipartite(BCC[i][0], i)) {
			for (int j = 0; j < BCC[i].size(); j++) odd[BCC[i][j]] = 1;
		}
	}

	int ans = 0;
	for (int i = 1; i <= N; i++)
		if (!odd[i]) ans++;
	return ans;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init ();
		printf("%d\n", solve());
	}
	return 0;
}
