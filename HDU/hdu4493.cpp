#include <cstdio>
#include <cstring>

int main () {
	int cas;
	double s, a;
	scanf("%d", &cas);
	while (cas--) {
		s = 0;
		for (int i = 0; i < 12; i++) {
			scanf("%lf", &a);
			s += a;
		}

		s /= 12;
		printf("$%d", (int)s);

		s -= (int)s;
		s *= 100;

		int k = (int)(s + 0.5);
		if (k) {
			printf(".%d", k/10);
			if (k%10)
				printf("%d", k%10);
		}
		printf("\n");
	}
	return 0;
}
