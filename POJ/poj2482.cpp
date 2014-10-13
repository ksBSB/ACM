#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 40000;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)

int lc[maxn << 2], rc[maxn << 2];
ll v[maxn << 2], s[maxn << 2];

inline void pushup (int u) {
	s[u] = max(s[lson(u)], s[rson(u)]) + v[u];
}

inline void maintain (int u, int d) {
	v[u] += d;
	pushup(u);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	v[u] = s[u] = 0;

	if (l == r)
		return;

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

	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, d);
	if (r > mid)
		modify(rson(u), l, r, d);
	pushup(u);
}

struct Seg {
	ll x, l, r, d;
	Seg (ll x = 0, ll l = 0, ll r = 0, ll d = 0) {
		this->x = x;
		this->l = l;
		this->r = r;
		this->d = d;
	}
	friend bool operator < (const Seg& a, const Seg& b) {
		return a.x < b.x;
	}
};

int N, W, H;
vector<ll> pos;
vector<Seg> vec;

inline int find (ll k) {
	return lower_bound(pos.begin(), pos.end(), k) - pos.begin();
}

void init () {
	ll x, y, d;

	pos.clear();
	vec.clear();
	for (int i = 0; i < N; i++) {
		scanf("%lld%lld%lld", &x, &y, &d);
		pos.push_back(y - H);
		pos.push_back(y);
		vec.push_back(Seg(x - W, y - H, y, d));
		vec.push_back(Seg(x, y - H, y, -d));
	}
	sort(pos.begin(), pos.end());
	sort(vec.begin(), vec.end());
}

ll solve () {
	ll ret = 0;
	build (1, 0, pos.size());

	for (int i = 0; i < vec.size(); i++) {
		modify(1, find(vec[i].l), find(vec[i].r) - 1, vec[i].d);
		ret = max(ret, s[1]);
	}
	return ret;
}

int main () {
	while (scanf("%d%d%d", &N, &W, &H) == 3) {
		init();
		printf("%lld\n", solve());
	}
	return 0;
}
