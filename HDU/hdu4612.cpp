#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 200005;
const int maxm = 1000005;

int N, M, E, first[maxn], jump[maxm<<1], linker[maxm<<1];
int dfsclock, L[maxm], R[maxm], iscut[maxm], pre[maxn];

int dfs (int u, int fa) {
	int lowu = pre[u] = ++dfsclock;
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = linker[i];
		if (!pre[v]) {
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv);
			if (lowv > pre[u])
				iscut[i>>1] = 1;
		} else if (pre[v] < pre[u] && v != fa)
			lowu = min(lowu, pre[v]);
	}
	return lowu;
}

void dfs (int u, int fa, int be) {
	pre[u] = be;
	for (int i = first[u]; i + 1; i = jump[i]) {
		int v = linker[i];
		if (pre[v] || iscut[i>>1]) continue;
		dfs(v, u, be);
	}
}

void findEdge () {
	dfsclock = 0;
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	for (int i = 1; i <= N; i++)
		if (!pre[i]) dfs(i, -1);

	dfsclock = 0;
	memset(pre, 0, sizeof(pre));
	for (int i = 1; i <= N; i++)
		if (!pre[i]) dfs(i, -1, ++dfsclock);
}

void addEdge(int u, int v) {
	jump[E] = first[u];
	linker[E] = v;
	first[u] = E++;
}

void init () {
	E = 0;
	memset(first, -1, sizeof(first));

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &L[i], &R[i]);
		addEdge(L[i], R[i]);
		addEdge(R[i], L[i]);
	}
	findEdge();
}

const int inf = 0x3f3f3f3f;
int D[maxn];

int solve () {
	int n = dfsclock, u;

	queue<int> que;
	que.push(1);

	memset(D, inf, sizeof(D));
	D[1] = 0;
	while (!que.empty()) {
		u = que.front();
		que.pop();
		for (int i = first[u]; i + 1; i = jump[i]) {
			int v = linker[i];
			if (D[v] > D[u] + 1) {
				D[v] = D[u] + 1;
				que.push(v);
			}
		}
	}

	que.push(u);
	memset(D, inf, sizeof(D));
	D[u] = 0;
	while (!que.empty()) {
		u = que.front();
		que.pop();
		for (int i = first[u]; i + 1; i = jump[i]) {
			int v = linker[i];
			if (D[v] > D[u] + 1) {
				D[v] = D[u] + 1;
				que.push(v);
			}
		}
	}
	return n - D[u] - 1;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2 && N + M) {
		init();

		E = 0;
		memset(first, -1, sizeof(first));
		for (int i = 0; i < M; i++) if (iscut[i]) {
			addEdge(pre[L[i]], pre[R[i]]);
			addEdge(pre[R[i]], pre[L[i]]);
		}
		printf("%d\n", solve());
	}
	return 0;
}
