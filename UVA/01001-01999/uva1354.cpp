#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 10;
const int M = 105;
const double INF = 0x3f3f3f3f;

int n, v[N], t[M];
double R, w[N], ans, l[M], r[M], val[M];

void init () {
	memset(t, 0, sizeof(t));
	memset(v, 0, sizeof(v));
	t[1] = -1; ans = -1;

	scanf("%lf%d", &R, &n);
	for (int i = 1; i <= n; i++) scanf("%lf", &w[i]);
}

void judge(int u) {
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));
	memset(val, 0, sizeof(val));

	for (int i = u; i; i--) {
		if (t[i] == -1) {
			int x = i*2, y = i*2+1;
			val[i] = val[x] + val[y];
			double Li = val[y] / val[i];
			double Ri = val[x] / val[i];

			l[i] = min(-Li+l[x], Ri+l[y]);
			r[i] = max(-Li+r[x], Ri+r[y]);
		} else if (t[i]) {
			val[i] = w[t[i]];
		}
	}

	double tmp = r[1] - l[1];
	if (tmp - R < 1e-5 && tmp > ans) ans = tmp;
}

void dfs(int u, int m, int use) {

	if (use == 0) {
		judge(u-1);
		return;
	}

	if (t[u/2] != -1)  {
		dfs(u+1, m, use);
	} else {

		if (use > m) {
			t[u] = -1;
			dfs(u+1, m+1, use);
			t[u] = 0;
		}

		if (m == 1 && use > 1) return;

		for (int i = 1; i <= n; i++) if (!v[i]) {
			v[i] = 1; t[u] = i;
			dfs(u+1, m-1, use-1);
			v[i] = 0; t[u] = 0;
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		if (n == 1) printf("%.10lf\n", 0.0);	
		else {
			dfs(2, 2, n);
			if (ans == -1) printf("-1\n");
			else printf("%.10lf\n", ans);
		}
	}
	return 0;
}
