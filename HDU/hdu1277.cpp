#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 10000 * 60;
const int maxm = 10005;
const int sigma_size = 10;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

	int vis[maxm], jump[maxm];
	int c, ans[maxm];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int u);
	void solve(char* s);
}AC;

int N, M;
char s[60005], w[105];

int main () {
	while (scanf("%d%d", &M, &N) == 2) {
		AC.init();
		int mv = 0;
		for (int i = 0; i < M; i++) {
			scanf("%s", s+mv);
			mv += strlen(s+mv);
		}

		for (int i = 1; i <= N; i++) {
			scanf("%*s%*s%*s%s", w);
			AC.insert(w, i);
		}
		AC.solve(s);
	}
	return 0;
}

void Aho_Corasick::solve(char* s) {
	c = 0;
	getFail();
	match(s);

	if (c) {
		printf("Found key:");
		for (int i = 0; i < c; i++)
			printf(" [Key No. %d]", ans[i]);
		printf("\n");
	} else
		printf("No key can be found !\n");
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch - '0';
}

void Aho_Corasick::put(int u) {
	int p = tag[u];
	while (p && vis[p] == 0) {
		vis[p] = 1;
		ans[c++] = p;
		p = jump[p];
	}
	if (last[u])
		put(last[u]);
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
	jump[k] = tag[u];
	tag[u] = k;
}

void Aho_Corasick::match(char* str) {
	int n = strlen(str), u = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		while (u && g[u][v] == 0)
			u = fail[u];

		u = g[u][v];

		if (tag[u])
			put(u);
		else if (last[u])
			put(last[u]);
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
