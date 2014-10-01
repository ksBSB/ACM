#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn =50005;

int N, M;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], V[maxn << 2];
int L[maxn << 2], R[maxn << 2], S[maxn << 2];

void maintain(int u, int v) {
	V[u] = v;
	int len = rc[u] - lc[u] + 1;
	L[u] = R[u] = S[u] = (v ? 0 : len);
}

void pushup (int u) {
	S[u] = max(max(S[lson(u)], S[rson(u)]), R[lson(u)] + L[rson(u)]);
	L[u] = L[lson(u)] + (L[lson(u)] == rc[lson(u)] - lc[lson(u)] + 1 ? L[rson(u)] : 0);
	R[u] = R[rson(u)] + (R[rson(u)] == rc[rson(u)] - lc[rson(u)] + 1 ? R[lson(u)] : 0);
}

void pushdown (int u) {
	if (V[u] != -1) {
		maintain(lson(u), V[u]);
		maintain(rson(u), V[u]);
		V[u] = -1;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	V[u] = -1;

	if (l == r) {
		V[u] = 0;
		L[u] = R[u] = S[u] = 1;
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l , mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int v) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, v);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, v);
	if (r > mid)
		modify(rson(u), l, r, v);
	pushup(u);
}

int query (int u, int k) {
	if (S[u] < k)
		return 0;

	pushdown(u);
	int ret;

	if (S[lson(u)] >= k)
		ret = query(lson(u), k);
	else if (R[lson(u)] + L[rson(u)] >= k) {
		int mid = (lc[u] + rc[u]) / 2;
		ret = mid - R[lson(u)] + 1;
	} else
		ret = query(rson(u), k);
	pushup(u);
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		int x, l, r;
		build(1, 1, N);
		while (M--) {
			scanf("%d", &x);
			
			if (x == 1) {
				scanf("%d", &r);
				l = query(1, r);
				printf("%d\n", l);
				if (l)
					modify(1, l, l + r - 1, 1);
			} else {
				scanf("%d%d", &l, &r);
				modify(1, l, l + r - 1, 0);
			}
		}
	}
	return 0;
}
