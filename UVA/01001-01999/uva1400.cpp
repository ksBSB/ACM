#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)
typedef long long ll;
const int maxn = 500005;
const ll INF = 0x3f3f3f3f3f3f3f3f;

struct segment {
	int l, r;
	ll val;
	segment (int l = 0, int r = 0, ll val = 0) {
		this->set(l, r, val);
	}
	void set (int l, int r, ll val) {
		this->l = l;
		this->r = r;
		this->val = val;
	}
	segment operator + (const segment& u) {
		return segment(min(l, u.l), max(r, u.r), val + u.val);
	}
	bool operator < (const segment& u) const {
		if (val != u.val)
			return val < u.val;
		if (l != u.l)
			return l > u.l;
		return r > u.r;
	}
};

struct Node {
	int l, r;
	segment max_sub, max_prefix, max_suffix;
} node[4*maxn];
int N, M;
ll arr[maxn], s[maxn];

Node seg_push (Node a, Node b) {

	Node ret;

	ll suml = s[a.r] - s[a.l-1];
	ll sumr = s[b.r] - s[b.l-1];

	ret.l = a.l;
	ret.r = b.r;
	ret.max_sub = max(a.max_suffix + b.max_prefix, max(a.max_sub, b.max_sub));
	ret.max_prefix = max(a.max_prefix, segment(a.l, a.r, suml) + b.max_prefix);
	ret.max_suffix = max(b.max_suffix, a.max_suffix + segment(b.l, b.r, sumr));
	return ret;
}

void build_segTree (int root, int l, int r) {

	if (l == r) {
		node[root].l = node[root].r = l;
		node[root].max_sub.set(l, r, (ll)arr[l]);
		node[root].max_prefix.set(l, r, (ll)arr[l]);
		node[root].max_suffix.set(l, r, (ll)arr[l]);
		return;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(root), l, mid);
	build_segTree(rson(root), mid + 1, r);

	node[root] = seg_push(node[lson(root)], node[rson(root)]);
}

Node query (int root, int l, int r) {

	if (l <= node[root].l && r >= node[root].r)
		return node[root];

	int mid = (node[root].l + node[root].r) / 2;
	if (l <= mid && r > mid)
		return seg_push(query(lson(root), l, r), query(rson(root), l, r));
	else if (r <= mid)
		return query(lson(root), l, r);
	else
		return query(rson(root), l, r);
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &N, &M) == 2) {
		s[0] = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%lld", &arr[i]);
			s[i] = s[i-1] + arr[i];
		}

		build_segTree(1, 1, N);
		printf("Case %d:\n", cas++);

		int l, r;
		for (int i = 0; i < M; i++) {
			scanf("%d%d", &l, &r);
			Node u = query(1, l, r);
			printf("%d %d\n", u.max_sub.l, u.max_sub.r);
		}
	}
	return 0;
}
