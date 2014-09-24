#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

const int maxn = 200005;

struct Node {
	int l, r, v;
	void set(int l, int r, int v) {
		this->l = l;
		this->r = r;
		this->v = v;
	}
}nd[maxn * 4];

int N, M, Q;

void pushup(int u) {
	nd[u].v = max(nd[lson(u)].v, nd[rson(u)].v);
}

void build (int u, int l, int r) {
	nd[u].l = l;
	nd[u].r = r;
	
	if (l == r) {
		nd[u].v = M;
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

int query(int u, int x) {
	if (nd[u].l == nd[u].r) {
		nd[u].v -= x;
		return nd[u].l;
	}

	int ret = nd[lson(u)].v >= x ? query(lson(u), x) : query(rson(u), x);
	pushup(u);
	return ret;
}

int main () {
	while (scanf("%d%d%d", &N, &M, &Q) == 3) {
		build(1, 1, min(N,Q));

		int x;
		while (Q--) {
			scanf("%d", &x);
			printf("%d\n", nd[1].v >= x ? query(1, x) : -1);
		}
	}
	return 0;
}
