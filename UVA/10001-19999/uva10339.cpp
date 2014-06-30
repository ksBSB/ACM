#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

const int R = 12 * 60 * 60;
const int D = 24 * 60 * 60;

int k, m;

int main () {
	while (scanf("%d%d", &k, &m) == 2) {
		int d = abs(k - m);
		if (d == 0) {
			printf("%d %d 12:00\n", k, m);
			continue;	
		}

		double p = R*1.0/d;
		int t = (int)(p * (D - k)/60.0 + 0.5)%D;

		int h = t/60;
		h %= 12;
		if (h == 0) h = 12;
		int f = t%60;
		printf("%d %d %02d:%02d\n", k, m, h, f);
	}
	return 0;
}
