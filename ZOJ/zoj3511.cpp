#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 10005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2];

inline void pushdown(int u) {
	if (s[u] == 0)
		s[lson(u)] = s[rson(u)] = 0;
}

inline void pushup(int u) {
	s[u] = s[lson(u)] + s[rson(u)];
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		s[u] = 1;
		return;
	}

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r) {
	if (l > r)
		return;

	if (l <= lc[u] && rc[u] <= r) {
		s[u] = 0;
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r);
	if (r > mid)
		modify(rson(u), l, r);
	pushup(u);
}

int N, M;
struct Seg {
	int l, r, c;
	Seg (int l = 0, int r = 0) {
		this->l = l;
		this->r = r;
		this->c = r - l + 1;
	}
	friend bool operator < (const Seg& a, const Seg& b) {
		return a.c < b.c;
	}
};
vector<Seg> vec;

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		int l, r, ans = 0;
		build(1, 1, N);
		vec.clear();

		while (M--) {
			scanf("%d%d", &l, &r);
			if (l > r) swap(l, r);
			vec.push_back(Seg(l, r));
		}
		sort(vec.begin(), vec.end());

		for (int i = 0; i < vec.size(); i++) {
			int tmp = s[1];
			modify(1, vec[i].l + 1, vec[i].r - 1);
			ans = max(ans, tmp - s[1] + 2);
		}
		printf("%d\n", max(ans, s[1]));
	}
	return 0;
}
