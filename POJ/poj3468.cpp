#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

const int maxn = 100005;
typedef long long ll;

struct Node {
	int l, r;
	ll sum, add;
	void set (int l, int r, ll sum, ll add) {
		this->l = l;
		this->r = r;
		this->sum = sum;
		this->add = add;
	}
	void maintain (ll v) {
		sum += (r - l + 1) * v;
		add += v;
	}
}nd[maxn * 4];

int N, Q, A[maxn];

void pushup (int u) {
	nd[u].sum = nd[lson(u)].sum + nd[rson(u)].sum;
}

void pushdown(int u) {
	if (nd[u].add) {
		nd[lson(u)].maintain(nd[u].add);
		nd[rson(u)].maintain(nd[u].add);
		nd[u].add = 0;
	}
}

void build (int u, int l, int r) {
	nd[u].l = l;
	nd[u].r = r;
	nd[u].add = 0;

	if (l == r) {
		nd[u].sum = A[l];
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

ll query(int u, int l, int r) {
	if (l <= nd[u].l && nd[u].r <= r)
		return nd[u].sum;

	pushdown(u);
	ll ret = 0;
	int mid = (nd[u].l + nd[u].r) / 2;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	pushup(u);
	return ret;
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

int main () {
	while (scanf("%d%d", &N, &Q) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);

		build(1, 1, N);

		int l, r, v;
		char order[5];
		for (int i = 0; i < Q; i++) {
			scanf("%s%d%d", order, &l, &r);
			if (order[0] == 'Q')
				printf("%lld\n", query(1, l, r));
			else {
				scanf("%d", &v);
				modify(1, l, r, v);
			}
		}
	}
	return 0;
}
