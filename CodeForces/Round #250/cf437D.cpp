#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5+5;

struct edge {
	int u, v, w;
}e[N];

int n, m, f[N], c[N], w[N];

bool cmp (const edge& a, const edge& b) {
	return a.w > b.w;
}

int getfar (int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

void init () {
	scanf("%d%d", &n, &m);

	for (int i = 1; i <= n; i++) {
		f[i] = i;
		c[i] = 1;
		scanf("%d", &w[i]);
	}

	for (int i = 0; i < m; i++) {
		scanf("%d%d", &e[i].u, &e[i].v);
		e[i].w = min(w[e[i].u], w[e[i].v]);
	}

	sort(e, e + m, cmp);
}

int main () {
	init();
	double ans = 0;

	for (int i = 0; i < m; i++) {
		int p = getfar(e[i].u);
		int q = getfar(e[i].v);

		if (p != q) {
			ans += (double)e[i].w * c[p] * c[q];
			c[p] += c[q];
			f[q] = p;
		}
	}
	printf("%.6lf\n", ans * 2 / (n * 1.0 * (n-1)));
	return 0;
}
