#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 100005;
const ll inf = 0x3f3f3f3f3f3f3f3f;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

struct Edge {
	ll oo, oe, eo, ee;
	Edge() {
		oo = oe = eo = ee = -inf;
	}
	ll Answer() {
		return max(max(oo, oe), max(eo, ee));
	}
}s[maxn << 2];
int lc[maxn << 2], rc[maxn << 2];

int N, M, A[maxn];

Edge merge(Edge l, Edge r) {
	Edge ret;
	ret.oo = max(l.oo + r.eo, l.oe + r.oo);
	ret.oo = max(ret.oo, max(l.oo, r.oo));

	ret.oe = max(l.oo + r.ee, l.oe + r.oe);
	ret.oe = max(ret.oe,  max(l.oe, r.oe));

	ret.eo = max(l.eo + r.eo, l.ee + r.oo);
	ret.eo = max(ret.eo, max(l.eo, r.eo));

	ret.ee = max(l.eo + r.ee, l.ee + r.oe);
	ret.ee = max(ret.ee, max(l.ee, r.ee));
	return ret;
}

void maintain(int u, int x, ll d) {
	if (x&1) {
		s[u].oo = d;
		s[u].ee = -inf;
	} else {
		s[u].oo = -inf;
		s[u].ee = d;
	}
	s[u].oe = s[u].eo = -inf;
}
void pushup(int u) {
	s[u] = merge(s[lson(u)], s[rson(u)]);
}

void build(int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		maintain(u, l, A[l]);
		return;
	}

	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid+1, r);
	pushup(u);
}

void modify(int u, int x, ll d) {
	if (lc[u] == rc[u]) {
		maintain(u, x, d);
		return;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid)
		modify(lson(u), x, d);
	if (x > mid)
		modify(rson(u), x, d);
	pushup(u);
}

Edge query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	Edge ret;
	int mid = (lc[u] + rc[u]) >> 1;
	if (l <= mid)
		ret = merge(ret, query(lson(u), l, r));
	if (r > mid)
		ret = merge(ret, query(rson(u), l, r));
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		build(1, 1, N);

		int type, l, r;
		for (int i = 0; i < M; i++) {
			scanf("%d%d%d", &type, &l, &r);
			if (type) 
				modify(1, l, r);
			else {
				Edge ret = query(1, l, r);
				printf("%lld\n", ret.Answer());
			}
		}
	}

	return 0;
}
