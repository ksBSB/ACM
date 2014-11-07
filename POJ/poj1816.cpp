#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int maxn = 100000 * 6 + 5;
const int sigma_size = 28;

struct Tire {
    int sz;
    int g[maxn][sigma_size];
    int val[maxn];

    void init();
    int idx(char ch);
    void insert(char* s, int x);
	int find(char* s);
}T;

int N, M, L, F[maxn];
char W[30];
set<int> ans;

void dfs (int u, int p) {

	if (T.val[u] && p == L) {
		int k = T.val[u];
		while (k) {
			ans.insert(k - 1);
			k = F[k];
		}
	}


	if (T.g[u][27]) {
		for (int i = p; i <= L; i++)
			dfs(T.g[u][27], i);
	}

	if (p == L)
		return;

	if (T.g[u][26])
		dfs(T.g[u][26], p + 1);

	int v = W[p] - 'a';
	if (T.g[u][v])
		dfs(T.g[u][v], p + 1);
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		T.init();
		for (int i = 1; i <= N; i++) {
			scanf("%s", W);
			T.insert(W, i);
		}

		for (int i = 1; i <= M; i++) {
			scanf("%s", W);
			L = strlen(W);
			ans.clear();
			dfs(0, 0);

			if (ans.size()) {
				set<int>::iterator iter = ans.begin();
				printf("%d", *iter);
				for (iter++; iter != ans.end(); iter++)
					printf(" %d", *iter);
				printf("\n");
			} else
				printf("Not match\n");
		}
	}
	return 0;
}

void Tire::init() {
	sz = 1;
	val[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx (char ch) {
	if (ch == '?')
		return 26;
	if (ch == '*')
		return 27;
	return ch - 'a';
}

int Tire::find(char* s) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (g[u][v] == 0)
			return 0;
		u = g[u][v];
	}
	return val[u];
}

void Tire::insert(char* s, int x) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (g[u][v] == 0) {
			val[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}

		u = g[u][v];
	}
	F[x] = val[u];
	val[u] = x;
}
