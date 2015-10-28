#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
const int maxn = 100005;
typedef long long ll;

stack<int> S;
vector<int> G[maxn];
int dfsclock, cntscc, sccno[maxn], pre[maxn];

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

void findSCC(int n) {
	dfsclock = cntscc = 0;
	memset(pre, 0, sizeof(pre));
	memset(sccno, 0, sizeof(sccno));
	for (int i = 1; i <= n; i++)
		if (!pre[i]) dfs(i);
}

int N, M, C[maxn], in[maxn], ot[maxn];

void init () {
	scanf("%d%d", &N, &M);

	for (int i = 1; i <= N; i++) G[i].clear();

	int u, v;
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}

	findSCC(N);
}


ll get(int c1) {
	int c2 = N - c1;
	return 1LL * N * (N-1) - 1LL * c1 * c2 - M;
}

ll solve () {
	if (cntscc == 1) return -1;

	memset(in, 0, sizeof(in));
	memset(ot, 0, sizeof(ot));
	memset(C, 0, sizeof(C));

	for (int i = 1; i <= N; i++) {
		int u = sccno[i];
		C[u]++;

		for (int j = 0; j < G[i].size(); j++) {
			int v = sccno[G[i][j]];
			if (u == v) continue;
			ot[u]++, in[v]++;
		}
	}

	ll ret = 0;
	for (int i = 1; i <= cntscc; i++) {
		if (in[i] && ot[i]) continue;
		ret = max(ret, get(C[i]));
	}

	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d: %lld\n", kcas, solve());
	}
	return 0;
}
