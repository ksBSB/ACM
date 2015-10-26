#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)
const int maxn = 50000;

int lc[maxn<<2], rc[maxn<<2], s[maxn<<2];

void pushup(int u) { s[u] = max(s[lson(u)], s[rson(u)]); }

void build(int u, int l, int r) {
	lc[u] = l, rc[u] = r, s[u] = 0;

	if (l == r) return;
	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid+1 , r);
	pushup(u);
}

void modify(int u, int p, int v) {
	if (lc[u] == rc[u]) {
		s[u] = max(s[u], v);
		return;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (p <= mid) modify(lson(u), p, v);
	else modify(rson(u), p, v);
	pushup(u);
}

int query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	int mid = (lc[u] + rc[u]) >> 1, ret = 0;
	if (l <= mid) ret = max(ret, query(lson(u), l, r));
	if (r > mid) ret = max(ret, query(rson(u), l, r));
	return ret;
}

struct State {
	int l, r, id;
	State(int l = 0, int r = 0, int id = 0):l(l), r(r), id(id) {}
	bool operator < (const State& u) const { return r < u.r; }
}Q[maxn + 5];

int N, M, A[maxn + 5], P[maxn + 5], ans[maxn + 5];
vector<int> G[maxn + 5];

void init () {
	scanf("%d", &N);
	memset(P, 0, sizeof(P));
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);

	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &Q[i].l, &Q[i].r);
		Q[i].id = i;
	}
	sort(Q, Q + M);
	build(1, 0, N);
}

int main () {
	for (int i = 1; i <= maxn; i++)
		for (int j = i; j <= maxn; j += i)
			G[j].push_back(i);

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();

		int p = 0;
		for (int i = 1; i <= N; i++) {
			int u = A[i];

			for (int j = 0; j < G[u].size(); j++) {
				int v = G[u][j];
				modify(1, P[v], v);
				P[v] = i;
			}
			while (p < M && Q[p].r == i) {
				ans[Q[p].id] = query(1, Q[p].l, Q[p].r);
				p++;
			}
		}
		for (int i = 0; i < M; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
