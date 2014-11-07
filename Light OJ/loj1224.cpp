#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50005 * 50;
const int sigma_size = 4;

struct Tire {
    int sz, ans;
    int g[maxn][sigma_size];
    int val[maxn];

    void init();
    int idx(char ch);
    void insert(char* s);
	void solve(int u, int d);
}T;

int main () {
	int cas;
	scanf("%d", &cas);

	int n;
	char w[105];
	for (int kcas = 1; kcas <= cas; kcas++) {
		T.init();

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", w);
			T.insert(w);
		}

		T.solve(0, 0);
		printf("Case %d: %d\n", kcas, T.ans);
	}
	return 0;
}

void Tire::init() {
    sz = 1;
    ans = val[0] = 0;
    memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx (char ch) {
	if (ch == 'A') return 0;
	else if (ch == 'C') return 1;
	else if (ch == 'G') return 2;
	else return 3;
}

void Tire::solve(int u, int d) {
	ans = max(ans, d * val[u]);

	for (int i = 0; i < 4; i++) {
		if (g[u][i])
			solve(g[u][i], d + 1);
	}
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
