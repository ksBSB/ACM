#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 1005;
const int sigma_size = 4;
const int inf = 0x3f3f3f3f;
const char sign[5] = "ACGT";

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

	int dp[maxn][maxn];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int x, int y);
	int solve(char* s);
}AC;

int N;
char s[maxn];

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		AC.init();
		for (int i = 0; i < N; i++) {
			scanf("%s", s);
			AC.insert(s, i+1);
		}
		scanf("%s", s);
		printf("Case %d: %d\n", cas++, AC.solve(s));
	}
	return 0;
}

int Aho_Corasick::solve(char* s) {
	getFail();

	int n = strlen(s);
	memset(dp, inf, sizeof(dp));
	dp[0][0] = 0;

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < sz; i++) {
			if (dp[k][i] == inf || tag[i] || last[i])
				continue;

			for (int j = 0; j < 4; j++) {
				int u = i;
				while (u && g[u][j] == 0)
					u = fail[u];
				u = g[u][j];

				int d = (sign[j] == s[k] ? 0 : 1);
				if (dp[k+1][u] > dp[k][i] + d)
					dp[k+1][u] = dp[k][i] + d;
			}
		}
	}

	int ans = inf;
	for (int i = 0; i < sz; i++) {
		if (tag[i] || last[i])
			continue;
		ans = min(ans, dp[n][i]);
	}
	return ans == inf ? -1 : ans;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	if (ch == 'A')
		return 0;
	if (ch == 'C')
		return 1;
	if (ch == 'G')
		return 2;
	return 3;
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
	tag[u] = 1;
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
			last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}
