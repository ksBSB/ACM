#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
const int maxn = 4005;

int N, pre[maxn], sccno[maxn], dfsclock, cntscc;
vector<int> G[maxn];
stack<int> S;

int dfs (int u) {
	int lowu = pre[u] = ++dfsclock;
	S.push(u);

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!pre[v]) {
			int lowv = dfs(v);
			lowu = min(lowu, lowv);
		} else if (!sccno[v])
			lowu = min(lowu, pre[v]);
	}
	if (lowu == pre[u]) {
		cntscc++;
		while (true) {
			int x = S.top();
			S.pop();
			sccno[x] = cntscc;
			if (x == u) break;
		}
	}
	return lowu;
}

void findSCC () {
	dfsclock = cntscc = 0;
	memset(pre, 0, sizeof(pre));
	memset(sccno, 0, sizeof(sccno));
	for (int i = 1; i <= 2*N; i++)
		if (!pre[i]) dfs(i);
}

int main () {
	while (scanf("%d", &N) == 1) {

		int t, x;
		for (int i = 1; i <= N; i++) {
			G[i].clear();
			scanf("%d", &t);
			while (t--) {
				scanf("%d", &x);
				G[i].push_back(x + N);
			}
		}
		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			G[x+N].clear();
			G[x+N].push_back(i);
		}

		findSCC();

		vector<int> ans;
		for (int i = 1; i <= N; i++) {
			ans.clear();
			for (int j = 0; j < G[i].size(); j++) {
				if (sccno[i] == sccno[G[i][j]]) ans.push_back(G[i][j]-N);
			}

			printf("%lu", ans.size());
			sort(ans.begin(), ans.end());
			for (int j = 0; j < ans.size(); j++)
				printf(" %d", ans[j]);
			printf("\n");
		}
	}
	return 0;
}
