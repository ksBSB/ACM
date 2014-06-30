#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)
const int N = 105;
const double INF = 1 << 30;

int n;
double ans, x[N], y[N], g[N][N];

double distant(int a, int b) {
	return sqrt( (x[a] - x[b]) * (x[a] - x[b] ) + (y[a] - y[b]) * (y[a] - y[b]) );
}

void input() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf%lf", &x[i], &y[i]);
		for (int j = 0; j < i; j++) {
			double l = distant(i, j);
			g[j][i] = g[i][j] = (l - 10.0 > 1e-4 ? INF : l);
		}
	}
}

void Floyd() {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}

	ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j)
				ans = max(ans , g[i][j]);
		}
	}

}

int main () {
	int cas, ti = 1;
	scanf("%d", &cas);
	while (cas--) {
		input();
		Floyd();
		printf("Case #%d:\n", ti++);
		if (fabs(ans - INF) < 1e-4) printf("Send Kurdy\n");
		else printf("%.4lf\n", ans);
		printf("\n");
	}
	return 0;
}
