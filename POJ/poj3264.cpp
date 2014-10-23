#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int N, Q, v[maxn];
int lc[maxn << 2], rc[maxn << 2], T[maxn << 2], S[maxn << 2];

inline void pushup(int u) {
	T[u] = max(T[lson(u)], T[rson(u)]);
	S[u] = min(S[lson(u)], S[rson(u)]);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		T[u] = S[u] = v[l];
		return ;
	}

	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int x, int w) {
	if (x == lc[u] && rc[u] && x) {
		T[u] = S[u] = x;
		return;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid)
		modify(lson(u), x, w);
	else
		modify(rson(u), x, w);
	pushup(u);
}

int query(int u, int l, int r, int w) {
	if (l <= lc[u] && rc[u] <= r)
		return w ? T[u] : S[u];

	int mid = (lc[u] + rc[u]) >> 1, ret = w ? 0 : 1000001;
	if (l <= mid) {
		int tmp = query(lson(u), l, r, w);
		ret = w ? max(ret, tmp) : min(ret, tmp);
	}

	if (r > mid) {
		int tmp = query(rson(u), l, r, w);
		ret = w ? max(ret, tmp) : min(ret, tmp);
	}
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &Q) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &v[i]);
		build(1, 1, N);

		int l, r;
		for (int i = 0; i < Q; i++) {
			scanf("%d%d", &l, &r);
			printf("%d\n", query(1, l, r, 1) - query(1, l, r, 0));
		}
	}
	return 0;
}
