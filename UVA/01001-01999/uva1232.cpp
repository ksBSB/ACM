#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100000;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

struct Node {
	int l, r, sign, high;
	void set (int l, int r, int sign, int high) {
		this->l = l;
		this->r = r;
		this->sign = sign;
		this->high = high;
	}
}node[maxn*4+5];

void pushup(int u) {
	node[u].l = node[lson(u)].l;
	node[u].r = node[rson(u)].r;

	if (node[lson(u)].sign && node[rson(u)].sign
			&& node[lson(u)].high == node[rson(u)].high) {
		node[u].sign = 1;
		node[u].high = node[lson(u)].high;
	} else {
		node[u].sign = 0;
		node[u].high = 0;
	}
}

void build_segTree (int u, int l, int r) {
	if (l == r) {
		node[u].set(l, r, 1, 0);
		return;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(u), l, mid);
	build_segTree(rson(u), mid + 1, r);
	pushup(u);
}

void pushdown (int u) {
	node[lson(u)].sign = node[rson(u)].sign = 1;
	node[lson(u)].high = node[rson(u)].high = node[u].high;
	node[u].sign = node[u].high = 0;
}

int insert (int u, int l, int r, int h) {
	if (node[u].sign && node[u].high > h)
		return 0;

	if (l <= node[u].l && node[u].r <= r && node[u].sign) {
		node[u].high = h;
		return node[u].r - node[u].l + 1;
	}

	if (node[u].sign)
		pushdown(u);

	int mid = (node[u].l + node[u].r) / 2;
	int ret = 0;

	if (mid >= l)
		ret += insert(lson(u), l, r, h);
	if (mid < r)
		ret += insert(rson(u), l, r, h);
	pushup(u);
	return ret;
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		build_segTree(1, 1, maxn);

		int ans = 0, x, y, h;
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &x, &y, &h);
			ans += insert(1, x+1, y, h);
		}
		printf("%d\n", ans);
	}
	return 0;
}
