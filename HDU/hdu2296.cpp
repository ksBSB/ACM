#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 2005;
const int sigma_size = 26;
const int inf = 0x3f3f3f3f;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

	int dp[55][maxn];
	char rec[55][maxn][55];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int x, int y);
	void solve();
}A;

int N, M;
char w[105][15];

void init () {
	A.init();

	scanf("%d%d", &N, &M);
	int x;
	for (int i = 0; i < M; i++)
		scanf("%s", w[i]);
	for (int i = 0; i < M; i++) {
		scanf("%d", &x);
		A.insert(w[i], x);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		A.solve();
	}
	return 0;
}

bool cmp(char* a, char* b) {
	int la = strlen(a);
	int lb = strlen(b);

	if (la != lb)
		return la > lb;
	return strcmp(a, b) > 0;
}

void Aho_Corasick::solve() {
	getFail();
	int val = 0;
	char ans[55];
	memset(ans, 0, sizeof(ans));
	memset(rec, 0, sizeof(rec));

	memset(dp, -inf, sizeof(dp));
	dp[0][0] = 0;

	for (int k = 0; k < N; k++) {

		for (int i = 0; i < sz; i++) {
			if (dp[k][i] < 0)
				continue;

			for (int j = 0; j < sigma_size; j++) {
				int u = i;
				while (u && g[u][j] == 0)
					u = fail[u];
				u = g[u][j];

				if (dp[k+1][u] < dp[k][i] + tag[u] || (dp[k+1][u] == dp[k][i] + tag[u] && strcmp(rec[k+1][u], rec[k][i]) > 0)) {
					dp[k+1][u] = dp[k][i] + tag[u];
					strcpy(rec[k+1][u], rec[k][i]);
					rec[k+1][u][k] = j + 'a';

					if (val < dp[k+1][u] || (val == dp[k+1][u] && cmp(ans, rec[k+1][u])) ) {
						val = dp[k+1][u];
						strcpy(ans, rec[k+1][u]);
					}
				}
			}
		}
	}
	printf("%s\n", ans);
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch - 'a';
}

void Aho_Corasick::put(int x, int y) {
}

void Aho_Corasick::insert(char* str, int k) {
	int u = 0, n = strlen(str);

	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		if (g[u][v] == 0) {
			tag[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}
		u = g[u][v];
	}
	//tag[u] = max(tag[u], k);
	tag[u] += k;
}

void Aho_Corasick::match(char* str) {
	int n = strlen(str), u = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		while (u && g[u][v] == 0)
			u = fail[u];

		u = g[u][v];

		if (tag[u])
			put(i, u);
		else if (last[u])
			put(i, last[u]);
	}
}

void Aho_Corasick::getFail() {
	queue<int> que;

	for (int i  = 0; i < sigma_size; i++) {
		int u = g[0][i];
		if (u) {
			fail[u] = last[u] = 0;
			que.push(u);
		}
	}

	while (!que.empty()) {
		int r = que.front();
		que.pop();

		for (int i = 0; i < sigma_size; i++) {
			int u = g[r][i];

			if (u == 0) {
				g[r][i] = g[fail[r]][i];
				continue;
			}

			que.push(u);
			int v = fail[r];
			while (v && g[v][i] == 0)
				v = fail[v];

			fail[u] = g[v][i];
			tag[u] += tag[fail[u]];
			//		last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}
