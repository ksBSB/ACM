#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 32000;
const int maxm = 15000;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], c[maxn << 2], s[maxn << 2];

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
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	int mid = (lc[u] + rc[u]) >> 1, ret = 0;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	pushup(u);
	return ret;
}

int N, ans[maxm + 5];
struct point {
	int x, y;

	friend bool operator < (const point& a, const point& b) {
		if (a.x != b.x)
			return a.x < b.x;
		return a.y < b.y;
	}
}p[maxm + 5];

int main () {
	while (scanf("%d", &N) == 1) {
		build (1, 0, 32000);
		memset(ans, 0, sizeof(ans));

		for (int i = 0; i < N; i++)
			scanf("%d%d", &p[i].x, &p[i].y);
		sort(p, p + N);

		for (int i = 0; i < N; i++) {
			int k = query(1, 0, p[i].y);
			ans[k]++;
			modify(1, p[i].y, 1);
		}
		for (int i = 0; i < N; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
