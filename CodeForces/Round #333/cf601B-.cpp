#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

int lc[maxn<<2], rc[maxn<<2];
ll sm[maxn<<2], ad[maxn<<2];

void maintain(int u, ll add) {
	ad[u] += add;
	sm[u] += add * (rc[u] - lc[u] + 1);
}
void pushup(int u) { sm[u] = sm[lson(u)] + sm[rson(u)]; }
void pushdown(int u) {
	maintain(lson(u), ad[u]);
	maintain(rson(u), ad[u]);
	ad[u] = 0;
}

void build (int u, int l, int r) {
	lc[u] = l, rc[u] = r;
	sm[u] = ad[u] = 0;

	if (l == r) return;
	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid+1, r);
	pushup(u);
}

void modify(int u, int l, int r, ll add) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, add);
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	if (l <= mid) modify(lson(u), l, r, add);
	if (r > mid) modify(rson(u), l, r, add);
	pushup(u);
}

ll query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return sm[u];

	pushdown(u);
	int mid = (lc[u] + rc[u]) >> 1;
	ll ret = 0;

	if (l <= mid) ret += query(lson(u), l, r);
	if (r > mid) ret += query(rson(u), l, r);
	pushup(u);
	return ret;
}

struct Query {
	int l, r, id;
	bool operator < (const Query& a) const { return r < a.r; }
}Q[105];

int N, K, A[maxn];
ll ans[105];

void init () {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++) scanf("%d", &A[i]);
	for (int i = 0; i < K; i++) {
		scanf("%d%d", &Q[i].l, &Q[i].r);
		Q[i].id = i;
	}
	sort(Q, Q + K);
	build(1, 1, N);
}

int S, T[maxn], P[maxn];

void solve () {
	int mv = S = 0;
	for (int i = 2; i <= N; i++) {
		int tmp = abs(A[i] - A[i-1]);
		while (S && T[S-1] <= tmp) S--;
		T[S] = tmp;
		P[S] = i - 1;
		S++;

		modify(1, 1, P[0], T[0]);
		for (int j = 1; j < S; j++)
			modify(1, P[j-1] + 1, P[j], T[j]);

		while (mv < K && Q[mv].r == i) {
			ans[Q[mv].id] = query(1, Q[mv].l, Q[mv].r);
			mv++;
		}

		if (mv >= K) break;
	}

	for (int i = 0; i < K; i++)
		printf("%lld\n", ans[i]);
}

int main () {
	init();
	solve();
	return 0;
}
