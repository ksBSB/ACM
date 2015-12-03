#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
const int maxn = 2005;

/* Strong connected */
stack<int> S;
vector<int> G[maxn];
int dfsclock, cntscc, sccno[maxn], pre[maxn];

int dfs(int u) {
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
	for (int i = 0; i < n; i++)
		if (!pre[i]) dfs(i);
}

int N, M, K, BW, L[maxn];
bool T[maxn];

bool match(int u) {
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i] - BW;
		if (!T[v]) {
			T[v] = true;
			if (!L[v] || match(L[v])) {
				L[v] = u;
				return true;
			}
		}
	}
	return false;
}

int KM (int n) {
	int ret = 0;
	memset(L, 0, sizeof(L));
	for (int i = 1; i <= n; i++) {
		memset(T, false, sizeof(T));
		if (match(i)) ret++;
	}
	return ret;
}

void init () {
	scanf("%d%d", &N, &M);
	BW = N + M;
	for (int i = 1; i <= BW * 2; i++) G[i].clear();

	int k, x;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &k);
		while (k--) {
			scanf("%d", &x);
			G[i].push_back(x+BW);
		}
	}
	K = KM(N);
	for (int i = 1; i <= M-K; i++) {
		for (int j = 1; j <= M; j++)
			G[N+i].push_back(j+BW);
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N-K; j++)
			G[i].push_back(M+j+BW);
	}
	int tmp = KM(N+M-K);
	for (int i = 1; i <= N+M-K; i++)
		G[i+BW].push_back(L[i]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		findSCC(N+M-K);
		printf("Case #%d:\n", kcas);

		vector<int> ans;
		for (int i = 1; i <= N; i++) {
			ans.clear();
			for (int j = 0; j < G[i].size(); j++) {
				int v = G[i][j];
				if (v - BW > M) continue;
				if (sccno[i] == sccno[v])
					ans.push_back(v-BW);
			}
			sort(ans.begin(), ans.end());
			printf("%lu", ans.size());
			for (int i = 0; i < ans.size(); i++)
				printf(" %d", ans[i]);
			printf("\n");
		}
	}
	return 0;
}
