#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 2 * 1e5 + 5;
const double pi = atan(1.0) * 4;

struct point {
	double x, h;
	bool operator < (const point& u) const {
		return x < u.x;
	}
}p[maxn];

struct edge {
	int v;
	double k;

	void set (int v, double k) {
		this->v = v;
		this->k = k;
	}
}l[maxn], r[maxn];

int N;

inline double get_k(const point& a, const point& b) {
	return (a.h - b.h) / fabs(b.x - a.x);
}

void init () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%lf%lf\n", &p[i].x, &p[i].h);
	sort(p, p + N);

	l[0].set(-1, 0);
	for (int i = 1; i < N; i++) {
		int u = i - 1;

		while (l[u].v != -1 && l[u].k > get_k(p[u], p[i]))
			u = l[u].v;

		l[i].v = u;
		l[i].k = get_k(p[u], p[i]);
	}

	r[N-1].set(-1, 0);
	for (int i = N - 2; i >= 0; i--) {
		int u = i + 1;

		while (r[u].v != -1 && r[u].k > get_k(p[u], p[i]))
			u = r[u].v;

		r[i].v = u;
		r[i].k = get_k(p[u], p[i]);
	}
}

void solve () {
	int n;
	point q;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lf", &q.x);
		q.h = 0;
		int idx = lower_bound(p, p + N, q) - p;

		int mv = idx - 1;
		while (l[mv].v != -1 && l[mv].k > get_k(p[mv], q))
			mv = l[mv].v;

		while (r[idx].v != -1 && r[idx].k > get_k(p[idx], q))
			idx = r[idx].v;
		double R = pi - atan(get_k(p[mv], q)) + atan(get_k(q, p[idx]));
		printf("%.10lf\n", R / pi * 180);
	}
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
