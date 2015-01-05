#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 60005;

struct node {
	int n, high[15];
	node() { n = 0; }

	void insert(int h) {
		if (n < 10)
			high[n++] = h;
		else if (h < high[n-1])
			high[n-1] = h;
		sort(high, high + n);
	}
};

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2];
node nd[maxn << 2];

inline node merge (node a, node b) {
	node ret;
	int p = 0, q = 0;
	while ((p < a.n || q < b.n) && ret.n <= 10) {
		if (q >= b.n || (p < a.n && a.high[p] < b.high[q]) )
			ret.high[ret.n++] = a.high[p++];
		else
			ret.high[ret.n++] = b.high[q++];
	}
	return ret;
}

void build(int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;

	if (l == r) {
		nd[u].n = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	nd[u] = merge(nd[lson(u)], nd[rson(u)]);
}

void insert (int u, int x, int h) {
	if (x == lc[u] && rc[u] == x) {
		nd[u].insert(h);
		return;
	}

	int mid = (lc[u] + rc[u]) >> 1;
	if (x <= mid)
		insert(lson(u), x, h);
	else
		insert(rson(u), x, h);
	nd[u] = merge(nd[lson(u)], nd[rson(u)]);
}

node query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return nd[u];

	node ret;
	int mid = (lc[u] + rc[u]) >> 1;

	if (l <= mid)
		ret = merge(ret, query(lson(u), l, r));
	if (r > mid)
		ret = merge(ret, query(rson(u), l, r));
	return ret;
}

struct state {
	int x, y, h, id;
}cmd[maxn + 5];

vector<int> pos, tmp;
int N, M, T, ans[30005];

void init () {
	T = N + M;
	pos.clear();
	tmp.clear();
	int x, y, h;

	for (int i = 0; i < N; i++) {
		scanf("%d%d%d", &x, &y, &h);
		tmp.push_back(y);
		cmd[i] = (state) {x, y, h, 0};
	}
	for (int i = 0; i < M; i++) {
		scanf("%d%d%d", &x, &y, &h);
		tmp.push_back(y);
		cmd[i+N] = (state) {x, y, h, i+1};
	}

	sort(tmp.begin(), tmp.end());
	pos.push_back(tmp[0]);
	for (int i = 1; i < tmp.size(); i++) {
		if (tmp[i] != tmp[i-1])
			pos.push_back(tmp[i]);
	}
	build(1, 0, pos.size()-1);
}

inline int find(int x) {
	return lower_bound(pos.begin(), pos.end(), x) - pos.begin();
}

inline bool cmp (const state& a, const state& b) {
	if (a.x != b.x)
		return a.x < b.x;
	if (a.y != b.y)
		return a.y < b.y;
	return a.id < b.id;
}

void solve () {
	sort(cmd, cmd + T, cmp);
	for (int i = 0; i < T; i++) {
		if (cmd[i].id) {
			node tmp = query(1, 0, find(cmd[i].y));
			int kth = cmd[i].h;
			ans[cmd[i].id] = (tmp.n >= kth ? tmp.high[kth-1] : -1);
		} else
			insert(1, find(cmd[i].y), cmd[i].h);
	}
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		init();
		solve();
		for (int i = 1; i <= M; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
