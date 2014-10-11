#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 50005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], v[maxn << 2], s[maxn << 2];

inline void pushup (int u) {
	if (v[u])
		s[u] = rc[u] - lc[u] + 1;
	else if (rc[u] == lc[u])
		s[u] = 0;
	else
		s[u] = s[lson(u)] + s[rson(u)];
}

inline void maintain (int u, int d) {
	v[u] += d;
	pushup(u);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	s[u] = v[u] = 0;

	if (l == r)
		return ;

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
	int x, l, r, d;
	Seg (int x = 0, int l = 0, int r = 0, int d = 0) {
		this->x = x;
		this->l = l;
		this->r = r;
		this->d = d;
	}
};

typedef long long ll;

int N;
vector<Seg> vec;

inline bool cmp (const Seg& a, const Seg& b) {
		return a.x < b.x;
}

inline void add (int x1, int y1, int x2, int y2) {
	if (y1 == y2 || x1 == x2)
		return;
	vec.push_back(Seg(x1, y1, y2 - 1, 1));
	vec.push_back(Seg(x2, y1, y2 - 1, -1));
}

void init () {
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;

	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	scanf("%d%d%d%d", &x3, &y3, &x4, &y4);
	add (x1, y1, x2, y3);
	add (x1, y3, x3, y4);
	add (x4, y3, x2, y4);
	add (x1, y4, x2, y2);
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		build(1, 0, 50000);
		vec.clear();
		for (int i = 0; i < N; i++)
			init();
		sort(vec.begin(), vec.end(), cmp);

		ll ans = 0;
		for (int i = 0; i < vec.size(); i++) {
			modify(1, vec[i].l, vec[i].r, vec[i].d);
			if (i != vec.size() - 1)
				ans += 1LL * s[1] * (vec[i+1].x - vec[i].x);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
