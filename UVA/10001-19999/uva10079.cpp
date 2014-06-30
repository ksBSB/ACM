#include <stdio.h>
long long sum;
int n;
int main () {
	while (scanf("%d", &n), n >= 0) {
		sum = 1;
		for (long long i = 1; i <= n; i++)
			sum += i;
		printf("%lld\n", sum);
	}
	return 0;
}
