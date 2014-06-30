#include <cstdio>
#include <cstring>
#include <cmath>

int main () {
	int cas;
	double n, m, v, k;
	scanf("%d", &cas);

	while (cas--) {
		scanf("%lf%lf%lf%lf", &n, &m, &v, &k);

		if (m >= n) {
			printf("0\n");
			continue;
		}

		double tmp = (m-v)*k;
		if (tmp <= m) {
			printf("-1\n");
		} else {
			double c = -(v * k) / (k - 1);
			double a = m + c;
			double cnt = log((n+c) / a) / log(double(k));
			printf("%lld\n", (long long)ceil(cnt));
		}
	}
	return 0;
}
