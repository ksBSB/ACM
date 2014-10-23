#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 10005;
const int INF = 0x3f3f3f3f;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
struct pii {
	int len, pos;
	pii (int len = 0, int pos = 0) {
		this->len = len;
		this->pos = pos;
	}
	friend bool operator < (const pii& a, const pii& b) {
		if (a.len != b.len)
			return a.len < b.len;
		return a.pos > b.pos;
	}
}s[maxn << 2];
int N, M, pos[maxn], cnt = 0;
int lc[maxn << 2], rc[maxn << 2], L[maxn << 2], R[maxn << 2], set[maxn << 2];

inline int length(int u) {
	return pos[rc[u] + 1] - pos[lc[u]];
}

inline void maintain(int u, int w) {
	set[u] = w;
	if (w) {
		L[u] = R[u] = length(u);
		s[u] = pii(R[u], pos[lc[u]]);
	} else {
		L[u] = R[u] = 0;
		s[u] = pii(0, INF);
	}
}

inline void pushup(int u) {
	pii cur (L[rson(u)] + R[lson(u)], pos[lc[rson(u)]] - R[lson(u)]);
	s[u] = max(max(s[lson(u)], s[rson(u)]), cur);
	L[u] = L[lson(u)] + (L[lson(u)] == length(lson(u)) ? L[rson(u)] : 0);
	R[u] = R[rson(u)] + (R[rson(u)] == length(rson(u)) ? R[lson(u)] : 0);
	//printf("%d %d:%d %d!\n", lc[u], rc[u], s[u].pos, s[u].pos + s[u].len);
}

inline void pushdown(int u) {
	if (set[u] != -1) {
		maintain(lson(u), set[u]);
		maintain(rson(u), set[u]);
		set[u] = -1;
	}
}

void build(int u, int l, int r) {
	lc[u] = l; rc[u] = r;
	set[u] = -1;

	if (l == r) {
		L[u] = R[u] = length(u);
		s[u] = pii(R[u], pos[lc[u]]);
		return;
	}
	int mid = (lc[u] + rc[u]) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid+1, r);
	pushup(u);
}

void modify(int u, int l, int r, int w) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, w);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	if (l <= mid)
		modify(lson(u), l, r, w);
	if (r > mid)
		modify(rson(u), l, r, w);
	pushup(u);
}

pii query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];
	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	pii ret(0, INF);
	if (l <= mid)
		ret = max(ret, query(lson(u), l, r));
	if (r > mid)
		ret = max(ret, query(rson(u), l, r));
	pushup(u);
	return ret;
}

struct Seg {
	int l, r;
	char op[5];
	void read() { scanf("%d%d%s", &l, &r, op);}
}q[maxn];

int find (int x) {
	return lower_bound(pos, pos + M, x) - pos;
}

void init () {
	int n = 0;
	for (int i = 1; i <= N; i++) {
		q[i].read();
		pos[i*2-1] = q[i].l;
		pos[i*2] = q[i].r;
	}

	sort(pos + 1, pos + 1 + N * 2);
	M = unique(pos + 1, pos + 1 + N * 2) - (pos+1);
	pos[0] = 0;
	pos[M + 1] = 1e9;
	build(1, 0, M);
}

int main () {
	while (scanf("%d", &N) == 1) {
		init();

		for (int i = 1; i <= N; i++) {
			modify(1, find(q[i].l), find(q[i].r)-1, q[i].op[0] == 'w' ? 1 : 0);
		}
		printf("%d %d\n", s[1].pos, s[1].pos + s[1].len);
	}
	return 0;
}
