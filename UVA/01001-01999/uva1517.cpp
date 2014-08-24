#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

struct point {
	int x, y;
	point (int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}

	point operator + (const point& u) {
		return point(x + u.x, y + u.y);
	}
	point operator - (const point& u) {
		return point(x - u.x, y - u.y);
	}
	int operator ^ (const point& u) {
		return x * u.y - y * u.x;
	}
	bool operator < (const point& u) const {
		if (x != u.x)
			return x < u.x;
		return y < u.y;
	}
};
typedef pair<point, point> line;

int S, R, W, P;
set<point> pset;
vector<line> pline;

void init () {
	pset.clear();
	pline.clear();
	scanf("%d%d%d%d", &S, &R, &W, &P);

	point u, v;
	for (int i = 0; i < S; i++) {
		scanf("%d%d", &u.x, &u.y);
		pset.insert(u);
	}

	for (int i = 0; i < W; i++) {
		scanf("%d%d%d%d", &u.x, &u.y, &v.x, &v.y);
		pline.push_back(make_pair(u, v));
	}
}

bool check (point a, point b, point c, point d) {
	if (max(a.x, b.x) < min(c.x, d.x) ||
		max(a.y, b.y) < min(c.y, d.y) ||
		min(a.x, b.x) > max(c.x, d.x) ||
		min(a.y, b.y) > max(c.y, d.y) )
		return false;

	ll i = (b - a) ^ (b - c);
	ll j = (b - a) ^ (b - d);
	ll p = (d - c) ^ (d - a);
	ll q = (d - c) ^ (d - b);
	return i * j <= 0 && p * q <= 0;
}

bool judge (point u, int x, int y) {
	if (x * x + y * y > R * R)
		return false;
	point v = u + point(x, y);

	if (!pset.count(v))
		return false;

	int cnt = 0;
	for (int i = 0; i < W; i++) {
		if (check(u, v, pline[i].first, pline[i].second))
			cnt++;
	}
	if (cnt > R)
		return false;
	return x * x + y * y <= (R - cnt) * (R - cnt);
}

void solve () {
	point u;
	vector<point> ans;

	for (int i = 0; i < P; i++) {
		ans.clear();
		scanf("%d%d", &u.x, &u.y);

		for (int x = -R; x <= R; x++) {
			for (int y = -R; y <= R; y++) {
				if (judge(u, x, y))
					ans.push_back(u + point(x, y));
			}
		}

		sort(ans.begin(), ans.end());
		printf("%lu", ans.size());
		for (int i = 0; i < ans.size(); i++)
			printf(" (%d,%d)", ans[i].x, ans[i].y);
		printf("\n");
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
