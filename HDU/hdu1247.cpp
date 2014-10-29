#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50005;
const int maxm = 105;
const int sigma_size = 26;

struct Tire {
    int sz;
    int g[maxn * maxm][sigma_size];
    int val[maxn * maxm];

    void init();
    int idx(char ch);
    void insert(char* s);
	int find(char* s);
}S;

char s[maxn][maxm], w[maxm];

int main () {
	S.init();
	int n = 0;

	while (scanf("%s", w) == 1) {
		strcpy(s[n++], w);
		S.insert(w);
	}

	for (int i = 0; i < n; i++) {
		int len = strlen(s[i]);
		for (int j = 1; j < len - 1; j++) {
			strncpy(w, s[i], j);
			w[j] = '\0';
			if (S.find(w) && S.find(s[i]+j)) {
				printf("%s\n", s[i]);
				break;
			}
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

void Tire::insert(char* s) {
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
	val[u] = 1;
}
