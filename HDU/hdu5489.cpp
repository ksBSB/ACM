#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100005;
#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

struct SegTree {
	int lc[maxn<<2], rc[maxn<<2], s[maxn<<2];

	void pushup(int u) { s[u] = max(s[lson(u)], s[rson(u)]); }

	void modify(int u, int x, int v) {
		if (lc[u] == rc[u]) {
			s[u] = v;
			return;
		}

		int mid = (lc[u] + rc[u]) >> 1;
		if (x <= mid) modify(lson(u), x, v);
		else modify(rson(u), x, v);
		pushup(u);
	}

	int query(int u, int l, int r) {
		if (l <= lc[u] && rc[u] <= r) return s[u];

		int mid = (lc[u] + rc[u]) >> 1, ret = 0;
		if (l <= mid) ret = max(ret, query(lson(u), l, r));
		if (r > mid) ret = max(ret, query(rson(u), l, r));
		return ret;
	}

	void build (int u, int l, int r) {
		lc[u] = l, rc[u] = r, s[u] = 0;
		if (l == r) return;

		int mid = (l + r) >> 1;
		build(lson(u), l, mid);
		build(rson(u), mid+1, r);
		pushup(u);
	}
}T;

struct State {
	int idx, val, pos;
	State (int idx = 0, int val = 0, int pos = 0):idx(idx), val(val), pos(pos) {}
}S[maxn];

inline bool cmpval(const State& a, const State& b) {
	if (a.val != b.val) return a.val < b.val;
	return a.idx < b.idx;
}

inline bool cmpidx(const State& a, const State& b) {
	return a.idx < b.idx;
}

int N, M, L, X[maxn], P[maxn];

void  init () {
	scanf("%d%d", &N, &L);
	for (int i = 0; i < N; i++) {
		scanf("%d", &X[i]);
		S[i] = State(i, X[i]);
	}
	sort(X, X+N);
	M = unique(X, X+N) - X;

	for (int i = 0; i < N; i++)
		S[i].val = lower_bound(X, X+M, S[i].val) - X;
	sort(S, S+N, cmpval);
	for (int i = 0; i < N; i++)
		S[i].pos = i + 1;
	sort(S, S+N, cmpidx);

	memset(P, 0, sizeof(P));
	for (int i = 0; i < N; i++)
		P[S[i].val]++;

	P[0]++;
	for (int i = 1; i < M; i++)
		P[i] += P[i-1];
}

struct Stack {
	int n, s[maxn];
	int search(int x) {
		return lower_bound(s, s + n, x) - s;
	}

	void set(int pos, int x) {
		n = max(n, pos+1);
		s[pos] = x;
	}
}sta;

int solve () {
	T.build(1, 0, N);
	sta.n = 0;

	for (int i = 0; i < N; i++) {
		int t = sta.search(S[i].val);
		T.modify(1, S[i].pos, t+1);
		sta.set(t, S[i].val);
	}

	for (int i = 1; i <= L; i++)
		T.modify(1, S[N-i].pos, 0);

	int ret = T.s[1];
	sta.n = 0;
	for (int i = N-1; i >= L; i--) {
			T.modify(1, S[i-L].pos, 0);
		int t = sta.search(M-S[i].val);
		//printf("%d-%d\n", t+1, T.query(1, 0, P[S[i].val]-1));
		ret = max(ret, t + 1 + T.query(1, 0, P[S[i].val]-1));
		sta.set(t, M-S[i].val);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d: %d\n", kcas, solve());
	}
	return 0;
}
