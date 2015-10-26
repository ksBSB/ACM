#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 1e6 + 5;
const int maxm = 1e7;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

int N, Q, vis[maxm+5], A[maxn];
int lc[maxn<<2], rc[maxn<<2], S[maxn<<2], T[maxn<<2];

void maintain(int u, int k) {
	T[u] = k;
	S[u] = vis[T[u]] == 0 ? rc[u] - lc[u] + 1 : 0;
}
void pushup(int u) { S[u] = S[lson(u)] + S[rson(u)]; }
void pushdown(int u) {
	if (T[u]) {
		maintain(lson(u), T[u]);
		maintain(rson(u), T[u]);
		T[u] = 0;
	}
}

void build (int u, int l, int r) {
	S[u] = T[u] = 0;
	lc[u] = l, rc[u] = r;

	if (l == r) {
		T[u] = A[l];
		S[u] = vis[T[u]] == 0 ? 1 : 0;
		return;
	}

	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid+1, r);
	pushup(u);
}

void add(int u, int x, int k) {
	if (lc[u] == rc[u]) {
		T[u] += k;
		S[u] = vis[T[u]] == 0 ? 1 : 0;
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid) add(lson(u), x, k);
	else add(rson(u), x, k);
	pushup(u);
}

void modify(int u, int l, int r, int k) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, k);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	if (l <= mid) modify(lson(u), l, r, k);
	if (r > mid) modify(rson(u), l, r, k);
	pushup(u);
}

int query (int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return S[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1, ret = 0;
	if (l <= mid) ret += query(lson(u), l, r);
	if (r > mid) ret += query(rson(u), l, r);
	pushup(u);
	return ret;
}

int main () {
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i * i <= maxn; i++) {
		if (vis[i]) continue;
		for (int j = i + i; j <= maxn; j += i)
			vis[j] = 1;
	}

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &Q);
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
		build(1, 1, N);

		char s[5];
		int l, r, v;
		while (Q--) {
			scanf("%s", s);
			if (s[0] == 'A') {
				scanf("%d%d", &v, &l);
				add(1, l, v);
			} else if (s[0] == 'Q') {
				scanf("%d%d", &l, &r);
				printf("%d\n", query(1, l, r));
			} else {
				scanf("%d%d%d", &v, &l, &r);
				modify(1, l, r, v);
			}
		}
	}
	return 0;
}
