#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const int sigma_size = 128;

struct Aho_Corasick {
    int sz,  g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];
	int vis[505];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int u);
	int solve(int id);
}A;

int N, Q;
char s[10005];

int main () {
	while (scanf("%d", &N) == 1) {
		A.init();
		for (int i = 1; i <= N; i++) {
			scanf("%s", s);
			A.insert(s, i);
		}
		A.getFail();

		int cnt = 0;
		scanf("%d", &Q);
		for (int i = 1; i <= Q; i++) {
			scanf("%s", s);
			A.match(s);
			if (A.solve(i))
				cnt++;
		}
		printf("total: %d\n", cnt);
	}
	return 0;
}

int Aho_Corasick::solve(int id) {
	int n = 0, arr[10];
	for (int i = 1; i <= N; i++)
		if (vis[i])
			arr[n++] = i;

	if (n) {
		printf("web %d:", id);
		for (int i = 0; i < n; i++)
			printf(" %d", arr[i]);
		printf("\n");
	}
	return n;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch;
}

void Aho_Corasick::put(int u) {
	vis[tag[u]] = 1;
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
	tag[u] = k;
}

void Aho_Corasick::match(char* str) {
	memset(vis, 0, sizeof(vis));

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
