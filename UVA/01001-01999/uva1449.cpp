#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

const int maxn = 155;
const int maxl = 100;
const int maxt = 1e6+5;
const int sigma_size = 26;
const int noden = maxn * maxl;

char str[maxt], word[maxn][maxl];
map<string, int> ms;
int N, c[maxn];
int sz, ac[noden][sigma_size], val[noden];
int fail[noden], last[noden];

void insert (int x, char* s) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = s[i] - 'a';
		if (ac[u][v] == 0) {
			memset(ac[sz], 0, sizeof(ac[sz]));
			val[sz] = 0;
			ac[u][v] = sz++;
		}
		u = ac[u][v];
	}
	val[u] = x;
}

void get_fail () {
	queue<int> que;
	fail[0] = 0;

	for (int i = 0; i < sigma_size; i++) {
		int u = ac[0][i];
		if (u) {
			fail[u] = last[u] = 0;
			que.push(u);
		}
	}

	while (!que.empty()) {
		int r = que.front();
		que.pop();

		for (int i = 0; i < sigma_size; i++) {
			int u = ac[r][i];

			if (u == 0) {
				ac[r][i] = ac[fail[r]][i];
				continue;
			}

			que.push(u);
			int v = fail[r];
			while (v && !ac[v][i])
				v = fail[v];

			fail[u] = ac[v][i];
			last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}

void count (int x) {
	if (x) {
		c[val[x]]++;
		count(last[x]);
	}
}

void find (char* T) {
	int u = 0;
	int n = strlen(T);

	for (int i = 0; i < n; i++) {
		int v = T[i] - 'a';
		/*
		while (u && !ac[u][v])
			u = fail[u];
			*/
		u = ac[u][v];
		if (val[u])
			count(u);
		else
			count(last[u]);
	}
}

void init () {
	sz = 1;
	ms.clear();
	memset(ac[0], 0, sizeof(ac[0]));

	for (int i = 1; i <= N; i++) {
		scanf("%s", word[i]);
		insert(i, word[i]);
		ms[string(word[i])] = i;
	}

	memset(c, 0, sizeof(c));
	get_fail();
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();
		scanf("%s", str);
		find(str);

		int ans = -1;
		for (int i = 1; i <= N; i++)
			ans = max(ans, c[i]);
		printf("%d\n", ans);
		for (int i = 1; i <= N; i++) {
			if (c[ms[string(word[i])]] == ans)
				printf("%s\n", word[i]);
		}
	}
	return 0;
}
