#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-9;

int main () {
	double x, y;

	while (scanf("%lf%lf", &x, &y) == 2) {

		if (x > y) {
			printf("-1\n");
			continue;
		}

		double k = (y+1-eps) / x;
		int cnt = (int)x - 1;

		double tmp = 1;
		for (int i = 1; i <= (int)x; i++) {
			double t = i * k;
			int u = (int)(t-tmp);
			tmp += u;

			tmp = tmp * (i+1) / i;
			cnt += u;
		}
		printf("%d\n", cnt);
	}
	return 0;
}
