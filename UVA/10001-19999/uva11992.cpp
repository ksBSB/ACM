#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)
const int maxn = 1e6+6;
const int INF = 1<<30;

struct Item {
	int sum_val, max_val, min_val;
	Item (int sum_val = 0, int max_val = 0, int min_val = 0) {
		this->set(sum_val, max_val, min_val);
	}
	void set (int sum_val, int max_val, int min_val) {
		this->sum_val = sum_val;
		this->max_val = max_val;
		this->min_val = min_val;
	}
};

struct Node {
	int l, r;
	Item v;
	int vset, vadd;
	void set (int l, int r, int vset, int vadd) {
		this->l = l;
		this->r = r;
		this->vset = vset;
		this->vadd = vadd;
	}
} node[maxn*4];

int R, C, Q;

inline Item get_item (Item a, Item b) {
	return Item(a.sum_val + b.sum_val, max(a.max_val, b.max_val), min(a.min_val, b.min_val));
}

inline void add_node (int u, int val) {
	node[u].vadd += val;
	node[u].v.sum_val += (node[u].r - node[u].l + 1) * val;
	node[u].v.max_val += val;
	node[u].v.min_val += val;
}

inline void set_node (int u, int val) {
	node[u].vadd = 0; // clear vadd after set value;
	node[u].vset = val;
	node[u].v.sum_val = (node[u].r - node[u].l + 1) * val;
	node[u].v.max_val = val;
	node[u].v.min_val = val;
}

void pushup(int u) {
	node[u].set(node[lson(u)].l, node[rson(u)].r, -1, 0);
	node[u].v = get_item(node[lson(u)].v, node[rson(u)].v);
}

void pushdown(int u) {
	if (node[u].vset >= 0) {
		set_node(lson(u), node[u].vset);
		set_node(rson(u), node[u].vset);
		node[u].vset = -1;
	}

	if (node[u].vadd) {
		add_node(lson(u), node[u].vadd);
		add_node(rson(u), node[u].vadd);
		node[u].vadd = 0;
	}
}

void build_segTree (int u, int l, int r) {

	if (l == r) {
		node[u].set(l, r, -1, 0);
		node[u].v.set(0, 0, 0);
		return;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(u), l, mid);
	build_segTree(rson(u), mid + 1, r);
	pushup(u);
}

void add_segTree (int u, int l, int r, int val) {
	if (l <= node[u].l && node[u].r <= r) {
		add_node(u, val);
		return;
	}

	pushdown(u);
	int mid = (node[u].l + node[u].r) / 2;
	if (l <= mid)
		add_segTree(lson(u), l, r, val);
	if (r > mid)
		add_segTree(rson(u), l, r, val);
	pushup(u);
}

void set_segTree (int u, int l, int r, int val) {
	if (l <= node[u].l && node[u].r <= r) {
		set_node(u, val);
		return;
	}

	pushdown(u);
	int mid = (node[u].l + node[u].r) / 2;
	if (l <= mid)
		set_segTree(lson(u), l, r, val);
	if (r > mid)
		set_segTree(rson(u), l, r, val);
	pushup(u);
}

Item query_segTree (int u, int l, int r) {
	if (l <= node[u].l && node[u].r <= r)
		return node[u].v;

	pushdown(u);
	Item ret(0, -INF, INF);
	int mid = (node[u].l + node[u].r) / 2;
	if (l <= mid)
		ret = get_item(ret, query_segTree(lson(u), l, r));
	if (r > mid)
		ret = get_item(ret, query_segTree(rson(u), l, r));
	return ret;
}

int main () {
	while (scanf("%d%d%d", &R, &C, &Q) == 3) {
		build_segTree(1, 1, R * C);

		int sign, x1, y1, x2, y2, v;
		for (int i = 0; i < Q; i++) {
			scanf("%d", &sign);
			if (sign != 3) {
				scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
				for (int j = x1 - 1; j < x2; j++) {
					if (sign == 1)
						add_segTree(1, j * C + y1, j * C + y2, v);
					else
						set_segTree(1, j * C + y1, j * C + y2, v);
				}
			} else {
				Item ans(0, -INF, INF);
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

				for (int j = x1 - 1; j < x2; j++) {
					Item tmp = query_segTree(1, j * C + y1, j * C + y2);
					ans = get_item(ans, tmp);
				}
				printf("%d %d %d\n", ans.sum_val, ans.min_val, ans.max_val);
			}
		}
	}
	return 0;
}
