#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e4 + 5;
#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)

namespace SegTree {
	int lc[maxn << 2], rc[maxn << 2];
	ll A[maxn << 2], D[maxn << 2], S[maxn << 2];

	void maintain (int u, ll a, ll d) {
		A[u] += a;
		D[u] += d;
		int n = rc[u] - lc[u] + 1;
		S[u] += a * n + d * (n-1) * n / 2;
	}

	void pushup(int u) {
		S[u] = S[lson(u)] + S[rson(u)];
	}

	void pushdown (int u) {
		if (A[u] || D[u]) {
			int mid = ((lc[u] + rc[u]) >> 1) + 1;
			maintain(lson(u), A[u], D[u]);
			maintain(rson(u), A[u] + (mid - lc[u]) * D[u], D[u]);
			A[u] = D[u] = 0;
		}
	}

	void build (int u, int l, int r) {
		lc[u] = l;
		rc[u] = r;
		A[u] = D[u] = S[u] = 0;

		if (l == r) {
			return;
		}

		int mid = (l + r) >> 1;
		build (lson(u), l, mid);
		build (rson(u), mid + 1, r);
		pushup(u);
	}

	void modify (int u, int l, int r, ll a, ll d) {
		if (l <= lc[u] && rc[u] <= r) {
			maintain(u, a + (lc[u] - l) * d, d);
			return;
		}

		pushdown(u);
		int mid = (lc[u] + rc[u]) >> 1;
		if (l <= mid)
			modify(lson(u), l, r, a, d);
		if (r > mid)
			modify(rson(u), l, r, a, d);
		pushup(u);
	}

	ll query (int u, int l, int r) {
		if (l <= lc[u] && rc[u] <= r)
			return S[u];

		pushdown(u);
		ll ret = 0;
		int mid = (lc[u] + rc[u]) >> 1;
		if (l <= mid)
			ret += query(lson(u), l, r);
		if (r > mid)
			ret += query(rson(u), l, r);
		return ret;
	}
};

int gcd (int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

struct State {
	int l, r, idx;
	State (int l = 0, int r = 0, int idx = 0): l(l), r(r), idx(idx) {}
	bool operator < (const State& u) const { return r < u.r; }
}S[maxn], G[maxn];
int N, Q, A[maxn];
ll R[maxn];

void init () {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &A[i]);
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) {
		scanf("%d%d", &S[i].l, &S[i].r);
		S[i].idx = i;
	}
	sort(S + 1, S + 1 + Q);

	SegTree::build(1, 1, N);
}

void solve () {
	int n = 0, p = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < n; j++)
			G[j].idx = gcd(G[j].idx, A[i]);
		G[n++] = State(i, i, A[i]);
		int mv = 0;
		for (int j = 1; j < n; j++) {
			if (G[mv].idx == G[j].idx)
				G[mv] = State(G[mv].l, G[j].r, G[j].idx);
			else
				G[++mv] = G[j];
		}
		n = mv + 1;
		//printf("%d:%d\n", i, n);
		for (int i = 0; i < n; i++) {
		//	printf("%d %d %d\n", G[i].l, G[i].r, G[i].idx);
			int k = G[i].r - G[i].l + 1;
			SegTree::modify(1, G[i].l, G[i].r, 1LL * G[i].idx * k, -G[i].idx);
			if (G[i].l > 1)
				SegTree::modify(1, 1, G[i].l - 1, 1LL * G[i].idx * k, 0);
		}

		while (p <= N && S[p].r == i) {
			R[S[p].idx] = SegTree::query(1, S[p].l, S[p].l);
			p++;
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init ();
		solve ();
		for (int i = 1; i <= Q; i++)
			printf("%lld\n", R[i]);
	}
	return 0;
}
