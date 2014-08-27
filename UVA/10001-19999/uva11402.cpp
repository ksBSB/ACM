#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1024005;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

int N;
bool v[maxn];

struct Node {
	int l, r;
	int vset, vmix, val;
	void set (int l, int r, int val, int vset) {
		this->l = l;
		this->r = r;
		this->val = val;
		this->vset = vset;
	}
}node[maxn*4];

void set_node (int u, int vset) {
	if (vset == 1 || (node[u].vset == 2 && vset == 3)) {
		node[u].val = node[u].r - node[u].l + 1;
		node[u].vset = 1;
	} else if (vset == 2 || (node[u].vset == 1 && vset == 3)) {
		node[u].val = 0;
		node[u].vset = 2;
	} else {
		node[u].val = node[u].r - node[u].l + 1 - node[u].val;
		node[u].vset = vset - node[u].vset;
	}
}

void pushup (int u) {
	node[u].set(node[lson(u)].l, node[rson(u)].r, node[lson(u)].val + node[rson(u)].val, 0);
}

void pushdown (int u) {
	if (node[u].vset) {
		set_node(lson(u), node[u].vset);
		set_node(rson(u), node[u].vset);
	}
	node[u].vset = 0;
}

void build_segTree (int u, int l, int r) {
	if (l == r) {
		node[u].set(l, r, v[l] ? 1 : 0, 0);
		return;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(u), l, mid);
	build_segTree(rson(u), mid+1, r);
	pushup(u);
}

void init () {
	N = 0;
	memset(v, 0, sizeof(v));

	int n, x;
	char s[100];
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%s", &x, s);
		int len = strlen(s);
		for (int j = 0; j < len; j++) {
			if (s[j] == '1') {
				for (int k = 0; k < x; k++)
					v[k*len+j+N] = 1;
			}
		}
		N += x * len;
	}
	build_segTree(1, 0, N-1);
}

void set_segTree (int u, int l, int r, int vset) {

	if (l <= node[u].l && node[u].r <= r) {
		set_node(u, vset);
		return;
	}

	pushdown(u);
	int mid = (node[u].l + node[u].r) / 2;
	if (l <= mid)
		set_segTree(lson(u), l, r, vset);
	if (r > mid)
		set_segTree(rson(u), l, r, vset);
	pushup(u);
}

int query_segTree (int u, int l, int r) {
	if (l <= node[u].l && node[u].r <= r)
		return node[u].val;

	pushdown(u);
	int mid = (node[u].l + node[u].r) / 2;
	int ret = 0;
	if (l <= mid)
		ret += query_segTree(lson(u), l, r);
	if (r > mid)
		ret += query_segTree(rson(u), l, r);
	pushup(u);
	return ret;
}

void solve () {
	int n, cas = 1, l, r;
	char s[5];

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s%d%d", s, &l, &r);
		if (s[0] == 'F')
			set_segTree(1, l, r, 1);
		else if (s[0] == 'E')
			set_segTree(1, l, r, 2);
		else if (s[0] == 'I')
			set_segTree(1, l, r, 3);
		else
			printf("Q%d: %d\n", cas++, query_segTree(1, l, r));
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		printf("Case %d:\n", kcas);
		solve();
	}
	return 0;
}
