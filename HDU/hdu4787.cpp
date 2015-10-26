#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;
const int sigma_size = 2;

struct Aho_Corasick {
	int cnt, sz, g[maxn][sigma_size], f[maxn][sigma_size];
	int tag[maxn], fail[maxn], last[maxn];

	void init ();
	int idx (char ch) { return ch - '0'; }
	void getFail ();
	void insert (const string& str, int k, int bw);
	int match (const string& str, int bw);
	void mark(int u);
}AC;

const int maxm = 5 * 1e6 + 5;

int N, type[maxn];
string s[maxn];
char str[maxm];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {

		int mv = 0;
		printf("Case #%d:\n", kcas);

		AC.init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%s", str);
			type[i] = str[0] == '+' ? 1 : 0;
			s[i] = (str+1);

			int n = s[i].length();
			if (type[i]) {
				AC.insert(s[i], 1, mv % n);
			} else {
				AC.getFail();
				if (n) mv = AC.match(s[i], mv % n);
				else mv = 0;
				printf("%d\n", mv);
			}
		}
	}
	return 0;
}

void Aho_Corasick::init () {
	sz = 1;
	tag[0] = 0;
	memset(f[0], 0, sizeof(f[0]));
}

void Aho_Corasick::mark (int u) {
	if (u && tag[u]) cnt++;
	if (last[u]) mark(last[u]);
}

void Aho_Corasick::insert (const string& str, int k, int bw) {
	int u = 0, n = str.length();
	for (int i = 0; i < n; i++) {
		int v = idx(str[(i+bw) % n]);
		if (f[u][v] == 0) {
			tag[sz] = 0;
			memset(f[sz], 0, sizeof(f[sz]));
			f[u][v] = sz++;
		}
		u = f[u][v];
	}
	tag[u] += k;
}

int Aho_Corasick::match(const string& str, int bw) {
	int n = str.length(), u = 0;
	cnt = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(str[(i+bw)%n]);
		while (u && g[u][v] == 0) u = fail[u];
		u = g[u][v];

		if (tag[u]) mark(u);
		else if (last[u]) mark(last[u]);
	}
	return cnt;
}

void Aho_Corasick::getFail() {
	memcpy(g, f, sizeof(f));
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
			while (v && g[v][i] == 0) v = fail[v];
			fail[u] = g[v][i];
			last[u] = tag[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}
