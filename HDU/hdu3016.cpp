#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100010;
const int INF = 0x3f3f3f3f;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], v[maxn << 2], s[maxn << 2];

inline void maintain(int u, int d) {
	v[u] = s[u] = d;
}

inline void pushup (int u) {
	s[u] = max(s[lson(u)], s[rson(u)]);
}

inline void pushdown(int u) {
	if (v[u]) {
		maintain(lson(u), v[u]);
		maintain(rson(u), v[u]);
		v[u] = 0;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	v[u] = s[u] = -INF;

	if (l == r) 
		return;

	int mid = (l + r) / 2;
	build (lson(u), l, mid);
	build (rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int d) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, d);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, d);
	if (r > mid)
		modify(rson(u), l, r, d);
	pushup(u);
	return;
}

int query(int u, int l, int r) {
	if ((l <= lc[u] && rc[u] <= r) || v[u])
		return s[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2, ret = -INF;
	if (l <= mid)
		ret = max(ret, query(lson(u), l, r));
	if (r > mid)
		ret = max(ret, query(rson(u), l, r));
	pushup(u);
	return ret;
}

struct plank {
	int h, l, r, d, v;
	void read () {
		scanf("%d%d%d%d", &h, &l, &r, &d);
	}
	friend bool operator < (const plank& a, const plank& b) {
		return a.h > b.h;
	}
}p[maxn+5];

int N;

int main () {
	while (scanf("%d", &N) == 1) {
		build (1, 1, maxn);

		for (int i = 1; i <= N; i++)
			p[i].read();
		sort(p + 1, p + N + 1);

		p[1].v = 100 + p[1].d;
		modify(1, p[1].l, p[1].r, -INF);
		if (p[1].v > 0) {
			modify(1, p[1].l, p[1].l, p[1].v);
			modify(1, p[1].r, p[1].r, p[1].v);
		}

		for (int i = 2; i <= N; i++) {
			int ret = query(1, p[i].l, p[i].r);
			p[i].v = ret + p[i].d;
			modify(1, p[i].l, p[i].r, -INF);
			if (p[i].v > 0) {
				modify(1, p[i].l, p[i].l, p[i].v);
				modify(1, p[i].r, p[i].r, p[i].v);
			}
		}
		int ans = query(1, 1, maxn);
		printf("%d\n", ans <= 0 ? -1 : ans);
	}
	return 0;
}
