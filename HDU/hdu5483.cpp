#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 3005;
const int inf = 0x3f3f3f3f;

struct Edge {
	int u, v, w;
	Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) {}
	bool operator < (const Edge& a) const { return w < a.w; }
};

int N, F[maxn], W[maxn], T[maxn];
int E, first[maxn], jump[maxn<<1], linker[maxn<<1], idx[maxn<<1];
vector<Edge> S;
vector<int> D[maxn];

void addEdge(int u, int v, int w) {
	jump[E] = first[u];
	linker[E] = v;
	idx[E] = w;
	first[u] = E++;
}

int find (int x) { return x == F[x] ? x : F[x] = find(F[x]); }

void set(int u, int v, int w) {
	if (u > v) swap(u, v);
	D[u][v-u-1] = w;
}

int get (int u, int v) {
	if (u > v) swap(u, v);
	return D[u][v-u-1];
}

void init () {
	S.clear();
	scanf("%d", &N);

	int x;
	for (int i = 0; i < N; i++) {
		D[i].clear();
		for (int j = 1; j < N-i; j++) {
			scanf("%d", &x);
			D[i].push_back(x);
			S.push_back(Edge(i, i+j, x));
		}
	}
}

void miniTree () {
	E = 0;
	memset(first, -1, sizeof(first));
	for (int i = 0; i < N; i++) F[i] = i;

	int n = N;
	sort(S.begin(), S.end());
	for (int i = 0; i < S.size(); i++) {
		int u = S[i].u, v = S[i].v;
		if (find(u) != find(v)) {
			F[find(u)] = find(v);
			addEdge(u, v, n);
			addEdge(v, u, n);

			set(u, v, inf);
			W[n--] = S[i].w;

			if (n == 1) break;
		}
	}
}

int dfs (int u, int fa, int rt, int id, int w) {
//	printf("rt=%d fa=%d u=%d %d %d\n", rt, fa, u, id, w);
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = linker[i];
		if (v == fa) continue;
		w = min(w, dfs(v, u, rt, idx[i], get(rt, v)));
	}
	T[id] = min(T[id], w);
	return w;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		miniTree();
		for (int i = 1; i <= N; i++) T[i] = inf;
		for (int i = 0; i < N; i++) dfs(i, i, i, 1, inf);

		int ans = 0;
		for (int i = 2; i <= N; i++) {
			if (T[i] != W[i]) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
