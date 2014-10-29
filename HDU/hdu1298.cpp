#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const int maxm = 105;
const int sigma_size = 26;
const char dir[15][10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

struct Tire {
	int sz, g[maxn][sigma_size], val[maxn];

	void init();
	int idx(char ch);
	void insert(char *s, int x);
}T;

int N, Q, c[maxm];
char ans[maxm][maxm], w[maxm], r[maxm];

void dfs (int d, int u) {
	if (d) {
		if (T.val[u] > c[d]) {
			c[d] = T.val[u];
			strncpy(ans[d], r, d);
		}
	}

	if (w[d] == 0 || w[d] == '1')
		return;

	int x = w[d] - '0';
	for (int i = 0; dir[x][i]; i++) {
		int v = dir[x][i] - 'a';
		if (T.g[u][v] == 0)
			continue;
		r[d] = dir[x][i];
		dfs(d + 1, T.g[u][v]);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		T.init();
		scanf("%d", &N);

		int x;
		for (int i = 0; i < N; i++) {
			scanf("%s%d", w, &x);
			T.insert(w, x);
		}

		printf("Scenario #%d:\n", kcas);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%s", w);
			memset(c, 0, sizeof(c));

			dfs(0, 0);
			for (int x = 1; w[x-1] != '1'; x++) {
	//			printf("<%c> %d:", w[x], c[x]);
				if (c[x] == 0)
					printf("MANUALLY\n");
				else {
					for (int j = 0; j < x; j++)
						printf("%c", ans[x][j]);
					printf("\n");
				}
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}

void Tire::init() {
	sz = 1;
	val[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx(char ch) {
	return ch - 'a';
}

void Tire::insert(char* s, int x) {
	int u = 0, n = strlen(s);
	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (g[u][v] == 0) {
			g[u][v] = sz;
			memset(g[sz], 0, sizeof(g[sz]));
			val[sz++] = 0;
		}
		u = g[u][v];
		val[u] += x;
	}
}
