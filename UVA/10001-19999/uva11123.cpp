#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 205;
const double eps = 1e-9;
const double pi = 4 * atan(1.0);

struct line {
	double k, c, l;
	line (double k, double c = 0, double l = 0) {
		this->k = k;
		this->c = c;
		this->l = l;
	}
	friend bool operator < (const line& a, const line& b) {
		return a.k < b.k;
	}
};

struct state {
	double c, l;
	state (double c, double l) {
		this->c = c;
		this->l = l;
	}
};

int n;
double x[N], y[N];
vector<line> set;
vector<state> g;

inline double distant (double xi, double yi) {
	return xi * xi + yi * yi;
}

inline double cal (int a, int b) {
	if (x[a] == x[b])
		return x[a];
	return y[a] - x[a] * ( (y[a] - y[b]) / (x[a] - x[b]) );
}

inline int C (int a) {
	if (a < 1)
		return 0;
	return a * (a - 1) / 2;
}

inline bool cmpC (const state& a, const state& b) {
	if (fabs(a.c-b.c) > eps)
		return a.c < b.c;
	return a.l < b.l;
}

inline bool cmpL (const state& a, const state& b) {
	return a.l < b.l;
}

int judge () {
	sort(g.begin(), g.end(), cmpC);
	int ans = 0, cnt = 1, tmp = 1;

	/*
	for (int i = 0; i < g.size(); i++) {
		printf("%lf %lf\n", g[i].c, g[i].l);
	}
	printf("\n");
	*/

	for (int i = 1; i < g.size(); i++) {
		if (fabs(g[i].c - g[i-1].c) > eps) {
			ans = ans + C(cnt) - C(tmp);
			cnt = 0;
			tmp = 0;
		}

		if (fabs(g[i].l - g[i-1].l) > eps) {
			ans = ans - C(tmp);
			tmp = 0;
		}

		tmp++;
		cnt++;
	}
	ans = ans + C(cnt) - C(tmp);

	sort(g.begin(), g.end(), cmpL);
	cnt = 1;
	for (int i = 1; i < g.size(); i++) {
		if (fabs(g[i].l - g[i-1].l) > eps) {
			ans = ans + C(cnt);
			cnt = 0;
		}
		cnt++;
	}
	ans = ans + C(cnt);
	return ans;
}

int solve () {

	int ans = 0;

	if (set.size() == 0)
		return 0;

	g.clear();
	g.push_back(state(set[0].c, set[0].l));

	for (int i = 1; i < set.size(); i++) {

		//printf("%d %lf!!!!!!!\n", i, set[i].k);
		if (fabs(set[i].k - set[i-1].k) > eps) {
			ans += C(g.size()) - judge();
			g.clear();
		}
		g.push_back(state(set[i].c, set[i].l));
	}

	ans += C(g.size()) - judge();
	return ans;
}

int main () {
	int cas = 1;
	while (scanf("%d", &n) == 1 && n) {

		set.clear();
		for (int i = 0; i < n; i++) {
			scanf("%lf%lf", &x[i], &y[i]);
			for (int j = 0; j < i; j++)
				set.push_back(line( atan2(y[j]-y[i], x[j]-x[i]), cal(i, j), distant(y[i]-y[j], x[i]-x[j]) ));
		}

		for (int i = 0; i < set.size(); i++) {
			if (set[i].k < eps)
				set[i].k += pi;
		}

		sort(set.begin(), set.end());

		/*
		for (int i = 0; i < set.size(); i++) {
			printf("%d %lf %lf %lf\n", i, set[i].k, set[i].c, set[i].l);
		}
		*/

		printf("Case %d: %d\n", cas++, solve());
	}
	return 0;
}
