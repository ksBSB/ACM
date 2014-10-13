#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef  long long ll;

const int maxn = 100000;

int N, Q;
ll P[maxn + 5];

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2];
ll s[maxn << 2], v[maxn << 2];

inline void maintain(int u, ll d) {
	v[u] = d;
	s[u] = d * (rc[u] - lc[u] + 1);
}

inline void pushup(int u) {
	s[u] = s[lson(u)] + s[rson(u)];
	v[u] = (v[lson(u)] == v[rson(u)] ? v[lson(u)] : 0);
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

	if (l == r) {
		v[u] = s[u] = P[l];
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r && v[u]) {
		maintain(u, (ll)sqrt((double)v[u]));
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r);
	if (r > mid)
		modify(rson(u), l, r);
	pushup(u);
}

ll query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	pushdown(u);
	ll ret = 0;
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	pushup(u);
	return ret;
}

int main () {
	int kcas = 1;
	while (scanf("%d", &N) == 1) {
		for (int i = 1; i <= N; i++)
			scanf("%I64d", &P[i]);
		build(1, 1, N);
		printf("Case #%d:\n", kcas++);

		int t, l, r;
		scanf("%d", &Q);
		while (Q--) {
			scanf("%d%d%d", &t, &l, &r);
			if (l > r)
				swap(l, r);
			if (t)
				printf("%I64d\n", query(1, l, r));
			else
				modify(1, l, r);
		}
		printf("\n");
	}
	return 0;
}
