#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50005;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

struct Node {
	int l, r, val;
	void set (int l, int r, int val) {
		this->l = l;
		this->r = r;
		this->val = val;
	}
}node[maxn * 4];

void pushup(int u) {
	node[u].set(node[lson(u)].l, node[rson(u)].r, node[lson(u)].val + node[rson(u)].val);
}
void build_segTree (int u, int l, int r) {
	if (l == r) {
		node[u].set(l, r, 1);
		return ;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(u), l, mid);
	build_segTree(rson(u), mid + 1, r);
	pushup(u);
}

int query_segTree (int u, int val) {
	if (node[u].l == node[u].r && val == 1)
		return node[u].l;

	if (val > node[lson(u)].val)
		return query_segTree(rson(u), val - node[lson(u)].val);
	else
		return query_segTree(lson(u), val);
}

void insert_segTree (int u, int x, int val) {
	if (node[u].l == x && node[u].r == x) {
		node[u].val += val;
		return ;
	}

	int mid = (node[u].l + node[u].r) / 2;
	if (x <= mid)
		insert_segTree(lson(u), x, val);
	else
		insert_segTree(rson(u), x, val);
	pushup(u);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int n, x;
		scanf("%d", &n);
		build_segTree(1, 1, n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			x = query_segTree(1, x+1);
			insert_segTree(1, x, -1);
			printf("%d%c", x, i == n ? '\n' : ' ');
		}
	}
	return 0;
}
