#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1) 

struct Node {
	int l, r, v, s;
	void set (int l, int r, int v, int s) {
		this->l = l;
		this->r = r;
		this->v = v;
		this->s = s;
	}

	void maintain (int x) {
		v = x;
		s = (r - l + 1) * x;
	}
}nd[maxn * 4];

int N, Q;

void pushup (int u) {
	nd[u].s = nd[lson(u)].s + nd[rson(u)].s;

	if (nd[lson(u)].v == nd[rson(u)].v)
		nd[u].v = nd[lson(u)].v;
	else
		nd[u].v = 0;
}

void pushdown(int u) {
	if (nd[u].v) {
		nd[lson(u)].maintain(nd[u].v);
		nd[rson(u)].maintain(nd[u].v);
		nd[u].v = 0;
	}
}

void build (int u, int l, int r) {
	nd[u].set(l, r, 1, r - l + 1);

	if (l == r)
		return;

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
}

void modify (int u, int l, int r, int x) {
	if (l <= nd[u].l && nd[u].r <= r) {
		nd[u].maintain(x);
		return;
	}

	pushdown(u);
	int mid = (nd[u].l + nd[u].r) / 2;
	if (l <= mid)
		modify(lson(u), l, r, x);
	if (r > mid)
		modify(rson(u), l, r, x);
	pushup(u);
}

int main () {
	int cas;
	scanf("%d", &cas);

	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d", &N);
		build(1, 1, N);

		int l, r, v;
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d%d%d", &l, &r, &v);
			modify(1, l, r, v);
		}
		printf("Case %d: The total value of the hook is %d.\n", kcas, nd[1].s);
	}
	return 0;
}
