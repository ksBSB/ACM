#include <stdio.h>
#include <math.h>

int main () {
	int cas = 1, n;
	while (scanf("%d", &n), n) {
		long long sum = 0, tmp = sqrt(n), cnt = 0;
		for (int i = 2; i <= tmp; i++) {
			if (n % i == 0) {
				int c = 1;
				cnt++;
				while (n % i == 0) {
					c *= i;
					n /= i;
				}
				sum += c;
			}
		}

		if (n > 1 || cnt == 0) {
			sum += n;
			cnt++;
		}
		if (cnt == 1)	sum++;

		printf("Case %d: %lld\n", cas++, sum);
	}
	return 0;
}
