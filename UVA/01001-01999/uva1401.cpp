#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 105;
const int MOD = 20071027;
const int maxnode = 300000;
const int sigma_size = 30;

struct Trie {
	int sz;
	int val[maxnode];
	int next[maxnode][sigma_size];

	Trie () { clear(); }

	int idx (char ch) {	return ch - 'a'; }
	void clear();
	void insert (char *s, int v);
	bool query (char *s);
}tree;

int dp[maxnode];
char word[maxn], str[maxnode];

void init () {
	int n;
	tree.clear();

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", word);
		tree.insert(word, 1);
	}
}

void solve (int x) {
	int u;
	int& ans = dp[x];
	ans = u = 0;

	for (int i = x; str[i]; i++) {
		int v = str[i] - 'a';

		if (tree.next[u][v] == 0)
			return;
		u = tree.next[u][v];
		if (tree.val[u])
			ans = (ans + dp[i+1]) % MOD;
	}
}

int main () {
	int cas = 1;
	while (scanf("%s", str) == 1) {
		init();
		int n = strlen(str);
		dp[n] = 1;
		for (int i = n-1; i >= 0; i--)
			solve(i);
		printf("Case %d: %d\n", cas++, dp[0]);
	}
	return 0;
}

void Trie::clear () {
	sz = 1;
	memset(next[0], 0, sizeof(next[0]));
}

void Trie::insert (char* s, int v) {
	int u = 0, n = strlen(s);
	for (int i = 0; i < n; i++) {
		int c = idx(s[i]);

		if (next[u][c] == 0) {
			val[sz] = 0;
			memset(next[sz], 0, sizeof(next[sz]));
			next[u][c] = sz++;
		}
		u = next[u][c];
	}
	val[u] = v;
}

bool Trie::query (char* s) {
	int u = 0, n = strlen(s);
	for (int i = 0; i < n; i++) {
		int c = idx(s[i]);

		if (next[u][c] == 0)
			return false;
		u = next[u][c];
	}
	return val[u];
}
