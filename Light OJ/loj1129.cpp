#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10005;
const int sigma_size = 10;

struct Tire {
    int sz;
    int g[maxn * 10][sigma_size];
    int val[maxn * 10];

    void init();
    int idx(char ch);
    void insert(char* s);
	int find(char* s);
}T;

int N;
char w[maxn][15];

bool judge () {
	for (int i = 0; i < N; i++) {
		if (T.find(w[i]))
			return false;
	}
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		T.init();
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%s", w[i]);
			T.insert(w[i]);
		}

		printf("Case %d: %s\n", kcas, judge() ? "YES" : "NO");
	}
	return 0;
}

void Tire::init() {
    sz = 1;
    val[0] = 0;
    memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx (char ch) {
    return ch - '0';
}

int Tire::find(char* s) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (val[u])
			return 1;
		u = g[u][v];
	}
	return 0;
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
