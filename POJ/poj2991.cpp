#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const double pi = atan(1.0) * 4;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
const int maxn = 10005;

int lc[maxn * 4], rc[maxn * 4], s[maxn * 4], v[maxn * 4];
double xi[maxn * 4], yi[maxn * 4];

void rotate (int u, int deg) {
	double r = deg * pi / 180;
	double x = xi[u] * cos(r) - yi[u] * sin(r);
	double y = xi[u] * sin(r) + yi[u] * cos(r);

	xi[u] = x; yi[u] = y;
	s[u] = (s[u] + deg) % 360;
	v[u] = (v[u] + deg) % 360;
}

void pushup (int u) {
	xi[u] = xi[lson(u)] + xi[rson(u)];
	yi[u] = yi[lson(u)] + yi[rson(u)];
}

void pushdown (int u) {
	if (s[u]) {
		rotate(lson(u), s[u]);
		rotate(rson(u), s[u]);
		s[u] = 0;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	s[u] = v[u] = 0;

	if (l == r) {
		xi[u] = 0;
		scanf("%lf", &yi[u]);
		return ;
	}

	int mid = (l + r) / 2;
	build (lson(u), l, mid);
	build (rson(u), mid + 1, r);
	pushup(u);
}

int query (int u, int pos) {
	if (lc[u] == rc[u])
		return v[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (pos <= mid)
		return query(lson(u), pos);
	else
		return query(rson(u), pos);
	pushup(u);
}

void modify (int u, int l, int r, int deg) {
	if (l <= lc[u] && rc[u] <= r) {
		rotate(u, deg);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, deg);
	if (r > mid)
		modify(rson(u), l, r, deg);
	pushup(u);
}

int N, M;

int main () {
	int cas = 0, d, r;
	while (scanf("%d%d", &N, &M) == 2) {
		if (cas++)
			printf("\n");
		build (1, 0, N-1);

		while (M--) {
			scanf("%d%d", &d, &r);
			r = (query(1, d - 1) + 180 + r - query(1, d)) % 360;
			modify(1, d, N - 1, r);
			printf("%.2lf %.2lf\n", xi[1], yi[1]);
		}
	}
	return 0;
}
