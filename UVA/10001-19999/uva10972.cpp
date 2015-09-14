#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 1005;
const int maxm = 1e6;

int N, M, E, first[maxn], jump[maxm * 2], link[maxm * 2], iscut[maxm * 2];
int cntlock, cntbcc, pre[maxn], bccno[maxn];
vector<int> G[maxn], BCC[maxn];

int dfs (int u, int fa) {
	int lowu = pre[u] = ++cntlock;

	for (int i = first[u]; i != -1; i = jump[i]) {
		int v = link[i];

		if  (!pre[v]) {
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if (lowv > pre[u])
				iscut[i] = iscut[i^1] = 1;
		} else if (pre[v] < pre[u] && v != fa)
			lowu = min(lowu, pre[v]);
	}
	return lowu;
}

void dfs (int u) {
	bccno[u] = cntbcc;
	BCC[cntbcc].push_back(u);

	for (int i = first[u]; i != -1; i = jump[i]) {
		if (iscut[i]) continue;
		int v = link[i];
		if (!bccno[v]) dfs(v);
	}
}

void findBCC() {
	cntlock = cntbcc = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(bccno, 0, sizeof(bccno));
	for (int i = 1; i <= N; i++)
		if (!pre[i]) dfs(i, -1);

	for (int i = 1; i <= N; i++) {
		if  (!bccno[i]) {
			BCC[++cntbcc].clear();
			dfs(i);
		}
	}
}

inline void addEdge(int u, int v) {
	jump[E] = first[u];
	link[E] = v;
	first[u] = E++;
}

void init () {
	E = 0;
	memset(first, -1, sizeof(first));

	int u, v;
	while (M--) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}
	findBCC();
}

void search(int u, int& c) {
	pre[u] = 1;
	if (G[u].size() <= 1) c++;
	for (int i = 0; i < G[u].size(); i++)
		if (!pre[G[u][i]]) search(G[u][i], c);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();

		for (int i = 1; i <= cntbcc; i++) G[i].clear();
		for (int i = 1; i <= N; i++) {
			for (int j = first[i]; j != -1; j = jump[j]) {
				if (iscut[j]) {
					int u = bccno[i], v = bccno[link[j]];
					G[u].push_back(v);
				}
			}
		}

		int ans = 0;
		memset(pre, 0, sizeof(pre));
		for (int i = 1; i <= cntbcc; i++) {
			if (!pre[i]) {
				int cnt = 0;
				search(i, cnt);
				ans += (cnt == 1 ? 2 : cnt);
			}
		}
		
		if (cntbcc == 1) printf("0\n");
		else printf("%d\n", (ans+1) / 2);
	}
	return 0;
}
