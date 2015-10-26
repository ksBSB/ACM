#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 105;

int N, M, L[maxn], ans[maxn][maxn], row[maxn], col[maxn], in[maxn];
bool S[maxn], T[maxn];
vector<int> g[maxn];
char G[maxn][maxn];

bool match (int u) {
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
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

void KM () {
	memset(L, 0, sizeof(L));
	for (int i = 1; i <= N; i++) {
		memset(T, false, sizeof(T));
		match(i);
	}
}

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%s", G[i]+1);

	memset(ans, 0, sizeof(ans));
	memset(row, 0, sizeof(row));
	memset(col, 0, sizeof(col));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) if (G[i][j] == '*') {
			row[i]++; col[j]++;
		}
	}

	M = 0;
	for (int i = 1; i <= N; i++)
		M = max(M, max(row[i], col[i]));
}

void solve () {
	memset(in, 0, sizeof(in));
	for (int i = 1; i <= N; i++) {
		g[i].clear();
		for (int j = 1; j <= N; j++) if (G[i][j] == '*') {
			g[i].push_back(j);
			in[j]++;
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N && g[i].size() < M; j++) {
			while (in[j] < M && g[i].size() < M) {
				g[i].push_back(j);
				in[j]++;
			}
		}
	}

	for (int c = 1; c <= M; c++) {
		KM();
		for (int i = 1; i <= N; i++) {
			int u = L[i];
			if (G[u][i] == '*') ans[u][i] = c;
			for (int j = 0; g[u].size(); j++) if (g[u][j] == i) {
				g[u].erase(g[u].begin() + j);
				break;
			}
		}
	}

	printf("%d\n", M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			printf("%d%c", ans[i][j], j == N ? '\n' : ' ');
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
