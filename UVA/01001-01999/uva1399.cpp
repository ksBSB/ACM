#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 50005;
const int sigma_size = 26;

struct Aho_Corasick {
	int sz, ac[maxn][sigma_size];
	int fail[maxn], last[maxn];

	void init();
	int idx(char ch);
	void insert(char* s);
	void get_fail();
}fuck;

int K, vis[maxn], dp[maxn], jump[maxn];

int dfs (int u) {
	if (vis[u])
		return -1;

	if (dp[u] != -1)
		return dp[u];

	vis[u] = 1;
	int& ret = dp[u];
	jump[u] = -1;
	ret = 0;

	for (int i = K - 1; i >= 0; i--) {
		int v = fuck.ac[u][i];
		if (fuck.last[v] == 0) {
			int tmp = dfs(v);

			if (tmp == -1)
				return -1;

			if (tmp + 1 > ret) {
				ret = tmp + 1;
				jump[u] = i;
			}
		}
	}
	vis[u] = 0;
	return ret;
}

void put_ans (int u) {
	while (jump[u] != -1) {
		printf("%c", 'A' + jump[u]);
		u = fuck.ac[u][jump[u]];
	}
	printf("\n");
}

int main () {
	int cas, n;
	char word[55];

	scanf("%d", &cas);
	while (cas--) {
		fuck.init();
		memset(vis, 0, sizeof(vis));
		memset(dp, -1, sizeof(dp));

		scanf("%d%d", &K, &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", word);
			fuck.insert(word);
		}
		fuck.get_fail();

		if (dfs(0) != -1 && dp[0])
			put_ans(0);
		else
			printf("No\n");
	}
	return 0;
}

void Aho_Corasick::init() {
	sz = 1;
	memset(ac[0], 0, sizeof(ac[0]));
}

int Aho_Corasick::idx(char ch) {
	return ch - 'A';
}

void Aho_Corasick::insert(char* s) {
	int n = strlen(s), u = 0;

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (ac[u][v] == 0) {
			memset(ac[sz], 0, sizeof(ac[sz]));
			last[sz] = 0;
			ac[u][v] = sz++;
		}
		u = ac[u][v];
	}
	last[u] = 1;
}

void Aho_Corasick::get_fail () {
	queue<int> que;
	fail[0] = 0;

	for (int i = 0; i < sigma_size; i++) {
		int u = ac[0][i];
		if (u) {
			fail[u] = 0;
			que.push(u);
		}
	}

	while (!que.empty()) {
		int r = que.front();
		que.pop();

		for (int i = 0; i < K; i++) {
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
			last[u] |= last[fail[u]];
		}
	}
}
