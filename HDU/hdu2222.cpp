#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <algorithm>

using  namespace std;
const int maxn = 500005;
const int maxl = 1e6+5;
const int sigma_size = 26;

struct Aho_Corasick {
	int sz, g[maxn][sigma_size];
	int tag[maxn], jump[10005];
	int fail[maxn], last[maxn];
	int ans, vis[10005];

	void init();
	int idx(char ch);
	void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int u);
}A;

char s[maxl], w[55];

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		A.init();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s", w);
			A.insert(w, i);
		}
		A.getFail();
		scanf("%s", s);
		A.match(s);
		printf("%d\n", A.ans);
	}
	return 0;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = jump[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx (char ch) {
	return ch - 'a';
}

void Aho_Corasick::put(int u) {
	int p = tag[u];
	while (p && vis[p] == 0) {
		ans++;
		vis[p] = 1;
		p = jump[p];
	}

	if (last[u])
		put(last[u]);
}

void Aho_Corasick::match(char* str) {
	ans = 0;
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

void Aho_Corasick::insert(char* str, int k) {
	int n = strlen(str), u = 0;
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

void Aho_Corasick::getFail() {
	queue<int> que;

	for (int i = 0; i < sigma_size; i++) {
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
