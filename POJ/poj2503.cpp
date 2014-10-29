#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e6+5;
const int maxm = 105;
const int sigma_size = 26;

struct Tire {
    int sz;
    int g[maxn][sigma_size];
    int val[maxn];

    void init();
    int idx(char ch);
    void insert(char* s, int x);
	int find(char* s);
}T;

int N;
char w[100005][maxm], op[maxm], s[maxm];

int main () {
	
	T.init();
	strcpy(w[0], "eh");
	while (gets(op) && strcmp(op, "")) {
		sscanf(op, "%s%s", w[++N], s);
		T.insert(s, N);
	}

	while (gets(op)) {
		int x = T.find(op);
		printf("%s\n", w[x]);
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
	val[u] = x;;
}
