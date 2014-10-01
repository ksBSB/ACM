#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;

int N, M, a[maxn];

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], filp[maxn << 2];
int L[maxn << 2][2], R[maxn << 2][2], S[maxn << 2][2];

void maintain (int u) {
	filp[u] ^= 1;
	swap(L[u][0], L[u][1]);
	swap(R[u][0], R[u][1]);
	swap(S[u][0], S[u][1]);
}

void pushup(int u) {
	for (int i = 0; i < 2; i++) {
		S[u][i] = max(max(S[lson(u)][i], S[rson(u)][i]), R[lson(u)][i] + L[rson(u)][i]);
		L[u][i] = L[lson(u)][i] + (L[lson(u)][i] == rc[lson(u)] - lc[lson(u)] + 1 ? L[rson(u)][i] : 0);
		R[u][i] = R[rson(u)][i] + (R[rson(u)][i] == rc[rson(u)] - lc[rson(u)] + 1 ? R[lson(u)][i] : 0);
	}
}

void pushdown (int u) {
	if (filp[u]) {
		maintain(lson(u));
		maintain(rson(u));
		filp[u] = 0;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	filp[u] = 0;

	if (l == r) {
		int d = a[l];
		L[u][d] = R[u][d] = S[u][d] = 1;
		L[u][d^1] = R[u][d^1] = S[u][d^1] = 0;
		return ;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid+1, r);
	pushup(u);
}

void modify (int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r);
	if (r > mid)
		modify(rson(u), l, r);
	pushup(u);
}

int query (int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return S[u][1];

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2, ret;
	if (r <= mid)
		ret = query(lson(u), l, r);
	else if (l > mid)
		ret = query(rson(u), l, r);
	else {
		int ll = query(lson(u), l, r);
		int rr = query(rson(u), l, r);

		int a = min(L[rson(u)][1], r - mid);
		int b = min(R[lson(u)][1], mid - l + 1);

		ret = max( max(ll, rr), a + b);
	}
	pushup(u);
	return ret;
}

int main () {
	int x, l, r;

	while (scanf("%d", &N) == 1) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &a[i]);
		build (1, 1, N);

		scanf("%d", &M);
		while (M--) {
			scanf("%d%d%d", &x, &l, &r);
			if (x)
				modify(1, l, r);
			else
				printf("%d\n", query(1, l, r));
		}
	}
	return 0;
}
