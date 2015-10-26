#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 205;

int N, M, K, cnt, L[maxn], vis[maxn][maxn], ans[maxn];
bool T[maxn], used[maxn];
vector<int> G[maxn];

bool match (int u, int e) {
	if (u <= e) return false;

	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (!T[v]) {
			T[v] = true;
			if (!L[v] || match(L[v], e)) {
				L[v] = u;
				return true;
			}
		}
	}
	return false;
}

int KM () {
	int ret = 0;
	memset(L, 0, sizeof(L));
	for (int i = 1; i <= N; i++) {
		memset(T, false, sizeof(T));
		if (match(i, 0)) ret++;
	}
	return ret;
}

void init () {
	memset(vis, 0, sizeof(vis));
	scanf("%d%d%d", &N, &M, &K);

	int x;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &x);
			vis[j][x] = 1;
		}
	}
	for (int i = 1; i <= N; i++) {
		G[i].clear();
		for (int j = 1; j <= N; j++) if (!vis[i][j])
			G[i].push_back(j);
	}
}

int tmp[maxn];
bool judge (int d, int c) {
	if (L[c] == d) return true;

	
	int t = 1;
	for (int i = 1; i <= N; i++) {
		tmp[i] = L[i];
		T[i] = false;
		if (L[i] == d) t = i;
	}

	int nf = L[c];
	L[c] = d;
	L[t] = 0;

	if (match(nf, d)) {
		return true;
	} else {
		memcpy(L, tmp, sizeof(int) * (N+1));
		return false;
	}
}

bool dfs (int d) {
	if (d == N + 1)
		return ++cnt == K;

	for (int i = 0; i < G[d].size(); i++) {
		int c = G[d][i];
		if (used[c]) continue;

		if (judge(d, c)) {
			used[c] = true;
			ans[d] = c;
			if (dfs(d + 1)) return true;
			used[c] = false;
		}
	}
	return false;
}

void solve () {
	cnt = 0;
	memset(used, 0, sizeof(used));

	if (KM() == N && dfs(1)) {
		for (int i = 1; i <= N; i++) printf(" %d", ans[i]);
		printf("\n");
	} else
		printf(" -1\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d:", kcas);
		solve();
	}
	return 0;
}
