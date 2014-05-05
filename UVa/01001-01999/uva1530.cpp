#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

const int N = 20;
const double eps = 1e-6;

char s[N];
int main () {
	printf("Program 6 by team X\n");
	while (scanf("%s", s) == 1) {
		if (strcmp(s+1, "000000000000000") == 0) {
			printf(" 0.000000e+000\n");
			continue;
		}

		int sign = (s[0] == '1' ? 1 : 0);
		int e = 0;
		for (int i = 1; i <= 7; i++) {
			if (s[i] == '1')
				e += (1<<(7-i));
		}

		double a = 1;
		for (int i = 8; i < 16; i++) {
			if (s[i] == '1')
				a += pow(2, 7-i);;
		}

		a *= pow(2, e-63);

		e = log10(a);
		a /= pow(10, e);

		if (a < 1) {
			a *= 10;
			e--;
		}

		printf("%c", sign ? '-' : ' ');
		printf("%.6lfe", a);

		printf("%c", e < 0 ? '-' : '+');
		printf("%03d\n", abs(e));
	}
	printf("End of program 6 by team X\n");
	return 0;
}
