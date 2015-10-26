#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)
const int maxn = 50005;

int lc[maxn<<2], rc[maxn<<2], siz[maxn<<2], laz[maxn<<2];

int length(int u) { return rc[u] - lc[u] + 1; }
void maintain(int u, int v) {
	laz[u] = v;
	siz[u] = laz[u] * length(u);
}
void pushup(int u) { siz[u] = siz[lson(u)] + siz[rson(u)]; }
void pushdown(int u) {
	if (laz[u] != -1) {
		maintain(lson(u), laz[u]);
		maintain(rson(u), laz[u]);
		laz[u] = -1;
	}
}

void build (int u, int l, int r) {
	lc[u] = l, rc[u] = r, siz[u] = 0, laz[u] = -1;
	
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid+1, r);
	pushup(u);
}

void modify(int u, int l, int r, int v) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, v);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	if (l <= mid) modify(lson(u), l, r, v);
	if (r > mid) modify(rson(u), l, r, v);
	pushup(u);
}

int query(int u, int l, int r) {
	if (l > r) return 0;
	if (l <= lc[u] && rc[u] <= r)
		return siz[u];
	
	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1, ret = 0;
	if (l <= mid) ret += query(lson(u), l, r);
	if (r > mid) ret += query(rson(u), l, r);
	pushup(u);
	return ret;
}

int find(int u, int k) {
	if (lc[u] == rc[u]) return lc[u];
	pushdown(u);
	int rest = length(lson(u)) - siz[lson(u)], ret;
	if (rest >= k) ret =  find(lson(u), k);
	else ret = find(rson(u), k - rest);
	pushup(u);
	return ret;
}

int N, M;

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		build(1, 0, N-1);

		int k, l, r;
		while (M--) {
			scanf("%d%d%d", &k, &l, &r);
			if (k == 1) {
				int rest = N - l - query(1, l, N-1);
				if (rest == 0)
					printf("Can not put any one.\n");
				else {
					int pre = l - query(1, 0, l-1);
					int posl = find(1, pre + 1);
					int posr = find(1, pre + min(r, rest));
					modify(1, posl, posr, 1);
					printf("%d %d\n", posl, posr);
				}
			} else {
				printf("%d\n", query(1, l, r));
				modify(1, l, r, 0);
			}
		}
		printf("\n");
	}
	return 0;
}
