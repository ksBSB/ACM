#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 2 * 1e5 + 5;
const double pi = atan(1.0) * 4;

struct point {
	int idx;
	double x, h;
	point (int idx = 0, double x = 0, double h = 0) {
		this->idx = idx;;
		this->x = x;
		this->h = h;
	}

	bool operator < (const point& u) const {
		return x < u.x;
	}
};

struct edge {
	int v;
	double k;

	edge (int v, double k) {
		this->v = v;
		this->k = k;
	}
};

int N;
double l[maxn], r[maxn];
vector<point> p;
vector<edge> g;

inline double get_k(const point& a, const point& b) {
	return (a.h - b.h) / fabs(b.x - a.x);
}

void init () {

	p.clear();

	double x, h;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%lf%lf", &x, &h);
		p.push_back(point(0, x, h));
	}

	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%lf", &x);
		p.push_back(point(i, x, 0));
	}
	sort(p.begin(), p.end());
}

double bsearch (point u) {
	int L = 0, R = g.size();

	while (L < R) {
		int mid = (L + R) / 2;
		if (g[mid].k > get_k(p[g[mid].v], u))
			R = mid;
		else
			L = mid + 1;
	}

	L--;
	double k = p[g[L].v].h / fabs(p[g[L].v].x - u.x);
	return  atan(k);
}

void solve () {

	g.clear();
	g.push_back(edge(0, -1));
	for (int i = 1; i < p.size(); i++) {
		if (p[i].idx > 0) {
			l[p[i].idx] = bsearch(p[i]);
		} else {

			int u = g.size() - 1;
			while (u && g[u].k > get_k(p[g[u].v], p[i])) {
				g.pop_back();
				u--;
			}
			g.push_back(edge(i, get_k(p[g[u].v], p[i])));
		}
	}

	g.clear();
	g.push_back(edge(p.size()-1, -1));
	int u = p.size() - 1;
	for (int i = p.size() - 2; i >= 0; i--) {
		if (p[i].idx > 0) {
			r[p[i].idx] = bsearch(p[i]);
		} else {

			int u = g.size() - 1;
			while (u && g[u].k > get_k(p[g[u].v], p[i])) {
				g.pop_back();
				u--;
			}

			g.push_back(edge(i, get_k(p[g[u].v], p[i])));
		}
	}

	for (int i = 1; i <= N; i++)
		printf("%.10lf\n", (pi - l[i] - r[i]) / pi * 180);
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case #%d:\n", kcas);
		solve();
	}
	return 0;
}
