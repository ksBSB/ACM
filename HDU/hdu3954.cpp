#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10005;
const int INF = 0x3f3f3f3f;

int N, K, Q, need[15];

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2];
int ad[maxn << 2], nd[maxn << 2], rk[maxn << 2];

void maintain(int u, int d);

inline void pushup(int u) {
	s[u] = max(s[lson(u)], s[rson(u)]);
	rk[u] = max(rk[lson(u)], rk[rson(u)]);
	nd[u] = min(nd[lson(u)], nd[rson(u)]);
}

inline void pushdown(int u) {
	if (ad[u]) {
		maintain(lson(u), ad[u]);
		maintain(rson(u), ad[u]);
		ad[u] = 0;
	}
}

inline void levelup(int u) {
	ad[u] = 0;
	while (s[u] >= need[rk[u] + 1])
		rk[u]++;
	int tmp = need[rk[u] + 1] - s[u];
	nd[u] = tmp / rk[u] + (tmp % rk[u] ? 1 : 0);
}

void maintain (int u, int d) {
	nd[u] -= d;
	ad[u] += d;
	s[u] += rk[u] * d;

	if (nd[u] <= 0) {
		if (lc[u] == rc[u])
			levelup(u);
		else {
			pushdown(u);
			pushup(u);
		}
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	s[u] = ad[u] = nd[u] = rk[u] = 0;

	if (l == r) {
		rk[u] = 1;
		nd[u] = need[2];
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
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
}

int query (int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2, ret = 0;
	if (l <= mid)
		ret = max(ret, query(lson(u), l, r));
	if (r > mid)
		ret = max(ret, query(rson(u), l, r));
	pushup(u);
	return ret;
}

void init () {
	scanf("%d%d%d", &N, &K, &Q);

	for (int i = 2; i <= K; i++)
		scanf("%d", &need[i]);
	need[K+1] = INF;
	build(1, 1, N);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d:\n", kcas);

		char op[5];
		int t, l, r;
		while (Q--) {
			scanf("%s%d%d", op, &l, &r);
			if (op[0] == 'W') {
				scanf("%d", &t);
				modify(1, l, r, t);
			} else
				printf("%d\n", query(1, l, r));
		}
		printf("\n");
	}
	return 0;
}
