#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1e5+5;
const int sigma_size = 26;
const int inf = 0x3f3f3f3f;

struct Aho_Corasick {
	int sz, g[maxn * 6][sigma_size];
	int tag[maxn * 6], jump[maxn];
	int len[maxn], dis[maxn], c[maxn][2];
	int fail[maxn * 6], last[maxn * 6];

	void init();
	int idx(char ch);
	void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int d, int u);
}AC;

int N, vis[maxn];
char s[maxn];

int main () {
	char w[10];
	int cas = 1, x;

	while (scanf("%s", s) == 1) {
		AC.init();
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d%s", &vis[i], w);
			AC.insert(w, i);
		}
		AC.getFail();
		AC.match(s);

		printf("Case %d\n", cas++);
		for (int i = 1; i <= N; i++)
			printf("%d\n", AC.c[AC.jump[i]][vis[i]]);
		printf("\n");
	}
	return 0;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));

	memset(c, 0, sizeof(c));
	memset(dis, -1, sizeof(dis));
}

int Aho_Corasick::idx(char ch) {
	return ch - 'a';
}

void Aho_Corasick::put(int d, int u) {
	int p = tag[u];
	if (dis[p] == -1 || d - dis[p] >= len[p]) {
		dis[p] = d;
		c[p][1]++;
	}
	c[p][0]++;

	if (last[u])
		put(d, last[u]);
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

	len[k] = n;
	if (tag[u])
		jump[k] = tag[u];
	else
		jump[k] = tag[u] = k;
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
