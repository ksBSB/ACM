#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 20005;

vector<int> pos;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], set[maxn << 2];
int L[maxn << 2], R[maxn << 2], S[maxn << 2], len[maxn << 2];

inline int length(int u) {
	return rc[u] - lc[u] + 1;
}

inline void pushup (int u) {
	if (set[u]) {
		L[u] = R[u] = length(u);
		len[u] = pos[rc[u] + 1] - pos[lc[u]];
		S[u] = 1;
	} else if (lc[u] == rc[u]) {
		len[u] = 0;
		L[u] = R[u] = S[u] = 0;
	} else {
		S[u] = S[lson(u)] + S[rson(u)] + (R[lson(u)] && L[rson(u)] ? -1 : 0);
		L[u] = L[lson(u)] + (L[lson(u)] == length(lson(u)) ? L[rson(u)] : 0);
		R[u] = R[rson(u)] + (R[rson(u)] == length(rson(u)) ? R[lson(u)] : 0);
		len[u] = len[lson(u)] + len[rson(u)];
	}
}

inline void maintain (int u, int v) {
	set[u] += v;
	pushup(u);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	set[u] = 0;

	if (l == r) {
		maintain(u, 0);
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int v) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, v);
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, v);
	if (r > mid)
		modify(rson(u), l, r, v);
	pushup(u);
}

typedef long long ll;

struct point {
	int x1, y1;
	int x2, y2;
}p[maxn];

struct Seg {
	int x, l, r, v;
	Seg (int x = 0, int l = 0, int r = 0, int v = 0) {
		this->x = x;
		this->l = l;
		this->r = r;
		this->v = v;
	}
};

inline bool cmp (const Seg& a, const Seg& b) {
	return a.x < b.x;
}

int N;
vector<Seg> vec;

inline int find (int x) {
	return lower_bound(pos.begin(), pos.end(), x) - pos.begin();
}

int main () {
	while (scanf("%d", &N) == 1) {
		vec.clear();
		pos.clear();

		for (int i = 0; i < N; i++) {
			scanf("%d%d%d%d", &p[i].x1, &p[i].y1, &p[i].x2, &p[i].y2);
			pos.push_back(p[i].y1);
			pos.push_back(p[i].y2);
		}
		sort(pos.begin(), pos.end());
		build(1, 0, pos.size());

		for (int i = 0; i < N; i++) {
			int l = find(p[i].y1), r = find(p[i].y2) - 1;
			vec.push_back(Seg(p[i].x1, l, r, 1));
			vec.push_back(Seg(p[i].x2, l, r, -1));
		}
		sort(vec.begin(), vec.end(), cmp);

		ll ans = 0;
		for (int i = 0; i < vec.size(); i++) {

			int tmp = len[1];
			modify(1, vec[i].l, vec[i].r, vec[i].v);
			ans += abs(tmp - len[1]);

			if (i != vec.size() - 1)
				ans += (2LL * S[1] * (vec[i+1].x - vec[i].x));
		}
		printf("%lld\n", ans);
	}
	return 0;
}
