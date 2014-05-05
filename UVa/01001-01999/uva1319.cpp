#include <stdio.h>
#include <string.h>
#include <math.h>

int main () {
	int m, p, a, b;
	while (scanf("%d%d%d%d", &m, &p, &a, &b) == 4) {
		int l = 0, r = 0;
		int tmp = a * b;
		for (int i = 1; i < m; i++) {
			if (tmp >= a) {
				r++;
				tmp -= a;
			} else {
				l++;
				tmp++;
			}
		}

		double sum = l / pow(sqrt(a), p) + r * pow (sqrt(a), p);
		sum += pow(tmp/sqrt(a), p);
		printf("%d\n", (int)(sum + 0.5));
	}
	return 0;
}
