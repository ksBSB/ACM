#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 1005;
const int maxl = 10005;
const int sigma_size = 127;

char s[maxn][maxn];
int N, M, R, C;

struct Aho_Corasick {
	int sz;
	int ac[maxl][sigma_size];
	int vn[maxl], val[maxl][105];
	int fail[maxl], last[maxl];
	int cnt[maxn][maxn];

	void init ();
	int idx (char ch);

	void insert (int x, char* str);
	void get_fail ();
	void find (int id, int c, char *str);
	void count_ans(int x, int y, int u);
}ac_map;

void init () {
	char word[105];
	scanf("%d%d", &N, &M);

	for (int i = 1; i <= N; i++)
		scanf("%s", s[i]);

	ac_map.init();

	scanf("%d%d", &R, &C);
	for (int i = 1; i <= R; i++) {
		scanf("%s", word);
		ac_map.insert(i, word);
	}
	ac_map.get_fail();
}

int solve () {
	for (int i = 1; i <= N; i++)
		ac_map.find(i, C, s[i]);
	
	int ret = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (ac_map.cnt[i][j] == R)
				ret++;
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}

void Aho_Corasick::init () {
	sz = 1;
	vn[0] = 0;
	memset(ac[0], 0, sizeof(ac[0]));
	memset(cnt, 0, sizeof(cnt));
}

int Aho_Corasick::idx (char ch) {
	return ch;
}

void Aho_Corasick::insert (int x, char* str) {
	int n = strlen(str), u = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);

		if (ac[u][v] == 0) {
			vn[sz] = 0;
			memset(ac[sz], 0, sizeof(ac[sz]));
			ac[u][v] = sz++;
		}
		u = ac[u][v];
	}
	val[u][vn[u]++] = x;
}

void Aho_Corasick::get_fail () {
	fail[0] = 0;
	queue<int> que;

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
			while (v && ac[v][i] == 0)
				v = fail[v];
			fail[u] = ac[v][i];
			last[u] = vn[fail[u]] ? fail[u] : last[fail[u]];
		}
	}
}

void Aho_Corasick::count_ans (int x, int y, int u) {
	if (u) {
		for (int i = 0; i < vn[u]; i++)
			if (x >= val[u][i])
				cnt[x - val[u][i]][y]++;
		count_ans(x, y, last[u]);
	}
}

void Aho_Corasick::find(int x, int y, char* str) { 
	int n = strlen(str), u = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(str[i]);
		u = ac[u][v];

		if (vn[u])
			count_ans(x, i - y + 1, u);
		else if (last[u])
			count_ans(x, i - y + 1, last[u]);
	}
}
