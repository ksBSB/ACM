#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 8005;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2];

inline void pushdown(int u) {
	if (s[u] != -1) {
		s[lson(u)] = s[rson(u)] = s[u];
		s[u] = -1;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	s[u] = -1;

	if (l == r)
		return;

	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
}

void modify(int u, int l, int r, int w) {
	if (l <= lc[u] && rc[u] <= r) {
		s[u] = w;
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	if (l <= mid)
		modify(lson(u), l, r, w);
	if (r > mid)
		modify(rson(u), l, r, w);
}

int query(int u, int x) {
	if (lc[u] == x && x == rc[u])
		return s[u];
	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid)
		return query(lson(u), x);
	else
		return query(rson(u), x);
}

int N, ans[maxn];

int main () {

	int l, r, c;
	while (scanf("%d", &N) == 1) {
		build (1, 0, 8000);
		for (int i = 0; i < N; i++) {
			scanf("%d%d%d", &l, &r, &c);
			modify(1, l, r - 1, c);
		}

		int pre = -1;
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i <= 8000; i++) {
			int k = query(1, i);
			if (k != pre && k != -1)
				ans[k]++;
			pre = k;
		}

		for (int i = 0; i <= 8000; i++) {
			if (ans[i])
				printf("%d %d\n", i, ans[i]);
		}
		printf("\n");
	}
	return 0;
}
