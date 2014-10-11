#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 4005;

vector<int> pos;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], v[maxn << 2], s[maxn << 2][5];

inline void pushup(int u) {
	memset(s[u], 0, sizeof(s[u]));

	if (v[u] >= 3)
		s[u][3] = pos[rc[u]+1] - pos[lc[u]];
	else {
		if (lc[u] == rc[u])
			s[u][v[u]] = pos[rc[u]+1] - pos[lc[u]];
		else if (v[u] == 2) {
			s[u][2] = s[lson(u)][0] + s[rson(u)][0];
			for (int i = 1; i <= 3; i++)
				s[u][3] += s[lson(u)][i] + s[rson(u)][i];
		} else if (v[u] == 1) {
			s[u][1] = s[lson(u)][0] + s[rson(u)][0];
			s[u][2] = s[lson(u)][1] + s[rson(u)][1];
			for (int i = 2; i <= 3; i++)
				s[u][3] += s[lson(u)][i] + s[rson(u)][i];
		} else {
			for (int i = 0; i <= 3; i++)
				s[u][i] = s[lson(u)][i] + s[rson(u)][i];
		}
	}
}

inline void maintain(int u, int d) {
	v[u] += d;
	pushup(u);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	v[u] = 0;

	if (l == r) {
		maintain(u, 0);
		return ;
	}

	int mid = (l + r) / 2;
	build (lson(u), l, mid);
	build (rson(u), mid + 1, r);
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
vector<Seg> g[1005];

inline bool cmp (const Seg& a, const Seg& b) {
	return a.x < b.x;
}

void init () {
	int n, x1, x2, y1, y2, z1, z2;

	scanf("%d", &n);
	for (int i = 0; i <= 1000; i++)
		g[i].clear();

	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
		for (int i = z1; i < z2; i++) {
			g[i + 500].push_back(Seg(x1, y1, y2, 1));
			g[i + 500].push_back(Seg(x2, y1, y2, -1));
		}
	}
}

inline int find (int k) {
	return lower_bound(pos.begin(), pos.end(), k) - pos.begin();
}

ll solve (int idx) {

	if (g[idx].size() == 0)
		return 0;

	ll ret = 0;
	pos.clear();
	sort(g[idx].begin(), g[idx].end(), cmp);

	for (int i = 0; i < g[idx].size(); i++) {
		pos.push_back(g[idx][i].l);
		pos.push_back(g[idx][i].r);
	}

	sort(pos.begin(), pos.end());
	build(1, 0, pos.size());

	for (int i = 0; i < g[idx].size(); i++) {
		modify(1, find(g[idx][i].l), find(g[idx][i].r) - 1, g[idx][i].d);
		if (i + 1 != g[idx].size())
			ret += 1LL * s[1][3] * (g[idx][i+1].x - g[idx][i].x);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();

		ll ans = 0;
		for (int i = 0; i <= 1000; i++)
			ans += solve(i);

		printf("Case %d: %I64d\n", kcas, ans);
	}
	return 0;
}
