#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main  () {
	int x, y;
	double l, r, d, a, b;
	while (scanf("%d", &x) == 1) {
		y = x;
		int c = 0;
		while (y) {
			c++;
			y /= 10;
		}

		l = log(x) / log(2);
		r = log(x + 1) / log(2);
		d = log(10) / log(2);

		for (int i = c + 1; ; i++) {
			a = l + i * d;
			b = r + i * d;

			if (ceil(a) <= floor(b)) {
				printf("%.0lf\n", ceil(a));
				break;
			} else if (i == 1000000) {
					printf("no power of 2\n");
					break;
			}
		}
	}
	return 0;
}
