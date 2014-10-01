#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int N, M, a[maxn];

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
struct Node {
	int l, r, filp, set;
	int lc[2], rc[2], sc[2];
	int cnt[2];

	int length() {
		return r - l + 1;
	}
	void maintain(int d) {
		set = d;
		filp = 0;
		for (int i = 0; i < 2; i++)
			lc[i] = rc[i] = sc[i] = cnt[i] = (i == d ? r - l + 1 : 0);
	}
	void splay() {
		if (set != -1)
			set ^= 1;
		else
			filp ^= 1;

		swap(lc[0], lc[1]);
		swap(rc[0], rc[1]);
		swap(sc[0], sc[1]);
		swap(cnt[0], cnt[1]);
	}
}nd[maxn << 2];

void pushup(int u) {
	for (int i = 0; i < 2; i++) {
		nd[u].cnt[i] = nd[lson(u)].cnt[i] + nd[rson(u)].cnt[i];
		nd[u].lc[i] = nd[lson(u)].lc[i] + (nd[lson(u)].lc[i] == nd[lson(u)].length() ? nd[rson(u)].lc[i] : 0);
		nd[u].rc[i] = nd[rson(u)].rc[i] + (nd[rson(u)].rc[i] == nd[rson(u)].length() ? nd[lson(u)].rc[i] : 0);
		nd[u].sc[i] = max(max(nd[lson(u)].sc[i], nd[rson(u)].sc[i]), nd[lson(u)].rc[i] + nd[rson(u)].lc[i]);
	}
}

void pushdown (int u) {
	if (nd[u].filp) {
		nd[lson(u)].splay();
		nd[rson(u)].splay();
		nd[u].filp = 0;
	} else if (nd[u].set != -1) {
		nd[lson(u)].maintain(nd[u].set);
		nd[rson(u)].maintain(nd[u].set);
		nd[u].set = -1;
	}
}

void build(int u, int l, int r) {
	nd[u].l = l, nd[u].r = r;
	nd[u].filp = 0, nd[u].set = -1;

	if (l == r) {
		nd[u].maintain(a[l]);
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int v) {
	if (l <= nd[u].l && nd[u].r <= r) {
		nd[u].maintain(v);
		return;
	}

	pushdown(u);
	int mid = (nd[u].l + nd[u].r) / 2;
	if (l <= mid)
		modify(lson(u), l, r, v);
	if (r > mid)
		modify(rson(u), l, r, v);
	pushup(u);
}

void modify (int u, int l, int r) {
	if (l <= nd[u].l && nd[u].r <= r) {
		nd[u].splay();
		return;
	}

	pushdown(u);
	int mid = (nd[u].l + nd[u].r) / 2;
	if (l <= mid)
		modify(lson(u), l, r);
	if (r > mid)
		modify(rson(u), l, r);
	pushup(u);
}

int query_cnt(int u, int l, int r) {
	if (l <= nd[u].l && nd[u].r <= r)
		return nd[u].cnt[1];

	pushdown(u);
	int mid = (nd[u].l + nd[u].r) / 2, ret = 0;
	if (l <= mid)
		ret += query_cnt(lson(u), l, r);
	if (r > mid)
		ret += query_cnt(rson(u), l, r);
	pushup(u);
	return ret;

}

int query_len(int u, int l, int r) {
	if (l <= nd[u].l && nd[u].r <= r)
		return nd[u].sc[1];

	pushdown(u);
	int mid = (nd[u].l + nd[u].r) / 2, ret;
	if (r <= mid)
		ret = query_len(lson(u), l, r);
	else if (l > mid)
		ret = query_len(rson(u), l, r);
	else {
		int ll = query_len(lson(u), l, r);
		int rr = query_len(rson(u), l, r);

		int A = min(nd[lson(u)].rc[1], mid - l + 1);
		int B = min(nd[rson(u)].lc[1], r - mid);
		ret = max(max(ll, rr), A + B);
	}
	pushup(u);
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf("%d", &a[i]);
		build(1, 0, N - 1);

		int op, l, r;
		while (M--) {
			scanf("%d%d%d", &op, &l, &r);
			if (op == 0)
				modify(1, l, r, 0);
			else if (op == 1)
				modify(1, l, r, 1);
			else if (op == 2)
				modify(1, l, r);
			else if (op == 3)
				printf("%d\n", query_cnt(1, l, r));
			else
				printf("%d\n", query_len(1, l, r));
		}
	}
	return 0;
}
