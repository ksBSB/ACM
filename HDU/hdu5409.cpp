#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5; // The number of Node
const int maxm = 1e5 + 5; // The number of Edge
/* 如果要求边双联通分量，只需在做一遍dfs，保证不经过割边即可。*/

int dfsclock, pre[maxn], cntbcc, bccno[maxn];
bool iscut[maxm<<1];
int first[maxn], jump[maxm<<1], linker[maxm<<1], tag[maxm<<1];

int dfs (int u, int fa) {  
    int lowu = pre[u] = ++dfsclock;
    for (int i = first[u]; i != -1; i = jump[i]) { 
        int v = linker[i];
        if (!pre[v]) {
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if (lowv > pre[u]) 
                iscut[i] = iscut[i^1] = 1;
        } else if (pre[v] < pre[u] && v != fa)
            lowu = min(lowu, pre[v]);
    }
    return lowu;
} 

void dfs (int u) {
    bccno[u] = cntbcc;

    for (int i = first[u]; i + 1; i = jump[i]) {
        if (iscut[i]) continue;
        int v = linker[i];
        if (!bccno[v]) dfs(v);
    }
}

void findEdge (int n) {
    dfsclock = 0;
    memset(pre, 0, sizeof(pre));
    memset(iscut, 0, sizeof(iscut));
    for (int i = 1; i <= n; i++)
        if (!pre[i]) dfs(i, -1);

    cntbcc = 0;
    memset(bccno, 0, sizeof(bccno));
    for (int i = 1; i <= n; i++)
        if (!bccno[i]) { cntbcc++; dfs(i); }
} 

int N, M, E, L[maxm], R[maxm];

void addEdge(int u, int v, int k) {
	jump[E] = first[u];
	linker[E] = v;
	tag[E] = k;
	first[u] = E++;
}

void init () {
	scanf("%d%d", &N, &M);
	E = 0;
	memset(first, -1, sizeof(first));

	int u, v;
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &L[i], &R[i]);
		addEdge(L[i], R[i], 0);
		addEdge(R[i], L[i], 0);
	}

	findEdge(N);
}

int idx[maxn], ans[maxm];

int get(int u, int fa, int id) {
	int ret = idx[u];

	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = linker[i];
		if (v == fa) continue;
		ret = max(get(v, u, tag[i]), ret);
	}

	if (id != -1) ans[id] = ret;
	return ret;
}

void solve () {

	memset(idx, 0, sizeof(idx));
	for (int i = 1; i <= N; i++)
		idx[bccno[i]] = max(idx[bccno[i]], i);

	int s;
	for (int i = 1; i <= cntbcc; i++) if (idx[i] == N) s = i;

	E = 0;
	memset(first, -1, sizeof(first));
	for (int i = 0; i < M; i++) if (iscut[i<<1]) {
		addEdge(bccno[L[i]], bccno[R[i]], i);
		addEdge(bccno[R[i]], bccno[L[i]], i);
	}

	memset(ans, 0, sizeof(ans));
	get(s, 0, -1);
	for (int i = 0; i < M; i++) {
		if (iscut[i<<1]) printf("%d %d\n", ans[i], ans[i] + 1);
		else printf("0 0\n");
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
    return 0;
}
