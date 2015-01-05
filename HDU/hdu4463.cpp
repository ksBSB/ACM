#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 55;

struct edge {
	double d;
	int u, v;
}ed[maxn * maxn];

int N, P, Q, E, far[maxn];
double x[maxn], y[maxn];

inline int getfar(int x) {
	return x == far[x] ? x : far[x] = getfar(far[x]);
}

inline double dis(double x, double y) {
	return sqrt(x*x+y*y);
}

inline bool cmp(const edge& a, const edge& b) {
	return a.d < b.d;
}

void init () {
	E = 0;
	scanf("%d%d", &P, &Q);

	for (int i = 1; i <= N; i++) {
		far[i] = i;
		scanf("%lf%lf", &x[i], &y[i]);
		for (int j = 1; j < i; j++)
			ed[E++] = (edge){dis(x[i]-x[j], y[i]-y[j]), i, j};
	}
	sort(ed, ed + E, cmp);
}

double solve() {
	double ret = dis(x[P]-x[Q], y[P]-y[Q]);
	far[P] = Q;

	for (int i = 0; i < E; i++) {
		int p = getfar(ed[i].u);
		int q = getfar(ed[i].v);
		if (p != q) {
			ret += ed[i].d;
			far[p] = q;
		}
	}
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		init();
		printf("%.2lf\n", solve());
	}
	return 0;
}
