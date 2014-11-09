#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 40005;
const int bw = 20000;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], ad[maxn << 2], nd[maxn << 2];

inline void pushup(int u) {
	nd[u] = max(nd[lson(u)], + nd[rson(u)]) + ad[u];
}

inline void maintain(int u, int v) {
	ad[u] += v;
	nd[u] += v;
}

void build(int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	ad[u] = nd[u] = 0;

	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int l, int r, int v) {
	if (l <= lc[u] && rc[u] <= r) {
		maintain(u, v);
		return;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (l <= mid)
		modify(lson(u), l, r, v);
	if (r > mid)
		modify(rson(u), l, r, v);
	pushup(u);
}

int query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return nd[u];

	int mid = (lc[u] + rc[u]) >> 1, ret = 0; 
	if (l <= mid)
		ret = max(ret, query(lson(u), l, r));
	if (r > mid)
		ret = max(ret, query(rson(u), l, r));
	pushup(u);
	return ret;
}

struct Seg {
	int x, l, r, w;
	Seg(int x = 0, int l = 0, int r = 0, int w = 0) {
		this->x = x;
		this->l = l;
		this->r = r;
		this->w = w;
	}
};
vector<Seg> G;

inline bool cmp (const Seg& a, const Seg& b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.w < b.w;
}

int N, W, H;

void init () {
	int x, y;
	G.clear();
	scanf("%d%d", &W, &H);
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &x, &y);
		G.push_back(Seg(x, y + bw, min(bw, y + H) + bw, 1));
		G.push_back(Seg(x + W + 1, y + bw, min(bw, y + H) + bw, -1));
	}
	build(1, 0, bw * 2);
	sort(G.begin(), G.end(), cmp);
}

int main () {

	while (scanf("%d", &N) == 1 && N != -1) {
		init();
		int ans = 0;
		for (int i = 0; i < G.size(); i++) {
			modify(1, G[i].l, G[i].r, G[i].w);
			ans = max(ans, nd[1]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
