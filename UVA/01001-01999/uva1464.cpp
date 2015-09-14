#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 10005;
const int maxm = 100005;

int N, M, eccno[maxm];
int cntlock, cntbcc, pre[maxn], iscut[maxn], bccno[maxn];
int E, first[maxn], jump[maxm << 1], link[maxm << 1];
vector<int> G[maxn << 1], BCC[maxn], tmp;
stack<pii> S;

inline void addEdge(int u, int v) {
	jump[E] = first[u];
	link[E] = v;
	first[u] = E++;
}

int dfs (int u, int fa) {
	int lowu = pre[u] = ++cntlock, child = 0;

	for (int i = first[u]; i != -1; i = jump[i]) {
		int v = link[i];
		pii e = make_pair(u, v);

		if (!pre[v]) {
			child++;
			S.push(e);
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if (lowv >= pre[u]) {
				iscut[u] = 1;
				BCC[++cntbcc].clear();
				while (true) {
					e = S.top(); S.pop();
					if (bccno[e.first] != cntbcc) {
						bccno[e.first] = cntbcc;
						BCC[cntbcc].push_back(e.first);
					}
					if (bccno[e.second] != cntbcc) {
						bccno[e.second] = cntbcc;
						BCC[cntbcc].push_back(e.second);
					}
					if (e.first == u && e.second == v) break;
				}
			}
		} else if (pre[v] < pre[u] && v != fa) {
			S.push(e);
			lowu = min(lowu, pre[v]);
		}
	}

	if (fa < 0 && child == 1) iscut[u] = 0;
	return lowu;
}

void findBCC() {
	cntlock = cntbcc = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	for (int i = 1; i <= N; i++)
		if (!pre[i]) dfs(i, -1);
}

void init () {
	E = 0;
	memset(first, -1, sizeof(first));

	int u, v;
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	findBCC();

	for (int i = 1; i <= cntbcc; i++) {
		G[i].clear();
		for (int j = 0; j < BCC[i].size(); j++) bccno[BCC[i][j]] = i;
		for (int j = 0; j < BCC[i].size(); j++) {
			for (int p = first[BCC[i][j]]; p != -1; p = jump[p])
				if (bccno[link[p]] == i) eccno[p>>1] = i;
		}
	}

	int c = 0;
	for (int i = 1; i <= N; i++) {
		if (iscut[i]) {
			c++;
			G[cntbcc + c].clear();

			tmp.clear();
			for (int j = first[i]; j != -1; j = jump[j])
				tmp.push_back(eccno[j>>1]);
			sort(tmp.begin(), tmp.end());
			int n = unique(tmp.begin(), tmp.end()) - tmp.begin();
			for (int j = 0; j < n; j++) {
				G[cntbcc+c].push_back(tmp[j]);
				G[tmp[j]].push_back(cntbcc+c);
				//printf("%d-%d\n", cntbcc + c, tmp[j]);
			}
		}
	}
	N = cntbcc + c;
}

const int maxd = 18;
int vis[maxn << 1], dep[maxn << 1], dp[maxn << 1][maxd];

void dfs (int u, int fa, int d) {
	dep[u] = d;
	dp[u][0] = fa;
	vis[u] = 1;
	for (int i = 1; i < maxd; i++)
		dp[u][i] = dp[dp[u][i-1]][i-1];
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (vis[v]) continue;
		dfs(v, u, d + 1);
	}
}

void LCAinit() {
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= N; i++)
		if (!vis[i]) dfs(i, 0, 0);
}

int LCA(int a, int b) {
	if (dep[a] < dep[b]) swap(a, b);
	int k = 0;
	while ((1<<(k+1)) <= dep[a]) k++;
	for (int i = k; i >= 0; i--)
		if (dep[a]-(1<<i) >= dep[b]) a = dp[a][i];
	if (a == b) return a;

	for (int i = k; i >= 0; i--) {
		if (dp[a][i] != dp[b][i]) {
			a = dp[a][i];
			b = dp[b][i];
		}
	}
	return dp[a][0];
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();
		LCAinit();

		int q, u, v, f;
		scanf("%d", &q);
		while (q--) {
			scanf("%d%d", &u, &v);
			u = eccno[u-1];
			v = eccno[v-1];
			f = LCA(u, v);
			printf("%d\n", (dep[u] + dep[v] - 2 * dep[f]) >> 1);
		}
	}
	return 0;
}
