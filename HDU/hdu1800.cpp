#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 90005;
const int sigma_size = 10;

struct Tire {
    int sz, ans;
    int g[maxn][sigma_size];
    int val[maxn];

    void init();
    int idx(char ch);
    void insert(char* s);
	int find(char* s);
}T;

int main () {
	int n;
	char w[35];
	while (scanf("%d", &n) == 1) {
		T.init();
		for (int i = 0; i < n; i++) {
			scanf("%s", w);
			int v = 0;
			while (w[v] == '0') v++;
			T.insert(w + v);
		}
		printf("%d\n", T.ans);
	}
	return 0;
}

void Tire::init() {
    sz = 1;
    ans = val[0] = 0;
    memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx (char ch) {
    return ch - '0';
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
	val[u]++;
	ans = max(ans, val[u]);
}
