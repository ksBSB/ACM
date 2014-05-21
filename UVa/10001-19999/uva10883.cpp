#include <cstdio>
#include <cstring>
#include <cmath>

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		int n;
		double ans = 0, a, c = 0;

		scanf("%d", &n);
		for (int j = 0; j < n; j++) {
			scanf("%lf", &a);
			double tmp = log2(fabs(a));

			if (j) {
				c += log2(double(n-j)/j);
				tmp += c;
			}

			if (a < 0)
				ans -= pow(2, tmp - n + 1);
			else
				ans += pow(2, tmp - n + 1);
		}

		printf("Case #%d: %.3lf\n", i,  ans);
	}
	return 0;
}
