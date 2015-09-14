#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 2005;
const int maxm = 2 * 1e6 + 5;
typedef pair<int,int> pii;

struct State {
	int a, b, c;
	State(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {}
};

int N, M, L[maxm], R[maxm], C[maxm];
int cntlock, pre[maxn], iscut[maxm];
vector<pii> G[maxn];
vector<State> ans;

int dfs (int u, int fa) {
	int lowu = pre[u] = ++cntlock;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i].first, e = G[u][i].second;
		if (!pre[v]) {
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if (C[e] == 2) {
				if (lowv > pre[u]) {
					ans.push_back(State(u, v, 2));
					iscut[e] = 1;
				} else
					ans.push_back(State(u, v, 1));
			}
		} else if (pre[v] < pre[u] && v != fa) {
			lowu = min(lowu, pre[v]);
			if (C[e] == 2)
				ans.push_back(State(u, v, 1));
		}
	}
	return lowu;
}

void findBCC() {
	cntlock = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	for (int i = 1; i <= N; i++)
		if (!pre[i]) dfs(i, -1);
}

void init () {
	for (int i = 1; i <= N; i++) G[i].clear();

	for (int i = 1; i <= M; i++) {
		scanf("%d%d%d", &L[i], &R[i], &C[i]);
		G[L[i]].push_back(make_pair(R[i], i));
		if (C[i] == 2)
			G[R[i]].push_back(make_pair(L[i], i));
	}
	ans.clear();
	findBCC();
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();

		for (int i = 0; i < ans.size(); i++)
			printf("%d %d %d\n", ans[i].a, ans[i].b, ans[i].c);
	}
	return 0;
}
