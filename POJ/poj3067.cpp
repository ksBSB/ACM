#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2];
inline void pushup(int u) {
	s[u] = s[lson(u)] + s[rson(u)];
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	s[u] = 0;

	if (l == r)
		return ;
	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int x, int w) {
	if (x == lc[u] && rc[u] == x) {
		s[u] += w;
		return;
	}	

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid)
		modify(lson(u), x, w);
	else
		modify(rson(u), x, w);
	pushup(u);
}

int query(int u, int l, int r) {
	if (l > r)
		return 0;

	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	int mid = (lc[u] + rc[u]) >> 1, ret = 0;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	return ret;
}

int N, M, Q;
struct point {
	int x, y;
	friend bool operator < (const point& a, const point& b) {
		if (a.x != b.x)
			return a.x < b.x;
		return a.y < b.y;
	}
}p[maxn * maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%d%d%d", &N, &M, &Q);
		build(1, 1, M);

		long long ans = 0;
		for (int i = 0; i < Q; i++)
			scanf("%d%d", &p[i].x, &p[i].y);
		sort(p, p + Q);

		for (int i = 0; i < Q; i++) {
			ans += query(1, p[i].y + 1, M);
			modify(1, p[i].y, 1);
		}
		printf("Test case %d: %lld\n", kcas, ans);
	}
	return 0;
}
