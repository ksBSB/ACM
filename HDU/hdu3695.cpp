#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 250000;
const int sigma_size = 26;

struct Aho_Corasick {
    int sz, g[maxn][sigma_size];
    int tag[maxn], fail[maxn], last[maxn];

	int vis[300], jump[300];

    void init();
    int idx(char ch);
    void insert(char* str, int k);
	void getFail();
	void match(char* str);
	void put(int u);
	int solve(char* s);
}AC;

int N;
char w[1005], s[5100005];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		AC.init();
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%s", w);
			AC.insert(w, i);
		}

		int mv = 0, x;
		char ch;
		getchar();
		while(ch = getchar(), ch != '\n') {
			if (ch == '[') {
				scanf("%d%c", &x, &ch);
				for (int i = 0; i < x; i++)
					s[mv++] = ch;
				getchar();
			} else
				s[mv++] = ch;
		}
		s[mv] = '\0';

		printf("%d\n", AC.solve(s));
	}
	return 0;
}

int Aho_Corasick::solve(char* s) {
	memset(vis, 0, sizeof(vis));

	AC.getFail();
	AC.match(s);
	reverse(s, s + strlen(s));
	AC.match(s);

	int ans = 0;
	for (int i = 1; i <= N; i++)
		if (vis[jump[i]])
			ans++;
	return ans;
}

void Aho_Corasick::init() {
	sz = 1;
	tag[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch - 'A';
}

void Aho_Corasick::put(int u) {
	if (vis[tag[u]])
		return;

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
	if (tag[u] == 0)
		tag[u] = k;
	jump[k] = tag[u];
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
