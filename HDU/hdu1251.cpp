#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1000005;
const int sigma_size = 26;

struct Tire {
    int sz;
    int g[maxn][sigma_size];
    int val[maxn];

    void init();
    int idx(char ch);
    void insert(char* s);
	int find(char* s);
}S;

char op[maxn];

int main () {
	S.init();
	while (gets(op), strcmp(op, ""))
		S.insert(op);
	while (gets(op))
		printf("%d\n", S.find(op));
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
		val[u]++;
	}
}
