#include <stdio.h>
#define min(a,b) (a)<(b)?(a):(b)

int main () {
	int p, q, r, s;
	while (scanf("%d%d%d%d", &p, &q, &r, &s) == 4) {
		q = min(q, p - q), s = min(s, r - s);
		double ans = 1.0;
		for (int i = 1; i <= q || i <= s; i++) {
			if (i <= q) ans = ans * (p - q + i) / i;
			if (i <= s) ans = ans / (r - s + i) * i;
		}
		printf("%.05lf\n", ans);
	}
	return 0;
}
