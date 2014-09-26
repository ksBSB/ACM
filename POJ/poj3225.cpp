#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 65535 * 2;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

int lc[maxn * 4], rc[maxn * 4], set[maxn * 4], filp[maxn * 4];

inline void splay(int u) {
	filp[u] ^= 1;

	if (filp[u] && set[u] != -1) {
		filp[u] = 0;
		set[u] ^= 1;
	}
}

inline void maintain(int u, int v) {
	set[u] = v;
	filp[u] = 0;
}

inline void pushdown (int u) {
	if (set[u] != -1) {
		maintain(lson(u), set[u]);
		maintain(rson(u), set[u]);
		set[u] = -1;
	}

	if (filp[u]) {
		splay(lson(u));
		splay(rson(u));
		filp[u] = 0;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	maintain(u, -1);

	if (l == r) {
		maintain(u, 0);
		return;
	}

	int mid = (l + r) / 2;
	build (lson(u), l, mid);
	build (rson(u), mid + 1, r);
}

void modify (int u, int l, int r, int v) {
	if (l > r) return;

	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, v);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, v);
	if (r > mid)
		modify(rson(u), l, r, v);
}

void change (int u, int l, int r) {
	if (l > r) return;

	if (l <= lc[u] && rc[u] <= r) {
		splay(u);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		change(lson(u), l, r);
	if (r > mid)
		change(rson(u), l, r);
}

int query (int u, int x) {
	if (lc[u] == x && x == rc[u])
		return set[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		return query(lson(u), x);
	else
		return query(rson(u), x);
}

int L, R;
char op, LP, RP;

inline void put (int left, int right) {
	if (left&1)
		printf("(%d,", left/2);
	else
		printf("[%d,", left/2);

	if (right&1)
		printf("%d)", (right + 1) / 2);
	else
		printf("%d]", right / 2);
}

int main () {
	build (1, 0, maxn);

	while (~scanf("%c%*c%c%d,%d%c%*c", &op, &LP, &L, &R, &RP)) {
		L *= 2;
		R *= 2;
		if (LP == '(')
			L++;
		if (RP == ')')
			R--;

		if (op == 'U') {
			modify(1, L, R, 1);
		} else if (op == 'I') {
			modify(1, 0, L - 1, 0);
			modify(1, R + 1, maxn, 0);
		} else if (op == 'D') {
			modify(1, L, R, 0);
		} else if (op == 'C') {
			change(1, L, R);
			modify(1, 0, L - 1, 0);
			modify(1, R + 1, maxn, 0);
		} else if (op == 'S')
			change(1, L, R);
	}

	bool flag = false;
	int c = 0, t;

	for (int i = 0; i <= maxn; i++) {
		int s = query(1, i);
		if (s && !flag) {
			t = i;
			flag = true;
		} else if (!s && flag) {
			if (c++)
				printf(" ");
			put(t, i-1);
			flag = false;
		}
	}

	if (c == 0)
		printf("empty set\n");
	else
		printf("\n");

	return 0;
}
