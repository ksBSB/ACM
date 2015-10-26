//#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <algorithm>


using namespace std;
const int maxn = 20005;
const int inf = 0x3f3f3f3f;

int N, M, E, first[maxn], jump[maxn<<1], link[maxn<<1], C[maxn];
int id, idx[maxn], dep[maxn], top[maxn], far[maxn], son[maxn], cnt[maxn];

inline void addEdge(int u, int v) {
	link[E] = v;
	jump[E] = first[u];
	first[u] = E++;
}

void dfs (int u, int pre, int d) {
	far[u] = pre;
	dep[u] = d;
	cnt[u] = 1;
	son[u] = 0;

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == pre) continue;
		dfs(v, u, d + 1);
		cnt[u] += cnt[v];
		if (cnt[son[u]] < cnt[v])
			son[u] = v;
	}
}

void dfs (int u, int rot) {
	top[u]= rot;
	idx[u] = ++id;
	if (son[u])
		dfs(son[u], rot);

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = link[i];
		if (v == far[u] || v == son[u]) continue;
		dfs(v, v);
	}
}

void init () {
	int u, v;
	id = E = 0;
	memset(first, -1, sizeof(first));

	scanf("%d%d", &N, &M);
	for (int i = 1; i < N; i++) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
		addEdge(v, u);
	}

	dfs(1, 0, 0);
	dfs(1, 1);
}

void modify (int u, int v) {
	int p = top[u], q = top[v];
	while (p != q) {
		if (dep[p] < dep[q]) {
			swap(p, q);
			swap(u, v);
		}

		C[idx[p]]++;
		C[idx[u]+1]--;

		u = far[p];
		p = top[u];
	}

	if (dep[u] > dep[v])
		swap(u, v);

	C[idx[son[u]]]++;
	C[idx[v]+1]--;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		int u, v;
		memset(C, 0, sizeof(C));
		for (int i = N; i <= M; i++) {
			scanf("%d%d", &u, &v);
			modify(u, v);
		}

		int ans = inf;
		for (int i = 2; i <= N; i++) {
			C[i] += C[i-1];
			ans = min(ans, C[i]);
		}
		printf("Case #%d: %d\n", kcas, ans + 1);
	}
	return 0;
}
