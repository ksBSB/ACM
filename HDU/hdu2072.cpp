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

int ans;
char op[maxn], w[105];

void solve () {
	ans = 0;
	S.init();

	int len = strlen(op), p = 0;
	for (int i = 0; i <= len; i++) {
		if (op[i] >= 'a' && op[i] <= 'z')
			w[p++] = op[i];
		else {
			if (p == 0)
				continue;

			w[p] = '\0';
			S.insert(w);
			p = 0;
		}
	}
	printf("%d\n", ans);
}

int main () {

	while (gets(op) && strcmp(op, "#"))
		solve();
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
	if (val[u] == 0)
		ans++;
	val[u] = 1;
}
