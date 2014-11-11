#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int,int> pii;

const int maxn = 205;
const int sigma_size = 4;
const int inf = 0x3f3f3f3f;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

	int dp[maxn][1030];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int x, int y);
	int solve();
}AC;

int N;
char w[30];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		AC.init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%s", w);
			AC.insert(w, i);
		}
		printf("%d\n", AC.solve());
	}
	return 0;
}

int Aho_Corasick::solve() {
	getFail();
	memset(dp, inf, sizeof(dp));
	dp[0][0] = 0;

	queue<pii> que;
	que.push(make_pair(0, 0));

	while(!que.empty()) {
		int u = que.front().first;
		int s = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++) {
			int k = u;
			while (k && g[k][i] == 0)
				k = fail[k];
			k = g[k][i];
			int ss = s | tag[k];
			if (dp[k][ss] > dp[u][s] + 1) {
				dp[k][ss] = dp[u][s] + 1;
				que.push(make_pair(k, ss));
				if (ss == (1<<N)-1)
					return dp[k][ss];
			}
		}
	}
	return 0;
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
	tag[u] |= (1<<k);
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
			tag[u] |= tag[fail[u]];
			//last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}
