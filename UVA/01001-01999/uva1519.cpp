#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 400005;
const int sigma_size = 26;
typedef long long ll;

struct Tire {
	int sz, g[maxn][sigma_size];
	int c[sigma_size];

	void init ();
	int idx(char ch);
	void insert(char* s);
}pre, suf;

int main () {
	int N;
	while (scanf("%d", &N) == 1 && N) {
		char word[45];
		int vis[sigma_size];
		memset(vis, 0, sizeof(vis));

		pre.init();
		suf.init();

		for (int i = 0; i < N; i++) {
			scanf("%s", word);

			int n = strlen(word);
			if (n == 1)
				vis[word[0] - 'a'] = 1;

			pre.insert(word);
			reverse(word, word + n);
			suf.insert(word);
		}

		ll ans = (ll)(pre.sz - 1) * (suf.sz - 1);
		for (int i = 0; i < sigma_size; i++)
			ans -= (ll)pre.c[i] * suf.c[i] - vis[i];
		printf("%lld\n", ans);
	}
	return 0;
}

void Tire::init () {
	sz = 1;
	memset(g[0], 0, sizeof(g[0]));
	memset(c, 0, sizeof(c));
}

int Tire::idx (char ch) {
	return ch - 'a';
}

void Tire::insert(char* s) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (g[u][v] == 0) {
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
			if (i)
				c[v]++;
		}

		u = g[u][v];
	}
}
