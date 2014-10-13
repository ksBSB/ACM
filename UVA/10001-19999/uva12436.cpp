#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 250100;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], v[maxn << 2];
ll nd[maxn << 2], ad[maxn << 2], s[maxn << 2];

void pushup(int u);
void pushdown (int u);

inline int length(int u) {
	return rc[u] - lc[u] + 1;
}

inline void change (int u, ll a) {
	v[u] = 1;
	ad[u] = 0;
	nd[u] = a;
	s[u] = a * length(u);
}

inline void maintain (int u, ll a, ll d) {
	if (v[u] && lc[u] != rc[u]) {
		pushdown(u);
		pushup(u);
	}

	v[u] = 0;
	nd[u] += a;
	ad[u] += d;
	ll n = length(u);
	s[u] += a * n + (((n-1) * n) / 2) * d;
}

inline void pushup (int u) {
	s[u] = s[lson(u)] + s[rson(u)];
}

inline void pushdown (int u) {
	if (v[u]) {
		change(lson(u), nd[u]);
		change(rson(u), nd[u]);
		v[u] = nd[u] = 0;
	} else if (nd[u] || ad[u]) {
		maintain(lson(u), nd[u], ad[u]);
		maintain(rson(u), nd[u] + length(lson(u)) * ad[u], ad[u]);
		nd[u] = ad[u] = 0;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	nd[u] = ad[u] = s[u] = 0;

	if (l == r)
		return;
	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int l, int r, ll a, ll d) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, a + d * (lc[u] - l), d);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, a, d);
	if (r > mid)
		modify(rson(u), l, r, a, d);
	pushup(u);
}

void set(int u, int l, int r, ll a) {
	if (l <= lc[u] && rc[u] <= r) {
		change(u, a);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		set(lson(u), l, r, a);
	if (r > mid)
		set(rson(u), l, r, a);
	pushup(u);
}

ll query (int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	pushdown(u);
	ll ret = 0;
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid) 
		ret += query(rson(u), l, r);
	pushdown(u);
	return ret;
}

int N;

int main () {
	while (~scanf("%d", &N)) {
		char op[5];
		int l, r, x;
		build(1, 1, 250000);
		while (N--) {
			scanf("%s%d%d", op, &l, &r);
			if (op[0] == 'A')
				modify(1, l, r, 1, 1);
			else if (op[0] == 'B')
				modify(1, l, r, r - l + 1, -1);
			else if (op[0] == 'C') {
				scanf("%d", &x);
				set(1, l, r, x);
			} else
				printf("%lld\n", query(1, l, r));
		}
	}
	return 0;
}
