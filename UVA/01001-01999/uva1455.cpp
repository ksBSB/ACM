#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6;
const int maxp = 1e5+5;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

struct Node {
	int l, r, nc, nz;
	void set (int l, int r, int nc, int nz) {
		this->l = l;
		this->r = r;
		this->nc = nc;
		this->nz = nz;
	}
}node[maxn * 4 + 5];

struct Segment {
	int l, r;
	Segment (int l = 0, int r = 0) {
		this->l = l;
		this->r = r;
	}
}s[maxp];

void add_node(int u, int vc, int vz) {
	/*
	if (node[u].l == node[u].r && node[u].l == 1)
		printf("solve before:%d %d %d %d!\n", node[u].nc, node[u].nz, vc, vz);
		*/
	node[u].nc += vc;
	node[u].nz += vz;
}

void pushup(int u) {
	node[u].set(node[lson(u)].l, node[rson(u)].r, 0, 0);
}

void pushdown(int u) {
	add_node(lson(u), node[u].nc, node[u].nz);
	add_node(rson(u), node[u].nc, node[u].nz);
	node[u].nc = node[u].nz = 0;
}

void build_segTree (int u, int l, int r) {
	if (l == r) {
		node[u].set(l, r, 0, 0);
		return;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(u), l, mid);
	build_segTree(rson(u), mid + 1, r);
	pushup(u);
}

void insert_segTree (int u, int l, int r, int vc, int vz) {
	if (l <= node[u].l && node[u].r <= r) {
		add_node(u, vc, vz);
		return;
	}

	pushdown(u);
	int mid = (node[u].l + node[u].r) / 2;
	if (l <= mid)
		insert_segTree(lson(u), l, r, vc, vz);
	if (r > mid)
		insert_segTree(rson(u), l, r, vc, vz);
}

Segment query_segTree (int u, int x) {
	if (node[u].l == x && node[u].r == x)
		return Segment(node[u].nc, node[u].nz);

	pushdown(u);
	int mid = (node[u].l + node[u].r) / 2;
	if (x <= mid)
		return query_segTree(lson(u), x);
	else
		return query_segTree(rson(u), x);
}

int f[maxp], d[maxp];

void init () {
	build_segTree (1, 0, maxn);

	int n, x, y;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		f[i] = i;
		d[i] = 1;
		scanf("%d%d", &x, &y);
		s[i].l = s[i].r = y;
	}
}

void change (int r, int l, int vc, int vz) {
	if (r < l)
		return;
	insert_segTree (1, l, r, vc, vz);
}

int getfar (int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

void link (int u, int v) {
	int x = getfar(u);
	int y = getfar(v);

	if (x == y)
		return;

	if (s[x].l > s[y].l)
		swap(x, y);

	//printf("%d %d %d %d!!!\n", s[x].l, s[x].r, s[y].l, s[y].r);

	int root = 1048576;

	if (s[y].l >= s[x].r) {
		change(s[y].l - 1, s[x].r, 0, 1);
		change(s[y].r - 1, s[x].r, d[x], 0);
	} else if (s[y].r <= s[x].r) {
		change(s[y].r - 1, s[y].l, 0, -1);
		change(s[x].r - 1, s[y].r, d[y], 0);
	} else {
		change(s[x].r - 1, s[y].l, 0, -1);
		change(s[y].r - 1, s[x].r, d[x], 0);
	}
	//printf("fuck:%d %d\n", node[root].nc, node[root].nz);
	change(s[y].l - 1, s[x].l, d[y], 0);


	s[y].l = min(s[x].l, s[y].l);
	s[y].r = max(s[x].r, s[y].r);
	f[x] = y;
	d[y] += d[x];
}

void solve () {
	int n, x, y;
	double q;
	char order[10];

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", order);
		if (strcmp(order, "road") == 0) {
			scanf("%d%d", &x, &y);
			link(x, y);
		} else {
			scanf("%lf", &q);
			Segment ans = query_segTree(1, (int)q);
			printf("%d %d\n", ans.r, ans.l);
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
