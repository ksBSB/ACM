#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
typedef long long ll;

const ll mod = 200904040963LL;
const int maxn = 300000;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], s[maxn << 2];

inline void pushup(int u) {
	s[u] = s[lson(u)] + s[rson(u)];
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	s[u] = 0;

	if (l == r)
		return;

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify(int u, int x) {
	if (lc[u] == x && x == rc[u]) {
		s[u] += 1;
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (x <= mid)
		modify(lson(u), x);
	else
		modify(rson(u), x);
	pushup(u);
}

int query(int u, int l, int r) {
	if (l <= lc[u] && rc[u] <= r)
		return s[u];
	
	int mid = (lc[u] + rc[u]) / 2, ret = 0;
	if (l <= mid)
		ret += query(lson(u), l, r);
	if (r > mid)
		ret += query(rson(u), l, r);
	return ret;
}

struct point {
	int t,  x, y;
	point (int x = 0, int y = 0, int t = 0) {
		set(x, y);
		this->t = t;
	}
	void set (int x, int y) {
		this->x = x;
		this->y = y;
	}
	friend bool operator < (const point& a, const point& b) {
		if (a.x != b.x)
			return a.x < b.x;
		if (a.y != b.y)
			return a.y < b.y;
		return a.t < b.t;
	}
};

struct state {
	point a, b;
	state (point a, point b) {
		this->a = a;
		this->b = b;
	}
};

int N, M, P;
ll T[350];
vector<int> pos, tmp, cnt;
vector<point> vec;
vector<state> que;
map<point, int> G;

inline void add_point (ll x, ll y, int k) {
	vec.push_back(point(x, y, k));
	tmp.push_back(y);
}

inline void add_state (int a, int b, int c, int d) {
	add_point(a - 1, b - 1, 1);
	add_point(c, d, 1);

	int u = vec.size();
	que.push_back(state(vec[u-2], vec[u-1]));

	add_point(a - 1, d, 1);
	add_point(c, b - 1, 1);
}

inline int find (int a) {
	return lower_bound(pos.begin(), pos.end(), a) - pos.begin();
}

void init () {
	G.clear();
	cnt.clear();
	vec.clear();
	que.clear();
	pos.clear();
	tmp.clear();

	int a, b, c, d, aa, bb, cc, dd, k;

	for (int i = 0; i < M; i++) {
		scanf("%d%d%d%d%d", &a, &b, &aa, &bb, &k);
		a = (a + N) % N; b = (b + N) % N;
		for (int j = 0; j < k; j++) {
			add_point(a, b, 0);
			a = (a + aa + N) % N;
			b = (b + bb + N) % N;
		}
	}

	scanf("%d", &P);
	for (int i = 0; i < P; i++) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		scanf("%d%d%d%d%d", &aa, &bb, &cc, &dd, &k);
		a = (a + N) % N; b = (b + N) % N;
		c = (c + N) % N; d = (d + N) % N;

		cnt.push_back(k);
		for (int j = 0; j < k; j++) {
			add_state(min(a, b), min(c, d), max(a, b), max(c, d));

			a = (a + aa + N) % N; b = (b + bb + N) % N;
			c = (c + cc + N) % N; d = (d + dd + N) % N;
		}
	}

	sort(vec.begin(), vec.end());
	sort(tmp.begin(), tmp.end());
	pos.push_back(tmp[0]);
	for (int i = 1; i < tmp.size(); i++) {
		if (tmp[i] != tmp[i-1])
			pos.push_back(tmp[i]);
	}
	build(1, 0, pos.size());
}

inline int judge (state u) {
	return G[u.b] + G[u.a] - G[point(u.b.x, u.a.y, 1)] - G[point(u.a.x, u.b.y, 1)];
}

void solve () {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i].t)
			G[vec[i]] = query(1, 0, find(vec[i].y));
		else
			modify(1, find(vec[i].y));
	}

	int mv = 0;
	for (int i = 0; i < cnt.size(); i++) {
		if (cnt[i] > 20) {
			ll ret = 0;
			for (int j = 0; j < cnt[i]; j++)
				ret = (ret + (judge(que[mv + j]) > 0 ? 1 : 0) * T[j]) % mod;
			printf("%lld", ret);
		} else {
			for (int j = 0; j < cnt[i]; j++)
				printf("%d", judge(que[mv + j]) > 0 ? 1 : 0);
		}

		mv += cnt[i];
		printf("\n");
	}
}

int main () {

	T[0] = 1;
	for (int i = 1; i <= 345; i++)
		T[i] = T[i-1] * 7 % mod;

	while (scanf("%d%d", &N, &M) == 2) {
		init();
		solve();
	}
	return 0;
}
