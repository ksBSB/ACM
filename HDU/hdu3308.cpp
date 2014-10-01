#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;

int N, M, a[maxn];

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2];
int L[maxn << 2], R[maxn << 2], S[maxn << 2];

void pushup (int u) {
	int mid = (lc[u] + rc[u]) / 2;
	S[u] = max(max(S[lson(u)], S[rson(u)]), (a[mid] < a[mid+1] ? R[lson(u)] + L[rson(u)] : 0));
	L[u] = L[lson(u)] + (L[lson(u)] == rc[lson(u)] - lc[lson(u)] + 1 && a[mid] < a[mid + 1] ? L[rson(u)] : 0);
	R[u] = R[rson(u)] + (R[rson(u)] == rc[rson(u)] - lc[rson(u)] + 1 && a[mid] < a[mid + 1] ? R[lson(u)] : 0);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		L[u] = R[u] = S[u] = 1;
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int x, int v) {
	if (lc[u] == x && rc[u] == x) {
		a[x] = v;
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, v);
	else
		modify(rson(u), x, v);
	pushup(u);
}

int query (int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return S[u];

	int mid =(lc[u] + rc[u]) / 2, ret;
	if (r <= mid)
		ret = query(lson(u), l, r);
	else if (l > mid)
		ret = query(rson(u), l, r);
	else {
		int ll = query(lson(u), l, r);
		int rr = query(rson(u), l, r);

		int A = min(R[lson(u)], mid - l + 1);
		int B = min(L[rson(u)], r - mid);

		ret = max(max(ll, rr), a[mid] < a[mid + 1] ? A + B : 0);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf("%d", &a[i]);

		build(1, 0, N-1);

		int l, r;
		char op[5];
		while (M--) {
			scanf("%s%d%d", op, &l, &r);
			if (op[0] == 'U')
				modify(1, l, r);
			else
				printf("%d\n", query(1, l, r));
		}
	}
	return 0;
}
