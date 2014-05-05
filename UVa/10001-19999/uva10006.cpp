#include <stdio.h>
#include <string.h>
const int N = 65005;

int n, prime[N];

void init() {
	memset(prime, 0, sizeof(prime));
	prime[0] = prime[1] = 1;
	for (int i = 2; i < N; i++)
		for (int j = i * 2; j < N; j += i)
			prime[j] = 1;
}

long long count(int a, int c) {
	if (c == 1) return a;

	long long p = count(a, c / 2);
	p = p * p;
	if (c % 2) p *= a;
	return p % n;
}

bool judge(int n) {
	if (!prime[n]) return false;
	for (int i = 2; i < n; i++)
		if (count(i, n) != i) return false;
	return true;
}

int main () {
	init();
	while (scanf("%d", &n) && n) {
		if (judge(n))
			printf("The number %d is a Carmichael number.\n", n);
		else
			printf("%d is normal.\n", n);
	}
	return 0;
}
