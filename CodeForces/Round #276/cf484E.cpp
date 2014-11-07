#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1e6 + 5;
typedef pair<int,int> pii;
struct Node {
	int lc, rc, lp, rp, L, R, S;
	int length() {
		return rp - lp + 1;
	}
}nd[maxn << 2];

int N, sz, root[maxn];
pii blo[maxn];

inline int newNode() {
	return sz++;
}

inline void pushup(int u) {
	int lcid = nd[u].lc, rcid = nd[u].rc;
	nd[u].L = nd[lcid].L + (nd[lcid].L == nd[lcid].length() ? nd[rcid].L : 0);
	nd[u].R = nd[rcid].R + (nd[rcid].R == nd[rcid].length() ? nd[lcid].R : 0);
	nd[u].S = max(nd[lcid].R + nd[rcid].L, max(nd[lcid].S, nd[rcid].S));
}

inline Node merge(Node a, Node b) {
	Node u;
	u.lp = a.lp; u.rp = b.rp;
	u.L = a.L + (a.L == a.length() ? b.L : 0);
	u.R = b.R + (b.R == b.length() ? a.R : 0);
	u.S = max(a.R + b.L, max(a.S, b.S));
	return u;
}

void build(int& u, int l, int r) {
	if (u == 0) u = newNode();
	nd[u] = (Node){0, 0, l, r, 0, 0, 0};

	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build(nd[u].lc, l, mid);
	build(nd[u].rc, mid +1, r);
	pushup(u);
}

int insert(int u, int x) {
	int k = newNode();
	nd[k] = nd[u];

	if (nd[k].lp == x && x == nd[k].rp) {
		nd[k].S = nd[k].L = nd[k].R = 1;
		return k;
	}

	int mid = (nd[k].lp + nd[k].rp) >> 1;
	if (x <= mid)
		nd[k].lc = insert(nd[k].lc, x);
	else
		nd[k].rc = insert(nd[k].rc, x);
	pushup(k);
	return k;
}

Node query(int u, int l, int r) {
	if (l <= nd[u].lp && nd[u].rp <= r)
		return nd[u];

	int mid = (nd[u].lp + nd[u].rp) >> 1;
	if (r <= mid)
		return query(nd[u].lc, l, r);
	else if (l > mid)
		return query(nd[u].rc, l, r);
	else {
		Node ll = query(nd[u].lc, l, r);
		Node rr = query(nd[u].rc, l, r);
		return merge(ll, rr);
	}
}

inline bool cmp (const pii& a, const pii& b) {
	return a.first > b.first;
}

void init () {
	sz = 1;
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &blo[i].first);
		blo[i].second = i;
	}
	sort(blo + 1, blo + 1 + N, cmp);
	build(root[0], 1, N);
	for (int i = 1; i <= N; i++)
		root[i] = insert(root[i-1], blo[i].second);
}

int main () {
	init();

	int q, l, r, w;
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d%d", &l, &r, &w);
		int L = 1, R = N;
		while (L < R) {
			int mid = (L + R) >> 1;
			if (query(root[mid], l, r).S >= w)
				R = mid;
			else
				L = mid + 1;
		}
		printf("%d\n", blo[L].first);
	}
	return 0;
}
