#include <stdio.h>
const double tmp = 1e-7;

int main () {
	int cas, n, aid;
	double p, q;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%lf%d", &n, &p, &aid);
		double ans = 0, c = p, q = 1;

		for (int i = 1; i <= n; i++) {
			if (i < aid) c *= (1 - p);
			q *= (1 - p);
		}

		while (c > tmp) {
			ans += c;
			c *= q;
		}
		printf("%.4lf\n", ans);
	}
	return 0;
}
