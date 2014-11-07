#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e6+5;
const int maxc = 1005;
const int sigma_size = 26;
const int dir[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

struct Tire {
    int sz, C;
    int g[maxn][sigma_size];
    int val[maxn];

    void init();
    int idx(char ch);
    void insert(char* s, int x);
	void find(int x, int y, int d);
}T;

int N, M, Q, X[maxc], Y[maxc], D[maxc];
char G[maxc][maxc], W[maxc];

void solve () {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int d = 0; d < 8; d++) {
				T.find(i, j, d);
				if (T.C == 0)
					return;
			}
		}
	}
}

int main () {
	while (scanf("%d%d%d", &N, &M, &Q) == 3) {
		for (int i = 0; i < N; i++)
			scanf("%s", G[i]);

		T.init();
		for (int i = 1; i <= Q; i++) {
			scanf("%s", W);
			T.insert(W, i);
		}

		solve();
		for (int i = 1; i <= Q; i++)
			printf("%d %d %c\n", X[i], Y[i], D[i] + 'A');
	}
	return 0;
}

void Tire::init() {
	C = 0;
	sz = 1;
	val[0] = 0;
	memset(g[0], 0, sizeof(g[0]));
}

int Tire::idx (char ch) {
	return ch - 'A';
}

void Tire::find(int x, int y, int d) {
	int p = x, q = y, u = 0;

	for (int i = 1; i; i++) {
		if (p < 0 || p >= N || q < 0 || q >= M)
			break;
		int v = idx(G[p][q]);

		if (g[u][v] == 0)
			break;

		u = g[u][v];
		p += dir[d][0];
		q += dir[d][1];

		if (val[u]) {
			X[val[u]] = x;
			Y[val[u]] = y;
			D[val[u]] = d;
			C--;
			val[u] = 0;
		}
	}
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
	C++;
	val[u] = x;
}
