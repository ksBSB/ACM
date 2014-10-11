#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 30000;

int N, Q;
ll A[maxn+5], ans[100005];
map<ll, int> G;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

int lc[maxn << 2], rc[maxn << 2];
ll s[maxn << 2];

inline void pushup (int u) {
	s[u] = s[lson(u)] + s[rson(u)];
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	s[u] = 0;

	if (l == r)
		return;

	int mid = (lc[u] + rc[u]) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int x, ll d) {
	if (x == lc[u] && rc[u] == x) {
		s[u] += d;
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x, d);
	else
		modify(rson(u), x, d);
	pushup(u);
}

ll query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];

	ll ret = 0;
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	pushup(u);
	return ret;
}

struct Seg {
	int l, r, id;
	Seg (int l = 0, int r = 0, int id = 0) {
		this->l = l;
		this->r = r;
		this->id = id;
	}
	friend bool operator < (const Seg& a, const Seg& b) {
		return a.r < b.r;
	}
};
vector<Seg> vec;

void init () {
	int l, r;
	G.clear();
	vec.clear();
	
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%I64d", &A[i]);

	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++) {
		scanf("%d%d", &l, &r);
		vec.push_back(Seg(l, r, i));
	}
	sort(vec.begin(), vec.end());
}

void solve () {
	build (1, 0, N);
	int k = 0;
	for (int i = 0; i < Q; i++) {
		for ( ; k <= vec[i].r; k++) {
			if (G[A[k]])
				modify(1, G[A[k]], -A[k]);
			G[A[k]] = k;
			modify(1, k, A[k]);
		}
		ans[vec[i].id] = query(1, vec[i].l, vec[i].r);
	}
	for (int i = 1; i <= Q; i++)
		printf("%I64d\n", ans[i]);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}