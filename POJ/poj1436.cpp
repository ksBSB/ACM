#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 16000;

struct segment {
	int x, y1, y2;
	void read () {
		scanf("%d%d%d", &y1, &y2, &x);
		y1 *= 2;
		y2 *= 2;
	}
	friend bool operator < (const segment& a, const segment& b) {
		return a.x < b.x;;
	}
}seg[maxn+5];


#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)+1)

int lc[maxn * 4], rc[maxn * 4], w[maxn * 4];

void pushdown (int u) {
	if (w[u] != -1) {
		w[lson(u)] = w[rson(u)] = w[u];
		w[u] = -1;
	}
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	w[u] = -1;

	if (l == r)
		return;

	int mid = (l + r) / 2;
	build (lson(u), l, mid);
	build (rson(u), mid + 1, r);
}

void modify (int u, int l, int r, int v) {
	if (l <= lc[u] && rc[u] <= r) {
		w[u] = v;
		return;
	}

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, v);
	if (r > mid)
		modify(rson(u), l, r, v);
}

void query(int u, int l, int r, vector<int>& v, int* vis) {
	if (l <= lc[u] && rc[u] <= r && w[u] != -1) {
		if (vis[w[u]] == 0) {
			v.push_back(w[u]);
			vis[w[u]] = 1;
		}
		return;
	}

	if (lc[u] == rc[u])
		return;

	pushdown(u);
	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		query(lson(u), l, r, v, vis);
	if (r > mid)
		query(rson(u), l, r, v, vis);
}

int N, vis[maxn+5];
vector<int> g[maxn + 5];

void init () {
	build (1, 0, maxn);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		g[i].clear();
		seg[i].read();
	}
	sort(seg, seg + N);
}

int solve () {
	int ret = 0;
	for (int i = 0; i < N; i++) {
		memset(vis, 0, sizeof(vis));

		query(1, seg[i].y1, seg[i].y2, g[i], vis);
		modify(1, seg[i].y1, seg[i].y2, i);

		sort(g[i].begin(), g[i].end());

		/*
		printf("%d: %d %d\n", i, seg[i].y1, seg[i].y2);
		for (int j = 0; j < g[i].size(); j++)
			printf("%d ", g[i][j]);
		printf("\n");
		*/

		for (int j = 0; j < g[i].size(); j++) {
			int k = g[i][j];

			for (int t = 0; t < j; t++) {
				int id = lower_bound(g[k].begin(), g[k].end(), g[i][t]) - g[k].begin();
				if (id < g[k].size() && g[k][id] == g[i][t])
					ret++;
			}
		}
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
