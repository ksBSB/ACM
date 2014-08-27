#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

const int maxn = 50100;

ll N;
int M;
int x[2][maxn], y[2][maxn];
vector<int> bset, vec;

struct Segment {
	int l, r, h, v;
	void set(int l, int r, int h, int v) {
		this->l = l;
		this->r = r;
		this->h = h;
		this->v = v;
	}
}seg[maxn*2], node[maxn*8];

inline bool cmp (const Segment& a, const Segment& b) {
	return a.h < b.h;
}

inline int search (int x) {
	return lower_bound(bset.begin(), bset.end(), x) - bset.begin();
}

inline void get_hashkey () {
	sort(vec.begin(), vec.end());
	bset.push_back(vec[0]);

	for (int i = 1; i < vec.size(); i++) {
		if (vec[i] != vec[i-1])
			bset.push_back(vec[i]);
	}
}

inline void add_segment (int i, int h, int l, int r, int v) {
	seg[i].set(l, r, h, v);
	vec.push_back(l);
	vec.push_back(r);
}

inline void pushup (int u) {
	if (node[u].h)
		node[u].v = bset[node[u].r+1] - bset[node[u].l];
	else if (node[u].l == node[u].r)
		node[u].v = 0;
	else
		node[u].v = node[lson(u)].v + node[rson(u)].v;
}

void build_segTree (int u, int l, int r) {
	node[u].set(l, r, 0, 0);
	if (l == r) {
		pushup(u);
		return ;
	}

	int mid = (l + r) / 2;
	build_segTree(lson(u), l, mid);
	build_segTree(rson(u), mid + 1, r);
	pushup(u);
}

ll query_segTree (int u, int l, int r) {
	if (l <= node[u].l && node[u].r <= r)
		return node[u].v;

	int mid = (node[u].l + node[u].r) / 2;
	ll ret = 0;
	if (l <= mid)
		ret += query_segTree(lson(u), l, r);
	if (r > mid)
		ret += query_segTree(rson(u), l, r);
	return ret;
}

void add_segTree (int u, int l, int r, int v) {
	if (l <= node[u].l && node[u].r <= r) {
		node[u].h += v;
		pushup(u);
		return;
	}

	int mid = (node[u].l + node[u].r) / 2;
	if (l <= mid)
		add_segTree(lson(u), l, r, v);
	if (r > mid)
		add_segTree(rson(u), l, r, v);
	pushup(u);
}

ll solve (int x[2][maxn], int y[2][maxn], ll R, ll C) {

	if (N == 0)
		return 1LL * C * (R - M + 1);

	int n = 0;
	vec.clear();
	bset.clear();

	for (int i = 0; i < N; i++) {
		add_segment(n++, x[0][i] - 1, max(y[0][i] - M, 0), y[1][i], 1);
		add_segment(n++, x[1][i], max(y[0][i] - M, 0), y[1][i], -1);
	}

	add_segment(n++, 0, max((int)R + 1 - M, 0), R, 1);
	add_segment(n++, C, max((int)R + 1 - M, 0), R, -1);

	get_hashkey();
	sort(seg, seg + n, cmp);

	int size = bset.size() - 2;
	build_segTree (1, 0, size);

	ll ret = 0;
	for (int i = 0; i < n; i++) {
		ll tmp = query_segTree(1, 0, size);
		if (i)
			ret += tmp * (seg[i].h - seg[i-1].h);
		add_segTree(1, search(seg[i].l), search(seg[i].r) - 1, seg[i].v);
	}

	return R * C - ret;
}

int main () {
	ll R, C;
	while (scanf("%lld%lld%lld%d", &R, &C, &N, &M) == 4) {
		for (int i = 0; i < N; i++)
			scanf("%d%d%d%d", &x[0][i], &y[0][i], &x[1][i], &y[1][i]);

		ll ans = solve(x, y, C, R) + solve(y, x, R, C);

		if (M == 1)
			ans /= 2;
		printf("%lld\n", ans);
	}
	return 0;
}
