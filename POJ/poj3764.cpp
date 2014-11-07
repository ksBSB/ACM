#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100005 * 32;
const int sigma_size = 2;

struct Tire {
    int sz;
    int g[maxn][sigma_size];

    void init();
    int idx(char ch);
    void insert(int s);
	int find(int s);
}T;

int N, M, E, first[maxn], jump[maxn], link[maxn], val[maxn], rec[maxn];

inline void add_Edge (int u, int v, int w) {
	link[E] = v;
	val[E] = w;
	jump[E] = first[u];
	first[u] = E++;
}

void dfs (int u, int pre, int s) {
	T.insert(s);
	rec[M++] = s;
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == pre)
			continue;
		dfs(v, u, s ^ val[i]);
	}
}

int main () {
	while (scanf("%d", &N) == 1) {
		M = E = 0;
		T.init();
		memset(first, -1, sizeof(first));

		int u, v, w;
		for (int i = 1; i < N; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_Edge(u, v, w);
			add_Edge(v, u, w);
		}
		dfs(0, 0, 0);

		int ans = 0;
		for (int i = 0; i < M; i++)
			ans = max(ans, T.find(rec[i]));
		printf("%d\n", ans);
	}
	return 0;
}

void Tire::init() {
    sz = 1;
    memset(g[0], 0, sizeof(g[0]));
}

int Tire::find(int s) {
	int ret = 0, u = 0;
	for (int i = 30; i >= 0; i--) {
		int v = ((s>>i)&1) ^ 1;

		if (g[u][v])
			ret |= (1<<i);
		else
			v = v^1;
		u = g[u][v];
	}
	return ret;
}

void Tire::insert(int s) {
    int u = 0;

	for (int i = 30; i >= 0; i--) {
        int v = (s>>i)&1;

        if (g[u][v] == 0) {
            memset(g[sz], 0, sizeof(g[sz]));
            g[u][v] = sz++;
        }
        u = g[u][v];
	}
}
