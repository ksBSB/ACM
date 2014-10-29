#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 20005;
const int sigma_size = 26;

struct Tire {
    int sz;
    int g[maxn][sigma_size];
    int val[maxn];

    void init();
    int idx(char ch);
    void insert(char* s);
	void find(char* s);
}T;

int N;
char w[1005][25];

int main () {
	N = 0;
	T.init();

	while (scanf("%s", w[N]) == 1)
		T.insert(w[N++]);

	for (int i = 0; i < N; i++) {
		printf("%s ", w[i]);
		T.find(w[i]);
		printf("\n");
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

void Tire::find(char* s) {
	int u = 0, n = strlen(s);

	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		u = g[u][v];
		printf("%c", s[i]);
		if (val[u] == 1)
			return;
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
