#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1005;

#define lson(x) ((x)<<1)
#define rson(x) (((x)<<1)|1)
int lc[maxn << 2], rc[maxn << 2], v[maxn << 2];
double s[maxn << 2];
vector<double> pos;

inline void pushup(int u) {
	if (v[u])
		s[u] = pos[rc[u] + 1] - pos[lc[u]];
	else if (rc[u] == lc[u])
		s[u] = 0;
	else
		s[u] = s[lson(u)] + s[rson(u)];
}

inline void add(int u, int set) {
	v[u] += set;
	pushup(u);
}

void build (int u, int l, int r) {
	lc[u] = l;
	rc[u] = r;
	v[u] = 0;
	s[u] = 0;

	if (l == r)
		return;

	int mid = (l + r) / 2;
	build(lson(u), l, mid);
	build(rson(u), mid + 1, r);
	pushup(u);
}

void modify (int u, int l, int r, int set) {
	if (l <= lc[u] && rc[u] <= r) {
		add(u, set);
		return;
	}

	int mid = (lc[u] + rc[u]) / 2;
	if (l <= mid)
		modify(lson(u), l, r, set);
	if (r > mid)
		modify(rson(u), l, r, set);
	pushup(u);
}

struct segment {
	double x;
	int l, r, set;
	segment (double x = 0, int l = 0, int r = 0, int set = 0) {
		this->x = x;
		this->l = l;
		this->r = r;
		this->set = set;
	}
};

int N;
vector<segment> vec;
double x1[maxn], x2[maxn], y1[maxn], y2[maxn];

inline bool cmp (const segment& a, const segment& b) {
	return a.x < b.x;
}

inline int find (double k) {
	return lower_bound(pos.begin(), pos.end(), k) - pos.begin();
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		double ans = 0;
		vec.clear();
		pos.clear();

		for (int i = 0; i < N; i++) {
			scanf("%lf%lf%lf%lf", &x1[i], &y1[i], &x2[i], &y2[i]);
			pos.push_back(y1[i]);
			pos.push_back(y2[i]);
		}
		sort(pos.begin(), pos.end());
		build(1, 0, pos.size() * 2 - 1);

		for (int i = 0; i < N; i++) {
			vec.push_back(segment(x1[i], find(y1[i]), find(y2[i]) - 1, 1));
			vec.push_back(segment(x2[i], find(y1[i]), find(y2[i]) - 1, -1));
		}

		sort(vec.begin(), vec.end(), cmp);
		for (int i = 0; i < vec.size() - 1; i++) {
			modify(1, vec[i].l, vec[i].r, vec[i].set);
			ans += (s[1] * (vec[i+1].x - vec[i].x));
		}

		printf("Test case #%d\n", cas++);
		printf("Total explored area: %.2lf\n\n", ans);
	}
	return 0;
}
