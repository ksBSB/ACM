#include <stdio.h>
#include <string.h>
#include <math.h>

const int N = 1005;
const double eps = 1e-9;

struct point {
	double x, y;
}p[N];
int n, g[N][N], c[N], f[N], v[N];
double d;

int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

double dist (double x, double y) {
	return sqrt(x*x + y*y);
}

void init () {

	memset(v, 0, sizeof(v));
	memset(c, 0, sizeof(c));
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		scanf("%lf%lf", &p[i].x, &p[i].y);
		for (int j = 1; j < i; j++) {
			double tmp = dist(p[i].x-p[j].x, p[i].y-p[j].y);
		   if (d - tmp > -eps) {
				g[i][c[i]++] = j;
				g[j][c[j]++] = i;
			}
		}
	}
}

int main () {
	scanf("%d%lf", &n, &d);

	init ();

	int a, b;
	char str[10];
	while (scanf("%s", str) == 1) {
		if (str[0] == 'O') {

			scanf("%d", &a);
			v[a] = 1;
			int p = getfar(a);;
			for (int i = 0; i < c[a]; i++) {
				int u = g[a][i];

				if (v[u] == 0) continue;

				int q = getfar(g[a][i]);
				if (p != q)
					f[q] = p;
			}
		} else {
			scanf("%d%d", &a, &b);
			int p = getfar(a), q = getfar(b);
			printf("%s\n", p == q ? "SUCCESS" : "FAIL");
		}
	}
	return 0;
}
