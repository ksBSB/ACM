#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-6;

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		double d, u, v;
		scanf("%lf%lf%lf", &d, &v, &u);

		printf("Case %d: ", i);
		if (u-v < eps || u < eps || v < eps)
			printf("can't determine\n");
		else {
			double x = sqrt(u*u - v*v);
			printf("%.3lf\n", d/x - d/u);
		}
	}
	return 0;
}
