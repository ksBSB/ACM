#include <stdio.h>
#include <string.h>
#include<math.h>

long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	long long p, q;
	while (scanf("%lld%lld", &p, &q), p || q) {
		if (p == q)	printf("2 0\n");
		else if (p == 0) printf("0 2\n");
		else {
			long long g = gcd(p, q);
			p /= g, q /= g;
			long long i, j;
			for (i = 2; i <= 50000; i++) {
				if(i * (i - 1) % q == 0) {
					long long n = i * (i - 1) / q;
					long long m = n * p;
					j = (long long) sqrt(m + 0.5);
					if (j * (j + 1) == m && j + 1 >= 2)
						break;
				}
			}

			if (i <= 50000)
				printf("%lld %lld\n", j + 1, i - j - 1);
			else 
				printf("impossible\n");
		}
	}
	return 0;
}
